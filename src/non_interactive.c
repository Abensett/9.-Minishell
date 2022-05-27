/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:54:28 by abensett          #+#    #+#             */
/*   Updated: 2022/05/27 03:44:18 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	usage(void)
{
	printf("USAGE:\n");
	printf("./minishell (for interactive mode)\n");
	printf("./minishell -c [command] (for non-interactive mode)\n");
	return (1);
}

/* Pour lancer minishell en mode non interactif :
 * ./minishell -c "commande a executer" */

void	non_interactive_mode(char **array, char **env)
{
	t_minishell	shell;
  char          *line = NULL; 
  t_list        *token_list;

  shell.env = init_env(env);
  shell.envp = set_envp(shell.env);
  shell.heredoc = 0;
	shell.inf = 0;
	shell.outf = 0;


  while (*array)
  {
    line = ft_strjoin(line, *array);
    array++;
  }
  space_handler(&line);
  token_list=lexer(&shell.env,line);
  if (!is_valid(token_list, &shell))
     exit(2);
  parser(&token_list, &shell);
  executor(&shell);
  free_minishell(&shell);
}
