/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/01 06:26:40 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_minishell *shell)
{
	t_env_list		*tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("%s\n", tmp->all);
		tmp = tmp->next;
	}
}

void	ft_exit(int i, t_minishell *shell)
{
	(void)i;
	(void)shell;
}
