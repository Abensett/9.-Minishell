/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/22 15:11:04 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if empty arg, return 0 fail 1 succes*/
static int	is_valid_operator(char *next_token)
{
	char	*tmp;

	if (!next_token || is_redirection_or_pipe(next_token[0]))
	{
		tmp = ft_strdup("bash: syntax error near unexpected token `'");
		if (!next_token)
			ft_str_add(&tmp, ft_strlen(tmp) - 1, "newline");
		else if (is_redirection_or_pipe(next_token[0]))
			ft_str_add(&tmp, ft_strlen(tmp) - 1, next_token);
		ft_putendl_fd(tmp, 2);
		free(tmp);
		return (0);
	}
	return (1);
}

/* check if file is openable return 1 if sucess 0 fail*/
static int	is_valid_redir(char *token, char *next_token)
{
	char	*tmp;

	if (token[0] == '<' && ft_strlen(token) == 1 \
			&& open(next_token, O_RDONLY) == -1)
	{
		tmp = ft_strdup("bash: ");
		ft_str_add(&tmp, ft_strlen(tmp), next_token);
		perror(tmp);
		free(tmp);
		return (0);
	}
	return (1);
}

static int	is_valid_folder(char *token)
{
	char	*tmp;

	if (token[0] == '/' && !token[1])
	{
		tmp = ft_strdup("minishell: ");
		perror(tmp);
		free(tmp);
		return (0);
	}
	else if (token[0] == '/')
	{
		tmp = ft_strdup("minishell: ");
		perror(tmp);
		free(tmp);
		return (0);
	}
	return (1);
}
/*check if after < or pipe is  a readable file, or if empty arg*/
int		is_valid(t_list *token_lst)
{
	char	*token;
	char	*next_token;
	t_list	*tmp;

	tmp = token_lst;
	while (tmp)
	{
		token = tmp->content;
		if (is_redirection_or_pipe(token[0]))
		{
			next_token = 0;
			if (tmp->next)
				next_token = tmp->next->content;
			if (!is_valid_operator(next_token) \
					|| !is_valid_redir(token, next_token) \
					|| !is_valid_folder(token))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}