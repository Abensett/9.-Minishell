/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/12 02:27:46 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return the pointer of the first quote ' or " */

void	ft_str_delete(char **str, int start, int len)
{
	char	*tmp[2];

	tmp[0] = malloc(sizeof(char) * (ft_strlen(*str) - len + 1));
	if (!tmp[0])
		return ;
	ft_strlcpy(tmp[0], *str, start + 1);
	ft_strlcpy(tmp[0] + start, *str + start + len, \
			ft_strlen(*str + start + len) + 1);
	tmp[1] = *str;
	*str = tmp[0];
	free(tmp[1]);
}

/* return first quote between ' and " */
static char	find_first_quote(char *line)
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
		if (!look_for_quote)
			quote = find_first_quote(&((*line)[i]));
		if (quote != '\'' && (*line)[i] == '$'
			 && ft_isalpha((*line)[i + 1]))
			expansion(env, line, &i);
		if (quote && (*line)[i] == quote)
		{
			ft_str_delete(line, i--, 1);
			look_for_quote ^= 1;
		}
	}
}