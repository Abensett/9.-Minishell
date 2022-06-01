/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/31 16:32:18 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export2(t_minishell *shell, char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strchr(str, '=');
	tmp2 = ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp));
	unset_env(shell, tmp2);
	set_env(shell, str);
	free(tmp2);
}

void	cd_error(char *s1, char *s2, t_minishell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	ft_exit_status(1, shell);
	tmp = ft_strjoin(s1, sys_errlist[errno]);
	tmp2 = ft_strjoin(tmp, ": ");
	tmp3 = ft_strjoin(tmp2, s2);
	ft_putendl_fd(tmp3, 2);
	free(tmp);
	free(tmp2);
	free(tmp3);
}

void	cd2(char *old, char *new, t_minishell *shell, int i)
{
	char	*cwd2;
	char	*buff;
	size_t	size;

	buff = 0;
	size = 0;
	if (chdir(new) == 0)
	{
		cwd2 = getcwd(buff, size);
		new = ft_strjoin("PWD=", cwd2);
		if (new && old)
		{
			export2(shell, old);
			export2(shell, new);
		}
		free(new);
		free(cwd2);
		free(buff);
	}
	else
		cd_error("cd: ", shell->cmds[i].av[1], shell);
}

void	cd(int i, t_minishell *shell)
{
	char	*buff;
	char	*old;
	char	*new;
	char	*cwd;
	size_t	size;

	buff = 0;
	size = 0;
	old = NULL;
	new = NULL;
	if (!shell->cmds[i].av[1])
		new = get_env(&shell->env, "HOME");
	else
		new = shell->cmds[i].av[1];
	cwd = getcwd(buff, size);
	old = ft_strjoin("OLDPWD=", cwd);
	cd2(old, new, shell, i);
	free(buff);
	free(old);
	free(cwd);
}
