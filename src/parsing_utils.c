/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 08:18:39 by abensett          #+#    #+#             */
/*   Updated: 2022/05/31 18:10:45 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return count=nb of cmds, when str is found + 1*/
int	cmd_counter(char *str, t_list *token_list)
{
	int	count;

	count = 0;
	while (token_list)
	{
		if (ft_strncmp(token_list->content, str, ft_strlen(str)) == 0
			&& ft_strlen(token_list->content) == ft_strlen(str))
			count++;
		token_list = token_list->next;
	}
	return (count);
}

/*return array of simple_commands*/
t_simple_command	*pipe_separation(t_list **token_list, t_minishell *shell)
{
	t_simple_command	*cmds;
	t_list				*tmp;

	tmp = *token_list;
	cmds = malloc(sizeof(t_simple_command) * (cmd_counter("|", tmp) + 2));
	if (!cmds)
		return (NULL);
	cmds[0].av = malloc(sizeof(char *) * (args_counter(tmp) + 1));
	if (!cmds[0].av)
		return (NULL);
	cmds->nb_cmds = cmd_counter("|", tmp) + 1;
	cmds = fill_cmds(tmp, cmds, shell);
	return (cmds);
}
// cmds->nb_cmds = 0;
//
// cmds[0].av = malloc(sizeof(char *) * (args_counter(tmp) + 1));

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

int	jump_redirection(t_list **tk)
{
	while ((*tk)
		&& (!ft_strncmp((*tk)->content, ">", ft_strlen((*tk)->content))
			|| !ft_strncmp((*tk)->content, "<", ft_strlen((*tk)->content))
			|| !ft_strncmp((*tk)->content, ">>", ft_strlen((*tk)->content))))
	{
		*tk = (*tk)->next->next;
		if (!*tk)
			return (1);
	}
	return (0);
}

/*fill cmds with token list | j'ai changer le nom token_list
 en tolist pour la norme */
t_simple_command	*fill_cmds(t_list *tk, t_simple_command *cmds,
					t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tk)
	{
		if (jump_redirection(&tk))
			break ;
		if (!ft_strncmp(tk->content, "|", ft_strlen(tk->content)))
		{
			i++;
			cmds[i].av = malloc(sizeof(char *)
					* (args_counter(tk->next) + 1));
			j = 0;
			tk = tk->next;
		}
		cmds[i].av[j] = ft_strdup((char *)tk->content);
		cmds[i].nb_args = ++j;
		cmds[i].av[j] = 0;
		tk = tk->next;
	}
	shell->number_cmd = i;
	return (cmds);
}
