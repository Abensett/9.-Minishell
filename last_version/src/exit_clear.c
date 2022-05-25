/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/25 14:40:09 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	free_minishell(t_minishell *shell)
  {
// int		i;
// int		j;

// if (shell->outf)
// 	free(shell->outf);
// if (shell->inf)
// 	free(shell->inf);
// if (shell->heredoc)
// 	free(shell->heredoc);
// if (shell->prompt)
// 	free(shell->prompt);
// if (shell->env)
// 	free(shell->env);

// i = 0;
// if (i < shell->number_cmd)
// {	
// 	while (shell->cmds[i].av)
// 	{
// 		j = 0;
// 		while(shell->cmds[i].av && shell->cmds[i].av[j])
// 			free(shell->cmds[i].av[j++]);
// 		i++;
// 	}
// }
free(shell->envp);
}*/

void	freestrings(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	freecmds(t_simple_command *cmds)
{
	if (!cmds)
		return ;
	if (cmds->av)
		freestrings(cmds->av);
	free(cmds);
}

void	free_env(t_env_list *env)
{
	t_env_list *tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		if (env->all)
			free(env->all);
		free(env);
		env = tmp;
	}
}


void	free_minishell(t_minishell *shell)
{
	if(shell->prompt)
		free(shell->prompt);
	if(shell->envp)
		freestrings(shell->envp);
//	if(shell->paths)
//		freestrings(shell->paths);
	if(shell->inf)
		free(shell->inf);
	if(shell->outf)
		free(shell->outf);
	if(shell->heredoc)
		free(shell->heredoc);
	if(shell->cmds)
		freecmds(shell->cmds);
	if (shell->env)
		free_env(shell->env);
	//free(shell);
}

int	ft_exit(t_minishell *shell, char *line, t_list *token_list)
{
	if (!line)
	{
		rl_clear_history();
		free_minishell(shell); 
		exit(g_exit_status);
	}
	if (ft_strlen(shell->cmds[0].av[0]) == 4
			&& !ft_strncmp(shell->cmds[0].av[0], "exit", 4))
	{
		if (shell->cmds[0].av[1])
			g_exit_status = ft_atoi(shell->cmds[0].av[1]);
		rl_clear_history();
		free_minishell(shell);
		free(line);
		ft_lstclear(&token_list, free);
		ft_putendl_fd("exit", 1);
		exit(g_exit_status);
	}
	return (0);
}

