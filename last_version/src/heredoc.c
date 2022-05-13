/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:49:14 by abensett          #+#    #+#             */
/*   Updated: 2022/05/09 11:30:31 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return 1 if delimiter found else 0*/
int	is_eof(char *eof, char *line)
{
	if (!eof || !*eof || !line || !*line)
		return (0);
	if (ft_strlen(line) == ft_strlen(eof)
		&& ft_strncmp(line, eof, ft_strlen(line)) == 0)
		return (1);
	return (0);
}

char	*add_oldlines(char *oldlines, char *tmp, char *lines)
{
	int	i;

	i = 0;
	while (oldlines != NULL && oldlines[i])
	{
		lines[i] = oldlines[i];
		i++;
	}
	while (tmp != NULL && tmp[i - ft_strlen(oldlines)])
	{
		lines[i] = tmp[i - ft_strlen(oldlines)];
		i++;
	}
	return (lines);
}

char	*word_splitter(char *tmp, char *delimit, char *lines, char *oldlines)
{
	while ((!tmp || !*tmp) || !is_eof(delimit, tmp))
	{
		if (lines != NULL)
		{
			oldlines = ft_strdup(lines);
			free(lines);
		}
		lines = malloc(sizeof(char) * (ft_strlen(tmp)
					+ ft_strlen(oldlines) + 2));
		lines = add_oldlines(oldlines, tmp, lines);
		lines[ft_strlen(tmp) + ft_strlen(oldlines)] = '\n';
		lines[ft_strlen(tmp) + ft_strlen(oldlines) + 1] = 0;
		free(oldlines);
		free(tmp);
		tmp = readline("heredoc>");
	}
	return (lines);
}

int	heredoc(t_minishell *shell)
{
	char		*tmp;
	char		*lines;
	char		*oldlines;
	int			pipefd[2];

	oldlines = 0;
	lines = 0;
	tmp = readline(">");
	lines = word_splitter(tmp, shell->heredoc, lines, oldlines);
	pipe(pipefd);
	write(pipefd[1], lines, ft_strlen(lines));
	close(pipefd[1]);
	return (pipefd[0]);
}
