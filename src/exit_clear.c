/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/31 13:40:10 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//toujour des trucs pas free ici
void	free_env(t_env_list *env)
{
	t_env_list *tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		if (env->all)
			free(env->all);
		if (env)
			free(env);
		env = tmp;
	}
	free(tmp);
}


void	free_minishell(t_minishell *shell)
{
	//	if(shell->prompt)
	//		free(shell->prompt);
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
	// if(shell->cmds)
	// 	freecmds(shell->cmds);
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
	if ( shell->cmds && ft_strlen(shell->cmds[0].av[0]) == 4
			&& !ft_strncmp(shell->cmds[0].av[0], "exit", 4))
	{
		if (shell->cmds[0].av[1])
		{
			if(ft_isstr_num(shell->cmds[0].av[1]))
				g_exit_status = ft_atoi(shell->cmds[0].av[1]);
			else
				ft_exit_status(2, shell);
			if(g_exit_status > 255)
				ft_exit_status(g_exit_status % 256, shell);
		}
		if (shell->cmds->nb_args > 2 && ft_isstr_num(shell->cmds[0].av[1]))
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			ft_exit_status(1, shell);
			return(1);
		}
		(void )*token_list;
		// ft_free(shell, line, token_list);
		// rl_clear_history();
		// free_minishell(shell);
		// free(line);
		// ft_lstclear(&token_list, free);
		ft_putendl_fd("exit", 2);
		ft_exit_status(g_exit_status % 256, shell);
		exit(g_exit_status);
	}
	return (0);
}


void	free_minishell2(t_minishell *shell)
{
	int i = 0;
	t_env_list *tmp;

	tmp = shell->env;
	// if(shell->cmds->nb_cmds > 1)
	// {
	// 	while(i < shell->cmds->nb_cmds)
	// 		freestrings(shell->cmds[i++].av);
	// 	free(shell->cmds);
	// }
	// else
	// 	freecmds(shell->cmds);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	/*int j = 0;
	while (j < i)
	{
	}
	free(shell->env);*/

}


void	ft_free(t_minishell *shell, char *line, t_list *token_list)
{
	//rl_clear_history();
	if (!line)
		printf("je tente pas de free\n");
	else
	{
		//if (shell->cmds[0].av[1])
		//	g_exit_status = ft_atoi(shell->cmds[0].av[1]);
		free_minishell2(shell);
		free(line);
		ft_lstclear(&token_list, free);
	}
}
