/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/28 09:28:21 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*if first quote turn quote into it else if quote = c then quote = 0 */
void	type_quote(char *quote, char c)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

/* return number of args separated by ' " or space*/
static int	arg_len(char *line)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				++ret;
			while (*line && *line != ' ')
				type_quote(&quote, *line++);
		}
		else
			++line;
	}
	return (ret);
}

/* put args into str array = tokens */
static int	arg_list_create(char ***token_array, char *line)
{
	int		len;
	char	quote;
	int		i;

	*token_array = malloc(sizeof(char *) * (arg_len(line) + 1));
	if (!(*token_array))
		return (0);
	quote = 0;
	i = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				len = 0;
			while (*line && *line != ' ' && ++len)
				type_quote(&quote, *line++);
			if (!quote)
				(*token_array)[i++] = ft_substr(line - len, 0, len);
		}
		else if (++line && quote)
			++len;
	}
	(*token_array)[i] = 0;
	return (i);
}

/*r remove quotes, expand and turn line into t_list*/
t_list	*lexer(t_env_list **env, char *line)
{
	int		len;
	char	**token_array;
	t_list	*tokens;
	t_list	*tmp;

	tokens = 0;
	len = arg_list_create(&token_array, line);
	while (len--)
	{
		quote_remove(env, &token_array[len]);
		tmp = ft_lstnew(token_array[len]);
		if (ft_strlen(token_array[len]) != 0)
			ft_lstadd_front(&tokens, tmp);
	}
	free(token_array);
	return (tokens);
}
