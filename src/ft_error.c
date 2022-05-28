/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/27 00:44:33 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*exit if fork failed or any other function and print error msg*/
void	ft_error(int i, char *str)
{
	if (i == -1)
	{
		perror(str);
		exit(1);
	}
}

void	ft_exit_status(int i, t_minishell *shell)
{
	char	*g_exit_status_env;
	char	*tmp;

	tmp = ft_itoa(g_exit_status);
	g_exit_status_env = ft_strjoin("?=", tmp);
	g_exit_status = i;
	unset_env(shell, "?");
	set_env(shell, g_exit_status_env);
	free(g_exit_status_env);
	free(tmp);
}
