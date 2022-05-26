/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:25:49 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:28:43 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;

	new = malloc(size * count);
	if (!new)
		return (NULL);
	ft_memset(new, 0, count * size);
	return (new);
}
