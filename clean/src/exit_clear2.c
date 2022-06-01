/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:59:06 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/31 21:33:21 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freestrings(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	freecmds(t_simple_command *cmds)
{
	if (!cmds)
		return ;
	if (cmds->av)
		freestrings(cmds->av);
	free(cmds);
}

void	free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		if (env->all)
			free(env->all);
		if (env)
			free(env);
		env = tmp;
	}
	free(env);
}

void	ft_free(t_minishell *shell, char *line, t_list *token_list)
{
	if (!line)
		printf("je tente pas de free\n");
	else
	{
		unset_env(shell, "?");
		free_minishell2(shell);
		free(line);
		ft_lstclear(&token_list, free);
	}
}
