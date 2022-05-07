/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 08:18:39 by abensett          #+#    #+#             */
/*   Updated: 2022/05/07 13:29:10 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*return count=nb of cmds, when pipe is found +1*/
int	cmd_counter(char *str, t_list *token_lst)
{
	int	count;

	count = 0;
	while (token_lst)
	{
		if (ft_strncmp(token_lst->content, str, ft_strlen(str)) == 0
			&& ft_strlen(token_lst->content) == ft_strlen(str))
			count++;
		token_lst = token_lst->next;
	}
	return (count);
}

/*return array of simple_commands*/
t_simple_command	*pipe_separation(t_list **token_list, t_minishell *shell)
{
	t_simple_command	*cmds;
	t_list				*tmp;

	tmp = *token_list;
	// if (ft_strncmp(tmp->content, "<", 1) == 0)
	// 	tmp = tmp->next->next; 
	cmds = malloc(sizeof(t_simple_command) * (cmd_counter("|", tmp) + 2));
	cmds[0].av = malloc(sizeof(char *) * (args_counter(tmp) + 1));
	cmds = fill_cmds(tmp, cmds, shell);
	return (cmds);
}

void	parser(t_list **token_list, t_minishell *shell)
{

	shell->cmds = pipe_separation(token_list, shell);
}