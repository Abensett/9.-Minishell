/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 08:18:39 by abensett          #+#    #+#             */
/*   Updated: 2022/05/09 12:04:56 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return count=nb of cmds, when pipe is found +1*/
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
	if (ft_strncmp(tmp->content, "<", 1) == 0)
	 	tmp = tmp->next->next; 
	cmds = malloc(sizeof(t_simple_command) * (cmd_counter("|", tmp) + 2));
	cmds[0].av = malloc(sizeof(char *) * (args_counter(tmp) + 1));
	cmds = fill_cmds(tmp, cmds, shell);
	return (cmds);
}

int	tokens_counter(t_list *token_lst)
{
	int	i;

	i = 0;
	while (token_lst)
	{
		token_lst = token_lst->next;
		i++;
	}
	return (i);
}

static void	skip_heredoc(t_list **token_list, t_minishell *shell)
{
	t_list	*ret;

	ret = *token_list;
	if (tokens_counter(*token_list) < 3)
		return ;
	if (ft_strncmp("<<", (*token_list)->content,
			ft_strlen((*token_list)->content)) == 0
		&& (ft_strlen((*token_list)->content) == ft_strlen("<<")))
	{
		ret = (*token_list)->next->next;
		shell->heredoc = ft_strdup((*token_list)->next->content);
		free((*token_list)->next);
		free(*token_list);
		*token_list = ret;
	}
	else if (ft_strncmp("<<", (*token_list)->next->content,
			ft_strlen((*token_list)->next->content)) == 0
		&& (ft_strlen((*token_list)->next->content) == ft_strlen("<<")))
	{
		shell->heredoc = ft_strdup((*token_list)->next->next->content);
		ret = (*token_list)->next->next->next;
		ft_lstdelone((*token_list)->next->next, free);
		ft_lstdelone((*token_list)->next, free);
		(*token_list)->next = ret;
	}
}

void	get_infile(t_list *token_list, t_minishell *shell)
{
	t_list	*tmp;

	tmp = token_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<<"))
			return ;
		if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<"))
		{
			// while(tmp->next)
			// 	tmp = tmp->next;
			shell->inf = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
}

void	get_outfile(t_list *token_list, t_minishell *shell)
{
	t_list	*tmp;

	tmp = token_list;
	shell->append = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, ">>", ft_strlen(tmp->content)))
		{
			if (ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)))
				shell->append = 1;
			shell->outf = ft_strdup(tmp->next->content);
		}
		tmp = tmp->next;
	}
}

void	parser(t_list **token_list, t_minishell *shell)
{
	get_outfile(*token_list, shell);
	get_infile(*token_list, shell);
	skip_heredoc(token_list, shell);
	shell->cmds = pipe_separation(token_list, shell);
}