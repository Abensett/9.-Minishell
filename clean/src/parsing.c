/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/06/01 09:10:31 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return len of *tkn_list*/
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

/* skip << and store delimiter in shell->heredoc / if next go next command */
static void	delimit_heredoc(t_list **tkn_list, t_minishell *shell, t_list *ret)
{
	ret = *tkn_list;
	if (tokens_counter(*tkn_list) < 2)
		return ;
	if (!ft_strncmp("<<", (*tkn_list)->content, ft_strlen((*tkn_list)->content))
		&& (ft_strlen((*tkn_list)->content) == ft_strlen("<<")))
	{
		ret = (*tkn_list)->next;
		shell->heredoc = ft_strdup((*tkn_list)->next->content);
		free(*tkn_list);
		if (ret->next)
			*tkn_list = ret->next;
		else
			*tkn_list = NULL;
	}
	else if (!ft_strncmp("<<", (*tkn_list)->next->content,
			ft_strlen((*tkn_list)->next->content))
		&& (ft_strlen((*tkn_list)->next->content) == ft_strlen("<<")))
	{
		shell->heredoc = ft_strdup((*tkn_list)->next->next->content);
		ret = (*tkn_list)->next->next->next;
		ft_lstdelone((*tkn_list)->next->next, free);
		ft_lstdelone((*tkn_list)->next, free);
		(*tkn_list)->next = ret;
	}
}

/* store path infile if <  */
void	get_infile(t_list **tkn_list, t_minishell *shell)
{
	t_list	*tmp;

	tmp = *tkn_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "<<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<<"))
			return ;
		if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) == 0
			&& ft_strlen(tmp->content) == ft_strlen("<"))
		{
			if (tmp->next)
			{
				shell->inf = ft_strdup(tmp->next->content);
				if ((*tkn_list)->next->next && !ft_strncmp((*tkn_list)->content,
						"<", ft_strlen(tmp->content)))
					*tkn_list = (*tkn_list)->next->next;
			}
		}
		tmp = tmp->next;
	}
}

/* store path outfile, append =1 if >>*/
void	get_outfile(t_list *tkn_list, t_minishell *shell)
{
	t_list	*tmp;

	tmp = tkn_list;
	shell->append = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, ">>", ft_strlen(tmp->content)))
		{
			if (!ft_strncmp(tmp->content, ">", ft_strlen(tmp->content))
				&& tmp->next)
				close(open(tmp->next->content, O_RDWR | O_CREAT | O_TRUNC,
						S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP));
			if (!ft_strncmp(tmp->content, ">>", ft_strlen(tmp->content))
				&& tmp->next)
				close(open(tmp->next->content, O_RDWR | O_CREAT | O_APPEND,
						S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP));
			if (ft_strncmp(tmp->content, ">", ft_strlen(tmp->content)))
				shell->append = 1;
			if (tmp->next)
			{
				if (shell->outf)
					free(shell->outf);
				shell->outf = ft_strdup(tmp->next->content);
			}
		}
		tmp = tmp->next;
	}
}

void	parser(t_list **tkn_list, t_minishell *shell)
{
	int		i;
	int		j;
	t_list	*ret;

	ret = 0;
	delimit_heredoc(tkn_list, shell, ret);
	get_outfile(*tkn_list, shell);
	get_infile(tkn_list, shell);
	shell->cmds = pipe_separation(tkn_list, shell);
	i = 0;
	while (i <= shell->number_cmd)
	{
		j = 0;
		while (shell->cmds[i].av[j])
			quote_remove_after(&shell->env, &shell->cmds[i].av[j++]);
		i++;
	}
}
