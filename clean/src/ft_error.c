/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/06/01 09:01:02 by abensett         ###   ########.fr       */
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

/* 1: exit_status = i
	2 : add new exit_status to env*/
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

/* close stdin stdout */
int	store_fd_close(int tmpin, int tmpout)
{
	g_exit_status = 1;
	close(tmpin);
	close(tmpout);
	return (-1);
}
