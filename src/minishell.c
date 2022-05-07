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

#include "minishell.h"

void	ft_signals(int sig)
{
	if (sig == SIGINT)
	   ft_putchar_fd('\n', 1);
  rl_replace_line("", 0);
  rl_on_new_line();

	rl_redisplay();
}

char  *ft_prompt(void)
{
  char  *pwd;

	pwd = getcwd(NULL, 0);
  pwd = ft_strjoin(pwd, ":~$ ");
  return (pwd);
}

int main(int ac, char **av, char **envp)
{
  t_minishell   shell;
  char          *line;
  char          *pwd;
  t_list        *token_list;

  shell.env = init_env(envp);
  shell.envp = set_envp(shell.env);
  if (signal(SIGINT, ft_signals) == SIG_ERR || signal(SIGQUIT, ft_signals) == SIG_ERR)
	    perror("signal error");

  while(1)
  {
      pwd = ft_prompt();
      line = readline(pwd);
      if ((!ft_strncmp("exit", line, 4) && ft_strlen(line) == 4) || !line)
        break;
      if (!ft_strlen(line))
		  	continue ;
      if (!line)
	  	{
		    	ft_putendl_fd("unexpected end of file", 2);
		    	continue ;
		  }
      add_history(line);
      space_handler(&line);
      token_list=lexer(&shell.env,line);
      parser(&token_list, &shell);
      // printf("OHH \n" );
      // shell.cmds = malloc(sizeof(t_simple_command) * 1);

      // char *tmp;
      // char *line1;
      // char *line2;
	    // tmp = ft_strchr(line, ' ');
      // if(ft_strlen(tmp))
        
      // line2 = ft_strdup(tmp + 1);
      // line1 = ft_substr(line, 0, ft_strlen(line) - ft_strlen(tmp));

      // shell.cmds[0].av = malloc(sizeof(char *)*3);
      // // printf("OHH \n" );

      // shell.cmds[0].av[0] = ft_strdup(line1);
      // shell.cmds[0].av[1] = ft_strdup(line2);
      // shell.number_cmd = 1;
      // printf("OHH \n" );
      // printf("OHH %d \n", shell.number_cmd);

      executor(&shell);
      free(line);
  }
  rl_clear_history();  
  (void)ac;
  (void)av;
  (void)env;
  return (0);
}