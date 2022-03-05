/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_str_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:40:00 by abensett          #+#    #+#             */
/*   Updated: 2021/12/07 14:56:13 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lst_str_print(t_list list)
{
	t_list	*tmp;

	tmp = &list;
	while (tmp)
	{
		ft_putendl_fd((tmp->content), 1);
		tmp = tmp->next;
	}
}
