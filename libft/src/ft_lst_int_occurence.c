/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_int_occurence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 04:33:00 by abensett          #+#    #+#             */
/*   Updated: 2021/10/25 04:33:00 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lst_int_occurence(t_list list, long nb)
{
	t_list	*tmp;
	int		i;

	tmp = &list;
	i = 0;
	while (tmp)
	{
		if ((long)tmp->content == nb)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
