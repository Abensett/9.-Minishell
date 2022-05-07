/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/05/07 13:19:44 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exec our buil-ins or exec binary file */
void	execution(int i, t_minishell *shell)
{
	const char	*cmd = shell->cmds[i].av[0];

	if (ft_strlen(cmd) == ft_strlen("echo") \
		&& !ft_strncmp(cmd, "echo", ft_strlen("echo")))
		echo(i, shell);
	else if (ft_strlen(cmd) == ft_strlen("cd") \
		&& !ft_strncmp(cmd, "cd", ft_strlen("cd")))
		cd(i, shell);
	else if (ft_strlen(cmd) == ft_strlen("pwd") \
		&& !ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		pwd();
	else if (ft_strlen(cmd) == ft_strlen("export") \
		&& !ft_strncmp(cmd, "export", ft_strlen("export")))
		export(i, shell);
	else if (ft_strlen(cmd) == ft_strlen("unset") \
		&& !ft_strncmp(cmd, "unset", ft_strlen("unset")))
		unset(i, shell);
	else if (ft_strlen(cmd) == ft_strlen("env") \
		&& !ft_strncmp(cmd, "env", ft_strlen("env")))
		env(shell);
	else if (ft_strlen(cmd) == ft_strlen("exit") \
		&& !ft_strncmp(cmd, "exit", ft_strlen("exit")))
		ft_exit(0, shell);
	else
		exec_binary(i, shell);
}

/* create a new process for each command, the parent process waits 
for the child to exec the command */

void	executor(t_minishell *shell)
{
	int			i;
	t_exec		exec;

	i = -1;
	while (shell->number_cmd >= ++i)
	{
		exec.pid = fork();
		if (exec.pid == -1)
			perror("fork error");
		if (exec.pid == 0)
			execution(i, shell);
		else
			waitpid(exec.pid, &exec.tmpret, 0);
	}
	return ;
}
