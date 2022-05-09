/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/09 10:16:46 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* writes  separated by single blank (' ') characters
with (`\n'), to the standard output. 
option -n => no newline */
void	echo(int i, t_minishell *shell)
{
	const char	*tmp = shell->cmds[i].av[1];
	int			j;
	int			option_n;

	j = 1;
	option_n = 1;
	if (ft_strlen(tmp) == ft_strlen("-n") \
		&& !ft_strncmp(tmp, "-n", ft_strlen("-n")) && ++j)
		option_n = 0;
	while (ft_strlen(shell->cmds[i].av[j]) == 2\
		&& !ft_strncmp(shell->cmds[i].av[j],"-n",2))
		j++; 
	while (shell->cmds[i].av[j])
	{
		ft_putstr_fd(shell->cmds[i].av[j++], 1);
		if (shell->cmds[i].av[j])
			ft_putchar_fd(' ', 1);
	}
	if (option_n)
		ft_putchar_fd('\n', 1);
	(void)i;
	(void)shell;
}

void	cd(int i, t_minishell *shell)
{
	(void)i;
	(void)shell;
}

/* Returns the name of the current working directory. */
/* buff = the Working directory et size = the size */
void	pwd(void)
{
	char	*pwd;
	char	*buf;
	size_t	size;

	buf = 0;
	size = 0;
	pwd = getcwd(buf, size);
	ft_putendl_fd(pwd, 1);
	free(pwd);
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
void	unset(int i, t_minishell *shell)
{
	unset_env(shell, shell->cmds[i].av[1]);
}
