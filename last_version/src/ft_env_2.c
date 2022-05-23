/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 23:49:14 by abensett          #+#    #+#             */
/*   Updated: 2022/05/12 17:37:11 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find env and return value*/
char	*get_env(t_env_list **env, char *key)
{
	t_env_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strlen(key) == ft_strlen(tmp->key) \
				&& !ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp->value);
		tmp = tmp->next;
	}	
	return (NULL);
}

/* from str=envp add t_env env to t_minishell shell  */
void	set_env(t_minishell *shell, char *str)
{
	int		i;
	char	**tmp;

	env_add_back(&shell->env, env_new(str));
	tmp = shell->envp;
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	shell->envp = set_envp(shell->env);
}

/* free t_env_list */
void	env_del(t_env_list *env, void (*del)(void *))
{
	del(env->key);
	del(env->value);
	del(env->all);
	free(env);
}

/* free *t_env_list */
void	env_clear(t_env_list **env, void (*del)(void *))
{
	if (env && *env)
	{
		env_clear(&(*env)->next, del);
		env_del(*env, del);
		*env = 0;
	}
}

/*remove env KEY from t_env_list of t_minishell SHELL*/
void	unset_env(t_minishell *shell, char *key)
{
	int			i;
	char		**tmp_envp;
	t_env_list	*prev;
	t_env_list	*tmp_env;

	tmp_env = shell->env;
	while (tmp_env)
	{
		if (ft_strlen(key) == ft_strlen(tmp_env->key) \
				&& !ft_strncmp(key, tmp_env->key, ft_strlen(key)))
		{
			env_del(tmp_env, free);
			prev->next = tmp_env->next;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
	tmp_envp = shell->envp;
	i = 0;
	while (tmp_envp[i])
		free(tmp_envp[i++]);
	free(tmp_envp);
	shell->envp = set_envp(shell->env);
}