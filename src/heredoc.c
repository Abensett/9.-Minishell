/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:49:14 by abensett          #+#    #+#             */
/*   Updated: 2022/05/24 18:53:15 by abensett         ###   ########.fr       */
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

/*put oldlines and tmp into lines*/
static char	*fill_lines(char *oldlines, char *tmp, char *lines)
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

/* if delimit !=eof
save lines in oldlines
add tmp to lines 
*/
static char	*concatenate(char *tmp, char *delimit, char *lines, char *oldlines,
						t_minishell *shell)
{
	while ((!tmp || !*tmp) || !is_eof(delimit, tmp))
	{
		if (lines != NULL)
		{
			oldlines = ft_strdup(lines);
			free(lines);
		}
		quote_expansion_heredoc(&shell->env, &tmp);
		lines = malloc(sizeof(char) * (ft_strlen(tmp)
					+ ft_strlen(oldlines) + 2));
		lines = fill_lines(oldlines, tmp, lines);
		lines[ft_strlen(tmp) + ft_strlen(oldlines)] = '\n';
		lines[ft_strlen(tmp) + ft_strlen(oldlines) + 1] = 0;
		free(oldlines);
		free(tmp);
		tmp = readline(">");
		if (!tmp)
			break;
	}
	return (lines);
}

/*heredoc handler*/
int	heredoc(t_minishell *shell)
{
	char		*tmp;
	char		*lines;
	char		*oldlines;
	int			pipefd[2];

	oldlines = 0;
	lines = 0;
	ft_signaux("heredoc");
	tmp = readline(">");
	if(g_exit_status == 128 + SIGINT)
			return (0);
	if (!tmp)
		return (0);
	lines = concatenate(tmp, shell->heredoc, lines, oldlines, shell);
	pipe(pipefd);
	write(pipefd[1], lines, ft_strlen(lines));
	close(pipefd[1]);
	return (pipefd[0]);
}
