/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/05/25 23:16:13 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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
	while (wait(NULL)>0); // waits for all children process

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
		fdin = heredoc(shell);
		if(g_exit_status == 128 + SIGINT)
		{
			g_exit_status = 1;
			close(exec->tmpin);
			close(exec->tmpout);
			return (-1);
		}
		if(fdin == -1)
		{
			g_exit_status = 0;
			close(exec->tmpin);
			close(exec->tmpout);
		}
		// printf("fdin=%d\n",g_exit_status);
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

void	executor(t_minishell *shell)
{
	int			i;
	t_exec		exec;

	i = -1;
	ft_signaux("heredoc");
	exec.fdin = store_fd(shell, &exec);
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