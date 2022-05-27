/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/27 21:08:51 by shamizi          ###   ########.fr       */
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
	char	*substr;
	int 	j;

	j = 1;
	g_exit_status = 0;
	if (!shell->cmds[i].av[1])
	{
		env(shell);
		return ;
	}
	while (shell->cmds[i].av[j])
	{
		if (!ft_strncmp(shell->cmds[i].av[j], "=", 1))
		{
			ft_exit_status(1, shell);
			perror( "export");
			j++;
			continue ;
		}
		tmp = ft_strchr(shell->cmds[i].av[j], '=');
		if (!tmp)
			return;
		substr = ft_substr(shell->cmds[i].av[j], 0, ft_strlen(shell->cmds[i].av[j]) - ft_strlen(tmp));
		unset_env(shell,substr);
		set_env(shell, shell->cmds[i].av[j++]);
		free(substr);
	}
}

/* unset the variable */
int	unset(int i, t_minishell *shell)
{
	int	j;
	
	j = 1;
	if (!shell->cmds[i].av[1])
	{
		ft_exit_status(0, shell);
		return (0);
	}
	while(shell->cmds[i].av[j])
	{
		if (!ft_isalpha(*shell->cmds[i].av[1]))
		{
			perror("unset");
			ft_exit_status(1, shell);
			return(1);
		}
		j++;
	}
	j = 1;
	while(shell->cmds[i].av[j])
	{
		if (ft_strlen(shell->cmds[i].av[j]) == 1
		&& !ft_strncmp(shell->cmds[i].av[j], "=", 1))
			 perror( "unset");
		unset_env(shell, shell->cmds[i].av[j]);
		j++;
	}
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
