/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/30 21:08:20 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if empty arg, return 0 fail 1 succes*/
static int	is_valid_operator(char *next_token)
{
	char	*tmp;

	if ((!next_token || is_redirection_or_pipe(next_token[0]))
		&& ft_strlen(next_token) == 1)
	{
		printf("caca\n");
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

static int	is_valid_first_token(t_list *tmp, t_minishell *shell)
{
	int	len;

	len = ft_strlen(tmp->content);
	if (!ft_strncmp(tmp->content, "|", len))
	{
		ft_putendl_fd("minishell : invalid syntax", 2);
		ft_exit_status(258, shell);
		return (1);
	}
	if (len == 1 && !ft_strncmp(tmp->content, ">", 1)
		&& tmp->next && !tmp->next->next)
	{
		open(tmp->next->content, O_RDWR | O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		return (1);
	}
	if (len == 2 && !ft_strncmp(tmp->content, ">>", 2)
		&& tmp->next && !tmp->next->next)
	{
		open(tmp->next->content, O_RDWR | O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		return (1);
	}
	return (0);
}
/*check if after < or pipe is  a readable file, or if empty arg*/
/*int	is_valid2(t_list *tmp, t_minishell *shell)
{

}*/
int	is_valid(t_list *token_lst, t_minishell *shell)
{
	char	*token;
	char	*next_token;
	t_list	*tmp;

	tmp = token_lst;
	if (is_valid_first_token(tmp, shell))
		return (0);
	while (tmp)
	{
	//	if(!is_valid2(tmp, shell))
	//		return (0);
		/*sa commence ici
	
		  sa fini la
		  */
		token = tmp->content;
		if (is_redirection_or_pipe(token[0]) && ft_strlen(token) <= 2)
		{
			next_token = 0;
			if (tmp->next)
				next_token = tmp->next->content;
			if ((!is_valid_operator(next_token) \
					|| !is_valid_redir(token, next_token) \
					|| !is_valid_folder(token)))
			{
				ft_exit_status(2, shell);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
