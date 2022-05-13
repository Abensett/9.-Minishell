/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:51:42 by shamizi           #+#    #+#             */
/*   Updated: 2022/04/19 16:20:49 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
#define MINI_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*typedef struct s_cmd
{
	char **cmdu;
	int sstdin;
	int sstdout;
	int redir;
}t_cmd;
*/

typedef struct s_arg
{
	char *argu;
	struct s_arg *prev;
	struct s_arg *next;
}t_arg;

typedef struct s_cmd
{
	char *com; //apre la division des pipes, divisions des espaces
	struct s_cmd *prev;
	struct s_cmd *next;
	struct s_arg *arg;
}t_cmd;

/*typedef struct s_pip
{
	char *pipe; //du coup les argument entre les |
	struct s_pip *prev;
	struct s_pip *next;
}t_pip;
*/

void	print_arg(t_arg *arg);
t_arg	*argcreate(char *commande);
t_arg	*argadd(t_arg *arg, char * commande, int pos);
t_cmd	*listcreate(char *commande);
int		ft_strlen(char *str);
void	print_list(t_cmd *cmd);
t_cmd	*listadd(t_cmd *cmd, char *commande, int pos);
static char **freestrings(char **tab);
char **ft_split(char *s, char c);
#endif
