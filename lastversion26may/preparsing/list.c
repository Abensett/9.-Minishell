/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:33:46 by shamizi           #+#    #+#             */
/*   Updated: 2022/04/24 16:49:50 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//initialisé un maillon et alloué la mémoire
t_cmd	*listcreate(char *commande)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	cmd->com = commande;
	cmd->prev = NULL;
	cmd->next = NULL;
	return(cmd);
}

//ajouter un nouveau maillon si nécessaire
t_cmd	*listadd(t_cmd *cmd, char *commande, int pos)
{
	t_cmd *prec;
	t_cmd *cur;
	t_cmd *cell;
	int i;

	cur = malloc(sizeof(t_cmd));
	prec = malloc(sizeof(t_cmd));
	i = 0;
	cur = cmd;
	cell = listcreate(commande);
	if(cmd == NULL)
		return (cell);
	while(i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return(cmd);
}

//imprimé la liste chainé
void	print_list(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", cmd->com);
		if (cmd->arg != NULL)
			print_arg(cmd->arg);
		printf("-----------------------------------\n");
		cmd = cmd->next;
		i++;
	}
}
