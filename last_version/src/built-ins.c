/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/12 18:39:06 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* writes  separated by single blank (' ') characters
with (`\n'), to the standard output.
option -n => no newline */

int	echo(int i, t_minishell *shell)
{
	const char	*tmp = shell->cmds[i].av[1];
	int			j;
	int			option_n;

	j = 1;
	option_n = 1;
	if (ft_strlen(tmp) == 2 \
		&& !ft_strncmp(tmp, "-n", 2) && ++j)
		option_n = 0;
	while (ft_strlen(shell->cmds[i].av[j]) == 2 \
			&& !ft_strncmp(shell->cmds[i].av[j], "-n", 2))
		j++;
	while (shell->cmds[i].av[j])
	{
		ft_putstr_fd(shell->cmds[i].av[j++], 1);
		if (shell->cmds[i].av[j])
			ft_putchar_fd(' ', 1);
	}
	if (option_n)
		ft_putchar_fd('\n', 1);
	return (0);
}

/* Returns the name of the current working directory. */
/* buff = the Working directory et size = the size */
int	pwd(int i, t_minishell *shell)
{
	char	*pwd;
	char	*buf;
	size_t	size;

	buf = 0;
	size = 0;
	pwd = getcwd(buf, size);
	if (pwd == NULL)
		return (0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	(void)shell;
	(void)i;
	return (0);
}

/*
set (no arg) : display all variables of the environment
set arg=2 :unset the variable before setting the new value */
void	export(int i, t_minishell *shell)
{
	char	*tmp;

	if (!shell->cmds[i].av[1])
	{
		env(shell);
		return ;
	}
	tmp = ft_strchr(shell->cmds[i].av[1], '=');
	unset_env(shell, ft_substr(shell->cmds[i].av[1], 0, \
		ft_strlen(shell->cmds[i].av[1]) - ft_strlen(tmp)));
	set_env(shell, shell->cmds[i].av[1]);
}

/* unset the variable */
int	unset(int i, t_minishell *shell)
{
	unset_env(shell, shell->cmds[i].av[1]);
	return (0);
}

int	env(t_minishell *shell)
{
	t_env_list		*tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("%s\n", tmp->all);
		tmp = tmp->next;
	}
	return (0);
}
