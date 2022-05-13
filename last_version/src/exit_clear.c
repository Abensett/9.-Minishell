/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/12 17:27:23 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *shell)
{
	// int		i;
	// int		j;

	if (shell->outf)
		free(shell->outf);
	if (shell->inf)
		free(shell->inf);
	if (shell->heredoc)
		free(shell->heredoc);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->env)
		free(shell->env);

	// i = 0;

	// while (shell->cmds[i].av)
	// {
	// 	j = 0;
	// 	while(shell->cmds[i].av && shell->cmds[i].av[j])
	// 		free(shell->cmds[i].av[j++]);
	// 	i++;
	// }
	free(shell->envp);
}

int	ft_exit(t_minishell *shell, char *line, t_list *token_list)
{

	if (!line)
	{
		rl_clear_history();
		free_minishell(shell);
		exit(g_exit_status);
	}
	if (ft_strlen(shell->cmds[0].av[0]) == 4
		&& !ft_strncmp(shell->cmds[0].av[0], "exit", 4))
	{
		if (shell->cmds[0].av[1])
			g_exit_status = ft_atoi(shell->cmds[0].av[1]);
		rl_clear_history();
		free_minishell(shell);
		free(line);
		ft_lstclear(&token_list, free);
		ft_putendl_fd("exit", 1);
		exit(g_exit_status);
	}
	return (0);
}


int	cd(int i, t_minishell *shell)
{
	(void)i;
	(void)shell;
	return (0);
}
