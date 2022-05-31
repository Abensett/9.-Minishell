/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 00:52:39 by abensett          #+#    #+#             */
/*   Updated: 2022/05/31 16:16:11 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

/*create the path we need to exec our binary file with execve(PATHS,CMD,ENVP)*/
char	**make_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**all_paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
		i++;
	all_paths = malloc(sizeof(char *) * (i + 2));
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
		all_paths[i] = ft_strjoin(paths[i], cmd);
	all_paths[i] = cmd;
	all_paths[i + 1] = 0;
	return (all_paths);
}

int	exec_binary(int num, t_minishell *shell)
{
	int			i;

	execve(shell->cmds[num].av[0], shell->cmds[num].av, shell->envp);
	shell->paths = make_paths(shell->cmds[num].av[0], shell->envp);
	i = -1;
	if (!shell->paths)
	{
		ft_putendl_fd("bash: cmd : No such file or directory", 2);
		exit(127);
	}
	while (shell->paths[++i])
		execve(shell->paths[i], shell->cmds[num].av, shell->envp);
	perror("cmd");
	exit(127);
}
