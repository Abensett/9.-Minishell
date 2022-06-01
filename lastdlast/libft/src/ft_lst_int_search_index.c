/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_int_search_index.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:03:32 by abensett          #+#    #+#             */
/*   Updated: 2021/12/10 12:25:16 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lst_int_search_index(t_list list, int nb)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = &list;
	while (tmp)
	{
		if ((long)tmp->content == nb)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
