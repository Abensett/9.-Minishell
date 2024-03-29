/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/05/30 20:42:27 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return 1 when c is pipe or redirection else return 0*/
int	is_redirection_or_pipe(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_doubled_redirection_or_pipe(char *c)
{
	if (ft_strlen(c) == 2 && !ft_strncmp(c, ">>", 2))
		return (1);
	if (ft_strlen(c) == 2 && !ft_strncmp(c, "<<", 2))
		return (1);
	return (0);
}

/*put space before >, < or pipe */
static void	handle_before(char **line)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		type_quote(&quote, (*line)[i]);
		if ((!quote && i > 0 && (is_redirection_or_pipe((*line)[i])
				&& (*line)[i - 1] != (*line)[i] && (*line)[i - 1] != ' '))
				|| (quote != '\'' && (*line)[i] == '$'
				&& (*line)[i - 1] != ' ' && (*line)[i - 1] != '"'
				&& (*line)[i - 1] != '\'' && !ft_isalpha((*line)[i + 1])))
			ft_str_add(line, i++, " ");
	}
}

/*put space after >, < or pipe if  */
static void	handle_after(char **line)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		type_quote(&quote, (*line)[i]);
		if (!quote && is_redirection_or_pipe((*line)[i]))
		{
			if ((*line)[i + 1] != (*line)[i] && (*line)[i + 1] != ' ')
				ft_str_add(line, ++i, " ");
			else if ((*line)[i + 1] == (*line)[i]
					&& (*line)[i - 1] == (*line)[i])
				ft_str_add(line, ++i, " ");
		}
	}
}

/*put space before and after < > | if not */
void	space_handler(char **line)
{
	handle_before(line);
	handle_after(line);
}
