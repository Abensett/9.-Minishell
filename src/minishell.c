/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:05 by abensett          #+#    #+#             */
/*   Updated: 2022/04/11 22:36:45 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals(int sig)
{
	if (sig == SIGINT)
	  ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int argc, char **av, char **env)
{
  char  *line;
  char *pwd;

	pwd = getcwd(NULL, 0);
  pwd = ft_strjoin(pwd, ":~$ ");
  if (signal(SIGINT, ft_signals) == SIG_ERR || signal(SIGQUIT, ft_signals) == SIG_ERR)
	    perror("signal error");
  while(1)
  {
      line = readline(pwd);
      if ((!ft_strncmp("exit", line, 4) && ft_strlen(line) == 4) || !line)
        break;
      add_history(line);
  }
  rl_clear_history();  
  return (0);
}