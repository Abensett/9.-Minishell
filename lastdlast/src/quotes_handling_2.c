/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/06/01 12:27:14 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remove quote and expand what's not between ' ' */
void	quote_remove_after(t_env_list **env, char **line)
{
	int		i;
	char	quote;
	int		look_for_quote;

	i = -1;
	quote = 0;
	look_for_quote = 0;
	if (is_quoted_redirection((*line)))
	{
		while ((*line)[++i])
		{
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
}

/*expand what's not between ' ', used for heredoc */
void	quote_expansion_heredoc(t_env_list **env, char **line)
{
	int		i;
	char	quote;
	int		look_for_quote;

	i = -1;
	quote = 0;
	look_for_quote = 0;
	if (*line)
	{
		while ((*line)[++i])
		{
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
}
