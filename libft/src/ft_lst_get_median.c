/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_get_median.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:22:18 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:22:18 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	ft_lst_get_median(t_list list)
{
	t_list	*tmp ;
	long	*tab;
	int		i;

	i = 0;
	tab = malloc(ft_lstsize(&list) * sizeof(long));
	tmp = &list;
	while (tmp)
	{
		tab[i++] = (long)(tmp->content);
		tmp = tmp->next;
	}
	return (tab[ft_lstsize(&list) / 2]);
}
