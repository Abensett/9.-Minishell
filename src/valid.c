/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/09 12:07:48 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	is_valid_operator(char *next_token)
{
	char	*tmp;

	if (!next_token || is_metachar(next_token[0]))
	{
		tmp = ft_strdup("minishell: syntax error near unexpected token `'");
		if (!next_token)
			ft_str_add(&tmp, ft_strlen(tmp) - 1, "newline");
		else if (is_metachar(next_token[0]))
			ft_str_add(&tmp, ft_strlen(tmp) - 1, next_token);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		return (0);
	}
	return (1);
}

static int	is_valid_in_redir(char *token, char *next_token)
{
	char	*tmp;

	if (token[0] == '<' && ft_strlen(token) == 1 \
			&& open(next_token, O_RDONLY) == -1)
	{
		tmp = ft_strdup("minishell: ");
		ft_str_add(&tmp, ft_strlen(tmp), next_token);
		perror(tmp);
		free(tmp);
		return (0);
	}
	return (1);
}

int		is_valid(t_list *token_lst)
{
	char	*token;
	char	*next_token;
	t_list	*tmp;

	tmp = token_lst;
	while (tmp)
	{
		token = tmp->content;
		if (is_metachar(token[0]))
		{
			next_token = 0;
			if (tmp->next)
				next_token = tmp->next->content;
			if (!is_valid_operator(next_token) \
					|| !is_valid_in_redir(token, next_token))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}