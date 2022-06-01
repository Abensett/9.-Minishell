/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_int_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 23:58:32 by abensett          #+#    #+#             */
/*   Updated: 2021/10/24 23:58:32 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lst_int_print(t_list list)
{
	t_list	*tmp;

	tmp = &list;
	while (tmp)
	{
		ft_putnbr_fd((long int)tmp->content, 1);
		ft_putstr_fd(" ", 1);
		tmp = tmp->next;
	}
}
