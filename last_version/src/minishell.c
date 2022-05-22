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

# include "minishell.h"

int g_exit_status = 0;


void   ft_prompt(t_minishell *shell)
{
	char  *pwd;

	pwd = getcwd(NULL, 0);
	shell->prompt = ft_strjoin(pwd, ":~$ ");
	shell->heredoc = 0;
	shell->inf = 0;
	shell->outf = 0;
	free(pwd);
}


int interactive(char **envp)
{
	t_minishell   shell;
	char          *line;
	t_list        *token_list;

	shell.env = init_env(envp);
	shell.envp = set_envp(shell.env);
	while(1)
	{
		ft_signaux("interactive");
		ft_signaux("heredoc");
		ft_prompt(&shell);
		line = readline(shell.prompt);
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			ft_exit(&shell, line, token_list);
		}
		if (!ft_strlen(line))
			continue ;
		add_history(line);
		space_handler(&line);
		token_list=lexer(&shell.env,line);
		if (!is_valid(token_list) || !token_list)    // evite le segfault de la chaine vide
			continue ;
		parser(&token_list, &shell);
		ft_exit(&shell, line, token_list);
		executor(&shell);
		free(line);
		ft_lstclear(&token_list, free);
		free(shell.prompt);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	if(ac > 2)
		non_interactive_mode(av + 2, envp);
	else if (ac == 1)
		interactive(envp);
	else
		usage();
	return (g_exit_status);
}
