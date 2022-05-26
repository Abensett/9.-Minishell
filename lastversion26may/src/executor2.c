/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:06:29 by abensett          #+#    #+#             */
/*   Updated: 2022/05/25 17:27:49 by abensett         ###   ########.fr       */
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
