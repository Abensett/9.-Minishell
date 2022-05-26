/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 17:06:56 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:29:49 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!*alst)
		*alst = new;
	else
	{
		tmp = ft_lstlast((*alst));
		tmp->next = new;
	}
}
