/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/26 15:49:24 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return key from str*/
static char	*find_key(char *str)
{
	int		i;
	char	*key;

	i = -1;
	while (str[++i])
		if (str[i] == '"' || str[i] == ' ' || str[i] == '\'')
			break ;
	key = ft_substr(str, 0, i);
	return (key);
}

/* Turn variables into their values thanks to get_env
and str modifying functions" */
void	expansion(t_env_list **env, char **line, int *i)
{
	int		len;
	char	*key;
	char	*value;

	key = find_key(&(*line)[*i + 1]);
	value = get_env(env, key);
	len = ft_strlen(key);
	ft_str_delete(line, *i, len + 1);
	free(key);
	ft_str_add(line, *i, value);
	*i += ft_strlen(value) - 1;
}
