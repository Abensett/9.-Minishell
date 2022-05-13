/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:37:13 by shamizi           #+#    #+#             */
/*   Updated: 2022/04/24 16:48:56 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//initialisation + assigner la valeur a cmd
t_arg	*argcreate(char *commande)
{
	t_arg *arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->argu = NULL;
	arg->prev = NULL;
	arg->next = NULL;
	arg->argu = commande;
	return(arg);
}

//ajouter un maillon a la chaine de caractere
t_arg	*argadd(t_arg *arg, char *commande, int pos)
{
	t_arg *prec;
	t_arg *cur;
	t_arg *cell;
	int i;

	cur = malloc(sizeof(t_arg));
	prec = malloc(sizeof(t_arg));
	i = 0;
	cur = arg;
	cell = argcreate(commande);
	if(arg == NULL)
		return (cell);
	while(i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return(arg);
}

//imprimer ma liste chainé

void	print_arg(t_arg *arg)
{
	int		i;

	i = 0;
	while (arg)
	{
		printf("| cmd->arg : %s            \n", arg->argu);
		arg = arg->next;
		i++;
	}
}
