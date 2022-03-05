/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_long_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:39:17 by abensett          #+#    #+#             */
/*   Updated: 2021/11/13 17:39:17 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	ft_tab_long_print(long *tab, int len)
{
	while (len--)
	{
		ft_putnbr_fd(*tab++, 1);
		ft_putchar_fd(' ', 1);
	}
	printf("\n");
}
