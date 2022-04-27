/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:25 by abou              #+#    #+#             */
/*   Updated: 2022/04/28 00:47:11 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>

// /*LISTE CHAINEES BLOCK = FUNCTIONS+OPTION+ARG  PAS UTILISE POUR L'INSTANT*/ 

// typedef struct s_all_commands
// {
// 	char					**cmds;
// 	struct s_all_commands	*next;
// }			t_all_commands;

/* Donne le nombre d'arguments + 1 car nom fonction + args */

typedef struct s_simple_command
{
	int		nb_arguments;
	char	**av;
}			t_simple_command;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				*all;
	struct s_env_list	*next;
}	t_env_list;

/* Structure d'exectution */
typedef struct s_exec
{
	pid_t	pid;
	int		tmpin;
	int		tmpout;
	int		tmpret;
	int		fdpipe[2];
	int		fdin;
	int		fdout;

}	t_exec;

/* struture de toutes les informations nécessaires*/

typedef struct s_minishell
{
	char				*prompt;
	int					number_cmd;
	char				**envp;
	char				**paths;
	t_simple_command	*cmds;
	t_env_list			*env;
}						t_minishell;

/* The executor.c*/
void		execution(int i, t_minishell *shell);
void		executor(t_minishell *shell);

/* The ft_envs.c*/
t_env_list	*env_new(char *str);
void		env_add_back(t_env_list **env, t_env_list *new);
t_env_list	*init_env(char **envp);
char		**set_envp(t_env_list *env);

/* The ft_envs2.c*/
void		set_env(t_minishell *shell, char *str);
void		unset_env(t_minishell *shell, char *key);

/* The execute_binary.c*/
int			exec_binary(int num, t_minishell *shell);

/* The builtins.c */
void		echo(int i, t_minishell *shell);
void		cd(int i, t_minishell *shell);
void		pwd(void);
void		export(int i, t_minishell *shell);
void		unset(int i, t_minishell *shell);
void		env(t_minishell *shell);

#endif