/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:59:06 by shamizi           #+#    #+#             */
/*   Updated: 2022/06/01 11:18:38 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *shell)
{
	if (shell->envp)
		freestrings(shell->envp);
	if (shell->inf)
		free(shell->inf);
	if (shell->outf)
		free(shell->outf);
	if (shell->heredoc)
		free(shell->heredoc);
	if (shell->cmds)
		free_minishell2(shell);
	if (shell->env)
		free_env(shell->env);
}

void	ft_exit2(t_minishell *shell, char *line, t_list *token_list)
{
	rl_clear_history();
	if (shell->cmds[0].av[1] && !ft_isstr_num(shell->cmds[0].av[1]))
		ft_putendl_fd("exit\nminishell: exit: numeric argument required", 2);
	free_minishell(shell);
	free(line);
	ft_lstclear(&token_list, free);
	(void )*token_list;
	close(0);
	close(1);
	close(2);
	exit(g_exit_status);
}

// Exit status depending on the arg of exit
void	ft_exit1(t_minishell *shell)
{
	if (ft_isstr_num(shell->cmds[0].av[1]))
		g_exit_status = ft_atoi(shell->cmds[0].av[1]);
	else
		ft_exit_status(2, shell);
	if (g_exit_status > 255)
		ft_exit_status(g_exit_status % 256, shell);
}

int	ft_exit(t_minishell *shell, char *line, t_list *token_list)
{
	if (!line)
	{
		rl_clear_history();
		if (shell->env)
			free_env(shell->env);
		if (shell->envp)
			freestrings(shell->envp);
		ft_putendl_fd("exit", 2);
		exit(g_exit_status);
	}
	if (shell->cmds && ft_strlen(shell->cmds[0].av[0]) == 4
		&& !ft_strncmp(shell->cmds[0].av[0], "exit", 4))
	{
		if (shell->cmds[0].av[1])
			ft_exit1(shell);
		if (shell->cmds->nb_args > 2 && ft_isstr_num(shell->cmds[0].av[1]))
		{
			ft_putendl_fd("exit\nminishell: exit: too many arguments", 2);
			ft_exit_status(1, shell);
			return (1);
		}
		ft_exit2(shell, line, token_list);
	}
	return (0);
}

void	free_minishell2(t_minishell *shell)
{
	int	i;

	i = 0;
	if (shell->cmds->nb_cmds > 1)
	{
		while (i < shell->cmds->nb_cmds)
			freestrings(shell->cmds[i++].av);
		free(shell->cmds);
	}
	else
		freecmds(shell->cmds);
	if (shell->outf)
		free(shell->outf);
	if (shell->inf)
		free(shell->inf);
	if (shell->heredoc)
		free(shell->heredoc);
}
