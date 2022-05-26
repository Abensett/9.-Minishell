/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_long_check_order.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:09:19 by abensett          #+#    #+#             */
/*   Updated: 2021/12/18 19:13:42 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lst_long_check_order(t_list list)
{
	t_list	*tmp;

	tmp = &list;
	if (ft_lstsize(tmp) == 1)
		return (1);
	while (tmp->next)
	{
		if ((long)tmp->content <= (long)tmp->next->content)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}
