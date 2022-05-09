/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/05/09 12:31:28 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exec our buil-ins or exec binary file */
void	execution(int i, t_minishell *shell)
{
	const char	*cmd = shell->cmds[i].av[0];

	if (ft_strlen(cmd) == 4 \
		&& !ft_strncmp(cmd, "echo", 4))
		exec_binary(i, shell);
	else if (ft_strlen(cmd) == 2 \
		&& !ft_strncmp(cmd, "cd", 2))
		cd(i, shell);
	else if (ft_strlen(cmd) == 3 \
		&& !ft_strncmp(cmd, "pwd", 3))
		pwd();
	else if (ft_strlen(cmd) == 6\
		&& !ft_strncmp(cmd, "export", 6))
		export(i, shell);
	else if (ft_strlen(cmd) == 5 \
		&& !ft_strncmp(cmd, "unset", 5))
		unset(i, shell);
	else if (ft_strlen(cmd) == 3 \
		&& !ft_strncmp(cmd, "env", 3))
		env(shell);
	else if (ft_strlen(cmd) == 4 \
		&& !ft_strncmp(cmd, "exit", 4))
		ft_exit(0, shell);
	else
		exec_binary(i, shell);
}

void	reinit_fd(t_exec *exec)
{
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
}

int		make_fd(t_minishell *shell, t_exec *exec)
{
	int	fdin;

	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	if (shell->inf)
		fdin = open(shell->inf, O_RDONLY);
	else if (shell->heredoc != 0)
		fdin = heredoc(shell);
	else
		fdin = dup(exec->tmpin);
	return (fdin);
}

int		get_out_file(int tmpout, t_minishell *shell)
{
	int	fdout;

	if (shell->outf)
	{
		if (shell->append > 0)
			fdout = open(shell->outf, O_APPEND | O_CREAT | O_RDWR,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		else
			fdout = open(shell->outf, O_RDWR | O_CREAT,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

/* creates a new process for each command, the parent process waits 
for the child to exec the command */
void	executor(t_minishell *shell)
{
	int			i;
	t_exec		exec;

	i = -1;
	exec.fdin = make_fd(shell, &exec);
	while (shell->number_cmd >= ++i)
	{
		dup2(exec.fdin, 0);
		close(exec.fdin);
		if (i == shell->number_cmd)
			exec.fdout = get_out_file(exec.tmpout, shell);
		else
		{
			pipe(exec.fdpipe);
			exec.fdout = exec.fdpipe[1];
			exec.fdin = exec.fdpipe[0];
		}
		dup2(exec.fdout, 1);
		close(exec.fdout);
		exec.pid = fork();
		if (exec.pid == -1)
			perror("fork error");
		if (exec.pid == 0)
			execution(i, shell);
	}
	reinit_fd(&exec);
}