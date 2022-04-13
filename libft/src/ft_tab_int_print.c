/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_int_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:28:12 by abensett          #+#    #+#             */
/*   Updated: 2021/11/17 17:28:12 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	ft_tab_int_print(int *tab, int len)
{
	while (len--)
	{
		ft_putnbr_fd(*tab++, 1);
		ft_putchar_fd(' ', 1);
	}
	printf("\n");
}
