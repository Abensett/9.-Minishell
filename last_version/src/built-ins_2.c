/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/25 23:51:48 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export2(t_minishell *shell, char *str)
{
	char *tmp;

	tmp = ft_strchr(str, '=');
	unset_env(shell, ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp)));
	set_env(shell, str);
}

void	cd_error(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strjoin(s1,sys_errlist[errno]);
	tmp = ft_strjoin(tmp, ": ");
	tmp = ft_strjoin(tmp, s2);
	ft_putendl_fd(tmp, 2);
	free(tmp);
}
void	cd(int i, t_minishell *shell)
{
	char *buff;
	char *old;
	char *new;
	size_t size;

	buff = 0;
	size = 0;
	old = NULL;
	new = NULL;
	if(!shell->cmds[i].av[1])
		new = get_env(&shell->env, "HOME");
	else
		new = shell->cmds[i].av[1];
	old = ft_strjoin("OLDPWD=", getcwd(buff, size));
	if(chdir(new) == 0)
	{
		new = ft_strjoin("PWD=", getcwd(buff, size));
		if(new && old)
		{

			export2(shell, old);
			export2(shell, new);
		}
	}
	else
		cd_error("cd: ", shell->cmds[i].av[1]);
	free(buff);
	free(old);
	free(new);
}

