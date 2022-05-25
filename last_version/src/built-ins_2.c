/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:21:02 by abensett          #+#    #+#             */
/*   Updated: 2022/05/25 14:37:15 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	set_env2(t_minishell *shell, char *key, char *value)
  {
  int i;
  char **tmp;

  env_add_back(&shell->env, env_new(key));
  tmp = shell->envp;
  i = 0;
  while(tmp[i])
  free(tmp[i++]);
  shell->envp = set_envp(shell->env);
  }*/
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
	//printf("%s\n", tmp);
	//transformer en putstrfd pour mettre sur sortie d'erreur
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
	//si y'a pas de 1er argument utiliser la valeur de HOME=
	//si 2 argument ou plus renvoyer too many argument
	//si pas les droit : permission denied
	//si chemin existe pas : no shuch files or directory
	//si c'est pas un dossier : is not a directory
	/*if(shell->cmds[i].nb_args > 2)
	{
		printf("il y a un av2 ???\n");
		return ;
	}*/
//	printf("j'ai bien passer le return si il y avait av2\n");
	if(!shell->cmds[i].av[1])
		new = get_env(&shell->env, "HOME");
	else
		new = shell->cmds[i].av[1];
//	printf("new : %s\n", new);
	//printf("new avant cd :%s\n",new);
	old = ft_strjoin("OLDPWD=", getcwd(buff, size));
	if(chdir(new) == 0)
	{
		new = ft_strjoin("PWD=", getcwd(buff, size));
		//ici je fait un access pour voir si j'ai les droit pour aller dans l'endroit, si j'ai pas je doit 
		//free old buff et new et envoyé le message d'erreur adéquat

		printf("old : %s\n",old);
		printf("new : %s\n",new);
	/*	if(new && old)
		{

			export2(shell, old);
			export2(shell, new);
		}*/
	}
	else
		cd_error("cd: ", shell->cmds[i].av[1]);
	//	printf("chdir a failed\n");
	free(buff);
	free(old);
	free(new);
}

