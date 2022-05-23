/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/05/23 17:05:04 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* exec our buil-ins or exec binary file */
void	execution(int i, t_minishell *shell, t_exec *exec)
{
	const char	*cmd = shell->cmds[i].av[0];

	if (ft_strlen(cmd) == 4
		&& !ft_strncmp(cmd, "echo", 4))
		exec_binary(i, shell);
	else if (ft_strlen(cmd) == 2
		&& !ft_strncmp(cmd, "cd", 2))
		cd(i, shell);
	else if (ft_strlen(cmd) == 3
		&& !ft_strncmp(cmd, "pwd", 3))
		pwd(i, shell);
	else if (ft_strlen(cmd) == 6
		&& !ft_strncmp(cmd, "export", 6))
		export(i, shell);
	else if (ft_strlen(cmd) == 5
		&& !ft_strncmp(cmd, "unset", 5))
		unset(i, shell);
	else if (ft_strlen(cmd) == 3
		&& !ft_strncmp(cmd, "env", 3))
		env(shell);
	else
		exec_binary(i, shell);
	exit(exec->pid);
}

/*  - wait for child
exit status 128 + N when fatal signal N*/
static void	reinit_fd_and_handle_g_exit_status(t_exec *exec, t_minishell *shell)
{
	char	*g_exit_status_env;

	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
	if (g_exit_status < 128)
	{
		if 	(WIFEXITED(exec->tmpret))
			g_exit_status = WEXITSTATUS(exec->tmpret);
		else if (WIFSIGNALED(exec->pid))
			g_exit_status = WTERMSIG(exec->tmpret);
		g_exit_status_env = ft_strjoin("?=",ft_itoa(g_exit_status));
		unset_env(shell, "?");
		set_env(shell, g_exit_status_env);
		g_exit_status = 0;
		free(g_exit_status_env);
	}
}

/* copie stdin stdout */
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
		if(g_exit_status == 128 + SIGINT)
		{
			g_exit_status = 1;
			return (-1);
		}
		fdin = heredoc(shell);
		if(fdin == -1)
		{
			g_exit_status = 0;
			close(exec->tmpin);
			close(exec->tmpout);
		}
		// printf("fdin=%d\n",fdin);
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
			fdout = open(shell->outf, O_RDWR | O_CREAT,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

/*
 MAIN THING :
-creates a new process for each command, the parent process waits
for the child to exec the command
- pipe it up
*/

int	ft_is_builtin(int i, t_minishell *shell)
{
	const char	*cmd = shell->cmds[i].av[0];

	if( shell->number_cmd != 0)
		return (0);
	if (ft_strlen(cmd) == 2
		&& !ft_strncmp(cmd, "cd", 2))
	{	
		cd(i, shell);
		return (1);
	}
	else if (ft_strlen(cmd) == 6
	&& !ft_strncmp(cmd, "export", 6))
	{
		export(i, shell);
		return (1);
	}
	else if (ft_strlen(cmd) == 5
		&& !ft_strncmp(cmd, "unset", 5))
	{
		unset(i, shell);
		return (1);
	}
	return (0);

}

void	executor(t_minishell *shell)
{
	int			i;
	t_exec		exec;

	i = -1;
	exec.fdin = store_fd(shell, &exec);
	ft_signaux("heredoc");
	if (exec.fdin == -1 || ft_is_builtin(shell->number_cmd, shell)) // stop heredo and exec 1 buiiltin export, etc
		return;
	ft_signaux("command");
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
		ft_error(exec.pid, "fork");
		if (exec.pid == 0)
			execution(i, shell, &exec);
	}
	reinit_fd_and_handle_g_exit_status(&exec, shell);
}

// 		if (exec.pid == -1)
//			perror("fork error");