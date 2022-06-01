/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/06/01 11:33:58 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  - wait for child
exit status 128 + N when fatal signal N
closes the files after dup into strin and out*/
static void	reinit_fd_and_handle_g_exit_status(t_exec *exec, t_minishell *shell)
{
	char	*g_exit_status_env;
	char	*tmp;

	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
	if (g_exit_status < 128)
	{
		if (WIFEXITED(exec->tmpret))
			g_exit_status = WEXITSTATUS(exec->tmpret);
		else if (WIFSIGNALED(exec->pid))
			g_exit_status = WTERMSIG(exec->tmpret);
		tmp = ft_itoa(g_exit_status);
		g_exit_status_env = ft_strjoin("?=", tmp);
		unset_env(shell, "?");
		set_env(shell, g_exit_status_env);
		ft_exit_status(g_exit_status, shell);
		free(g_exit_status_env);
		free(tmp);
	}
	while (wait(NULL) > 0)
		;
}

// 1 strore stdin ou infile, and  2 dup stdout  3 make heredoc
int	store_fd(t_minishell *shell, t_exec *exec)
{
	int	fdin;

	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	if (shell->inf)
		fdin = open(shell->inf, O_RDONLY);
	else if (shell->heredoc != 0)
	{
		ft_signaux("heredoc");
		fdin = heredoc(shell);
		if (g_exit_status == 128 + SIGINT)
			return (store_fd_close(exec->tmpin, exec->tmpout));
	}
	else
		fdin = dup(exec->tmpin);
	return (fdin);
}

/* open (path,  flags -> O_CREAT, O_APPEND = >>,
MODE -> define rights if O_CREAT)
Open if outf : open en mode ajout ou non
else */
int	get_out_file(int tmpout, t_minishell *shell)
{
	int	fdout;

	if (shell->outf)
	{
		if (shell->append > 0)
			fdout = open(shell->outf, O_APPEND | O_CREAT | O_RDWR,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		else
			fdout = open(shell->outf, O_RDWR | O_CREAT | O_TRUNC,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

void	elsexutor(t_exec *exec)
{
	int	i;

	i = pipe(exec->fdpipe);
	if (i == -1)
	{
		ft_putendl_fd("exit pipe error", 2);
		exit(2);
	}
	exec->fdout = exec->fdpipe[1];
	exec->fdin = exec->fdpipe[0];
}

/*
 MAIN THING :
-creates a new process for each command, the parent process waits
for the child to exec the command
- pipe it up
 THE EXECUTION -> store fds, fork each pipes, the parent pid waits children
 and then get the outfile*/
void	executor(t_minishell *shell)
{
	int			i;
	t_exec		exec;

	i = -1;
	exec.fdin = store_fd(shell, &exec);
	if (exec.fdin == -1 || ft_is_builtin(shell->number_cmd, shell))
		return ;
	ft_signaux("command");
	while (shell->number_cmd >= ++i && shell->cmds[0].av[0] != NULL)
	{
		dup2(exec.fdin, 0);
		close(exec.fdin);
		if (i == shell->number_cmd)
			exec.fdout = get_out_file(exec.tmpout, shell);
		else
			elsexutor(&exec);
		dup2(exec.fdout, 1);
		close(exec.fdout);
		exec.pid = fork();
		ft_error(exec.pid, "fork");
		if (exec.pid == 0)
			execution(i, shell, &exec);
	}
	reinit_fd_and_handle_g_exit_status(&exec, shell);
}
