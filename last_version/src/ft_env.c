/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 03:16:42 by abensett          #+#    #+#             */
/*   Updated: 2022/05/23 03:17:30 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  create t_env_list with key = variable, value = value, all = str
 from str = "key = value" */

t_env_list	*env_new(char *str)
{
	char		*tmp;
	t_env_list	*returned;

	returned = malloc(sizeof(t_env_list));
	if (!returned)
		return (0);
	returned->next = 0;
	returned->all = ft_strdup(str);
	tmp = ft_strchr(str, '=');
	returned->key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp));
	returned->value = ft_strdup(tmp + 1);
	return (returned);
}

/* add env at end of env_list */
void	env_add_back(t_env_list **env, t_env_list *new)
{
	t_env_list	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/* cast from char **envp return t_env_list */
t_env_list	*init_env(char **envp)
{
	int			i;
	t_env_list	*env;

	env = 0;
	i = 0;
	while (envp[i])
		env_add_back(&env, env_new(envp[i++]));
	return (env);
}

/* cast from t_env_list to **char */
char	**set_envp(t_env_list *env)
{
	int			i;
	int			len;
	char		**returned;
	t_env_list	*tmp;

	len = 1;
	tmp = env;
	while (tmp->next && ++len)
		tmp = tmp->next;
	returned = malloc(sizeof(char *) * (len + 1));
	if (!returned)
		return (0);
	i = 0;
	tmp = env;
	while (tmp)
	{
		returned[i++] = ft_strdup(tmp->all);
		tmp = tmp->next;
	}
	returned[i] = 0;
	return (returned);
}