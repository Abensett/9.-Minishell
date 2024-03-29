/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:24:25 by abensett          #+#    #+#             */
/*   Updated: 2022/06/01 09:15:48 by abensett         ###   ########.fr       */
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
# include <sys/wait.h>
# include <errno.h>

/* global variable : self-explanatory */
extern int	g_exit_status;

/* Donne le nombre d'arguments + 1 car nom fonction + args */

typedef struct s_simple_command
{
	int		nb_args;
	int		nb_cmds;
	char	**av;
}			t_simple_command;

/* Environment variable structure key = name of the variable */

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				*all;
	struct s_env_list	*next;
}	t_env_list;

/* Exectution  structure */
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
	char				*inf;
	char				*outf;
	char				*heredoc;
	int					redirin;
	int					append;
	t_simple_command	*cmds;
	t_env_list			*env;
}						t_minishell;

//////////////////////////  LEXER  //////////////////////////////////
/*The space handling*/
void				space_handler(char **line);
int					is_redirection_or_pipe(char c);
int					is_doubled_redirection_or_pipe(char *c);

/*The quotes handling*/
void				quote_remove(t_env_list **env, char **line);
void				quote_expansion(t_env_list **env, char **line);
void				quote_expansion_heredoc(t_env_list **env, char **line);
int					quote_check(char **line);
void				quote_remove_after(t_env_list **env, char **line);
char				find_first_quote(char *line);

/*The expansion*/
void				expansion(t_env_list **env, char **line, int *i);

/*The arglist aka lexer.c*/
t_list				*lexer(t_env_list **env, char *line);
void				type_quote(char *quote, char c);

//////////////////////////  PARSING  ////////////////////////////////
/*The valid.c*/
int					is_valid(t_list *token_list, t_minishell	*shell);

/*The parsing utils*/
void				parser(t_list **token_list, t_minishell *shell);

/*The parsing utils*/
int					cmd_counter(char *str, t_list *token_lst);
t_simple_command	*pipe_separation(t_list **token_list, t_minishell *shell);
int					args_counter(t_list *token_list);
t_simple_command	*fill_cmds(t_list *t, t_simple_command *cmds,
						t_minishell *shell);

//////////////////////////  EXECUTION  ////////////////////////////////

/* The executor.c*/
void				execution(int i, t_minishell *shell, t_exec *exec);
void				executor(t_minishell *shell);

/* The executor2.c*/
int					ft_is_builtin(int i, t_minishell *shell);
void				execution(int i, t_minishell *shell, t_exec *exec);

/*The heredoc.*/
int					heredoc(t_minishell *shell);

//////////////////////////  SUBSYSTEM  ////////////////////////////////

/* The ft_envs.c*/
t_env_list			*env_new(char *str);
void				env_add_back(t_env_list **env, t_env_list *new);
t_env_list			*init_env(char **envp);
char				**set_envp(t_env_list *env);

/* The ft_envs2.c*/
char				*get_env(t_env_list **env, char *key);
void				set_env(t_minishell *shell, char *str);
void				unset_env(t_minishell *shell, char *key);

/* The exec_binary.c*/
int					exec_binary(int num, t_minishell *shell);

/* The builtins.c */
int					echo(int i, t_minishell *shell);
void				cd(int i, t_minishell *shell);
int					pwd(int i, t_minishell *shell);
void				export(int i, t_minishell *shell);
void				unset(int i, t_minishell *shell);
int					env(t_minishell *shell);
int					ft_exit(t_minishell *shell, char *line, t_list *token_list);

/* The ft_error */
void				ft_error(int i, char *str);
void				ft_exit_status(int i, t_minishell *shell);
void				ft_free(t_minishell *shell, char *mine, t_list *token_list);
int					store_fd_close(int tmpin, int tmpout);
void				freestrings(char **tab);
void				free_minishell2(t_minishell *shell);
void				free_env(t_env_list *env);
void				freecmds(t_simple_command *cmds);

/* The non interactive */
void				non_interactive_mode(char **array, char **env);
int					usage(void);

/* The main.c */
void				free_minishell(t_minishell *shell);

/* The signals.c */
void				ft_signaux(char *mode);

#endif
