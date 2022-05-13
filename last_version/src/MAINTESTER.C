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

void	free_minishell(t_minishell *shell)
{
	int		i;
	int		j;

	if (shell->outf)
		free(shell->outf);
	if (shell->inf)
		free(shell->inf);
	if (shell->heredoc)
		free(shell->heredoc);
	i = 0;
	while (shell->cmds[i].av)
	{
		j = 0;
		while (shell->cmds[i].av && shell->cmds[i].av[j])
			free(shell->cmds[i].av[j++]);
		i++;
	}
}
void   ft_prompt(t_minishell *shell)
{
	char  *pwd;

	pwd = getcwd(NULL, 0);
	shell->prompt = ft_strjoin(pwd, ":~$ ");
  shell->heredoc = 0;
	shell->inf = 0;
	shell->outf = 0;
}


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
  char          *line;
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
  if (!is_valid(token_list))
     exit(1);
  parser(&token_list, &shell);
  executor(&shell);
}

int main(int ac, char **av, char **envp)
{
  t_minishell   shell;
  char          *line;
  t_list        *token_list;

  shell.env = init_env(envp);
  shell.envp = set_envp(shell.env);
  if (signal(SIGINT, ft_signals) == SIG_ERR || signal(SIGQUIT, ft_signals) == SIG_ERR)
	    perror("signal error");
  if(ac > 2)
    		non_interactive_mode(av + 2, envp);
  else if (ac == 1)
  {
      while(1)
      {
          ft_prompt(&shell);
          line = readline(shell.prompt);
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
          if (!is_valid(token_list))
              continue ;
          parser(&token_list, &shell);
          executor(&shell);
          free(line);
          ft_lstclear(&token_list, free);
          free(shell.prompt);
      }
      rl_clear_history();
      (void)ac;
      (void)av;
      (void)env;
      free_minishell(&shell);
      free(shell.envp);
  }
  else
    usage();
  return (0);
}
