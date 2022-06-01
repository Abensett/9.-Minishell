/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:05 by abensett          #+#    #+#             */
/*   Updated: 2022/05/30 21:42:51 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	ft_prompt(t_minishell *shell, char **line)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	shell->prompt = ft_strjoin(pwd, ":~$ ");
	shell->heredoc = 0;
	shell->inf = 0;
	shell->outf = 0;
	free(pwd);
	*line = readline(shell->prompt);
	free(shell->prompt);
}

void	ft_init_shell(t_minishell *shell, char **envp)
{
	shell->env = init_env(envp);
	shell->envp = set_envp(shell->env);
	ft_exit_status(g_exit_status, shell);
}

int	interactive(t_minishell *shell)
{
	char		*line;
	t_list		*token_list;

	while (1)
	{
		ft_signaux("interactive");
		ft_prompt(shell, &line);
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			ft_exit(shell, line, token_list);
		}
		if (!ft_strlen(line) || quote_check(&line))
			continue ;
		add_history(line);
		token_list = lexer(&shell->env, line);
		if (!is_valid(token_list, shell) || !token_list)
			continue ;
		parser(&token_list, shell);
		if (ft_exit(shell, line, token_list))
			continue ;
		executor(shell);
		ft_free(shell, line, token_list);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	shell;

	(void)av;
	if (!*envp)
	{
		printf("No environment found\n");
		return (1);
	}
	else if (ac == 1)
	{
		ft_init_shell(&shell, envp);
		interactive(&shell);
	}
	else
		printf("./minishell without any arg (for interactive mode)\n");
	return (g_exit_status);
}
