/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_int_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 01:26:01 by abensett          #+#    #+#             */
/*   Updated: 2021/10/25 01:26:01 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lst_int_search(t_list list, int nb)
{
	t_list	*tmp;

	tmp = &list;
	while (tmp)
	{
		if ((long)tmp->content == nb)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
