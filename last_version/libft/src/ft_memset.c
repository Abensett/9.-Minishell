/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:27:34 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:31:06 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*a;

	if (s == NULL)
		return (NULL);
	a = s;
	while (n)
	{
		*a = c;
		a++;
		n--;
	}
	return (s);
}
