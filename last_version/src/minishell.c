/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:05 by abensett          #+#    #+#             */
/*   Updated: 2022/05/26 15:16:53 by shamizi          ###   ########.fr       */
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
	//set_env(&shell, "?=0");
	while(1)
	{
		ft_signaux("interactive");
		ft_prompt(&shell);
		line = readline(shell.prompt);
		free(shell.prompt);
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			ft_exit(&shell, line, token_list);
		}
		if (!ft_strlen(line) || quote_check(&line))
			continue ;
		add_history(line);
		space_handler(&line);
		token_list=lexer(&shell.env,line);
		if (!is_valid(token_list) || !token_list)    // evite le segfault de la chaine vide
			continue ;
		parser(&token_list, &shell);
		ft_exit(&shell, line, token_list);
		executor(&shell);
		ft_free(&shell, line, token_list);
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
