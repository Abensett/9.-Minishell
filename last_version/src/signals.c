/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/12 16:31:21 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	ft_signals_non_interactif(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signaux(char *mode)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_slash;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ft_memset(&ctrl_slash, 0, sizeof(ctrl_slash));
	if (!ft_strncmp(mode,"interactive",5))
	{
		ctrl_c.sa_handler = &ft_signals;
		ctrl_c.sa_flags = 0;
		ctrl_slash.sa_handler = SIG_IGN;
		ctrl_slash.sa_flags = 0;
	}
	sigaction(SIGINT, &ctrl_c, 0);
	sigaction(SIGQUIT, &ctrl_slash, 0);
}
