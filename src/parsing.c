/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/29 18:09:43 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return len of *token_list*/
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

/* skip << and store delimiter  */
static void	delimit_heredoc(t_list **token_list, t_minishell *shell)
{
	t_list	*ret;

	ret = *token_list;
	if (tokens_counter(*token_list) < 2)
		return ;
	if (ft_strncmp("<<", (*token_list)->content,
			ft_strlen((*token_list)->content)) == 0
		&& (ft_strlen((*token_list)->content) == ft_strlen("<<")))
	{
		ret = (*token_list)->next;
		shell->heredoc = ft_strdup((*token_list)->next->content);
		free(*token_list);
		if (ret->next)
			*token_list = ret->next;
		else
			*token_list = NULL;
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

/* store path infile */
void	get_infile(t_list **token_list, t_minishell *shell)
{
	t_list	*tmp;

	tmp = *token_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<<"))
			return ;
		if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<"))
			if (tmp->next)
			{
				shell->inf = ft_strdup(tmp->next->content);
				if((*token_list)->next->next &&
					!ft_strncmp((*token_list)->content, "<", ft_strlen(tmp->content)))
					*token_list = (*token_list)->next->next;
				// printf("tokenlist %s \n", (char*)(*token_list)->content);
			}
		tmp = tmp->next;
	}
}

/* store path outfile, append  if */
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
			if (tmp->next)
				shell->outf = ft_strdup(tmp->next->content);
		}
		tmp = tmp->next;
	}
}

void	parser(t_list **token_list, t_minishell *shell)
{
	delimit_heredoc(token_list, shell);
	get_outfile(*token_list, shell);
	get_infile(token_list, shell);
	// printf("tokenlist %s \n", (char*)(*token_list)->content);

	shell->cmds = pipe_separation(token_list, shell);
}
