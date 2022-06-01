/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_long_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:09:55 by abensett          #+#    #+#             */
/*   Updated: 2021/11/16 10:09:55 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_tab_long_sort(long *tab, int size)
{
	int		tmp2;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j + 1] < tab[j])
			{
				tmp2 = tab[j + 1];
				tab[j + 1] = tab[j];
				tab[j] = tmp2;
			}
			j++;
		}
		i++;
	}
}
