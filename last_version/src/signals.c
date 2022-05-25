/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/24 18:53:14 by abensett         ###   ########.fr       */
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

void	ft_signals_command(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = sig + 128;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 0);
		g_exit_status = sig + 128;
		return ;
	}
}

void	ft_signals_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else if (sig == SIGQUIT)
	 	return ;
}

void	ft_signaux(char *mode)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_slash;

	ctrl_c.sa_flags = 0;
	ctrl_slash.sa_flags = 0;
	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ft_memset(&ctrl_slash, 0, sizeof(ctrl_slash));
	if (!ft_strncmp(mode,"heredoc",8))
	{
		// printf("hehe\n");
		ctrl_c.sa_handler = &ft_signals_here_doc;
		ctrl_slash.sa_handler = SIG_IGN;
	}
	else if (!ft_strncmp(mode,"command",8))
	{
		// printf("cmd\n");
		ctrl_c.sa_handler = &ft_signals_command;
		ctrl_slash.sa_handler = &ft_signals_command;
	}
	else if (!ft_strncmp(mode,"interactive",12))
	{
		// printf("interactive\n");
		ctrl_c.sa_handler = &ft_signals;
		ctrl_slash.sa_handler = SIG_IGN;
	}
	sigaction(SIGINT, &ctrl_c, 0);
	sigaction(SIGQUIT, &ctrl_slash, 0);
}
