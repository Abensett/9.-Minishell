/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_int_check_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 04:32:38 by abensett          #+#    #+#             */
/*   Updated: 2021/10/25 04:32:38 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lst_int_check_order(t_list list)
{
	t_list	*tmp;

	tmp = &list;
	if (ft_lstsize(tmp) == 1)
		return (1);
	while (tmp->next)
	{
		if (tmp->content <= tmp->next->content)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}
