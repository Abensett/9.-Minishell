/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/06/01 12:28:54 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return first quote between ' and " */
char	find_first_quote(char *line)
{
	char	*str[2];
	char	quote;

	str[0] = ft_strchr(line, '"');
	str[1] = ft_strchr(line, '\'');
	quote = 0;
	if (!str[0] && str[1])
		quote = '\'';
	else if (str[0] && !str[1])
		quote = '"';
	else if (str[0] && str[1])
	{
		if (ft_strlen(str[0]) > ft_strlen(str[1]))
			quote = '"';
		else
			quote = '\'';
	}
	return (quote);
}

int	is_quoted_redirection(char *line)
{
	if ((!ft_strncmp(line, "'<'", ft_strlen(line))
			|| !ft_strncmp(line, "'>'", ft_strlen(line))
			|| !ft_strncmp(line, "'| '", ft_strlen(line))
			|| !ft_strncmp(line, "'< '", ft_strlen(line))
			|| !ft_strncmp(line, "'> '", ft_strlen(line))
			|| !ft_strncmp(line, "'|'", ft_strlen(line))
			|| !ft_strncmp(line, "\"< \"", ft_strlen(line))
			|| !ft_strncmp(line, "\"> \"", ft_strlen(line))
			|| !ft_strncmp(line, "\"| \"", ft_strlen(line))
			|| !ft_strncmp(line, "\"<\"", ft_strlen(line))
			|| !ft_strncmp(line, "\">\"", ft_strlen(line))
			|| !ft_strncmp(line, "\"|\"", ft_strlen(line))
			|| !ft_strncmp(line, "\">>\"", ft_strlen(line))
			|| !ft_strncmp(line, "\">>\"", ft_strlen(line))
			|| !ft_strncmp(line, "\"<<\"", ft_strlen(line))
			|| !ft_strncmp(line, "\">>\"", ft_strlen(line)))
		&& ft_strlen(line) > 1)
		return (1);
	return (0);
}

/*remove quote and expand what's not between ' ' */
void	quote_remove(t_env_list **env, char **line)
{
	int		i;
	char	quote;
	int		look_for_quote;

	i = -1;
	quote = 0;
	look_for_quote = 0;
	while ((*line)[++i])
	{
		if (is_quoted_redirection((*line)) && ft_strlen(*line) > 2)
			continue ;
		if (!look_for_quote)
			quote = find_first_quote(&((*line)[i]));
		if (quote != '\'' && (*line)[i] == '$'
			&& (ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?'))
			expansion(env, line, &i);
		if (quote && (*line)[i] == quote)
		{
			ft_str_delete(line, i--, 1);
			look_for_quote ^= 1;
		}
	}
}

/*return error if quote not closed*/
int	quote_check(char **line)
{
	char	*tmp;
	char	quotes[2];

	quotes[0] = find_first_quote(*line);
	quotes[1] = quotes[0];
	if (quotes[1])
	{
		tmp = ft_strchr(*line, quotes[1]);
		while (tmp)
		{
			tmp = ft_strchr(++tmp, quotes[1]);
			if (!tmp)
			{
				ft_putendl_fd("Unexpected EOF looking for matching '\"'", 2);
				g_exit_status = 2;
				return (1);
			}
			else
				quotes[1] = find_first_quote(++tmp);
			if (!tmp || !quotes[1])
				break ;
			tmp = ft_strchr(tmp, quotes[1]);
		}
	}
	return (0);
}
