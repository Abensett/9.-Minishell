/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 08:18:39 by abensett          #+#    #+#             */
/*   Updated: 2022/05/07 15:26:43 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*return count=nb of args: count till pipe or rediction is found*/
int	args_counter(t_list *token_list)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = token_list;
	while (tmp && tmp->content)
	{
		if (ft_strlen(tmp->content) == 1
			&& (ft_strncmp(tmp->content, "|", ft_strlen(tmp->content)) == 0 \
			|| ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)) == 0))
			return (count);
		if (ft_strlen(tmp->content) == 2
			&& ft_strncmp(tmp->content, ">>", 2) == 0)
			return (count);
        if (ft_strlen(tmp->content) == 2
			&& ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0)
			count -= 2;
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*fill cmds with token list */
t_simple_command	*fill_cmds(t_list *token_list, t_simple_command *cmds, t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token_list && ft_strncmp(token_list->content, ">", 1) != 0)
	{
		if (ft_strncmp(token_list->content, "|", ft_strlen(token_list->content)) == 0)
		{
			i++;
			cmds[i].av = malloc(sizeof(char *)
					* (args_counter(token_list->next) + 1));
			j = 0;
			token_list = token_list->next;
		}
		cmds[i].av[j] = ft_strdup(token_list->content);
		cmds[i].nb_args = ++j;
		cmds[i].av[j] = 0;
		token_list = token_list->next;
	}
	shell->number_cmd = i;
	return (cmds);
}
