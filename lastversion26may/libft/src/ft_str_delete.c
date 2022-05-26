/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:02:01 by abensett          #+#    #+#             */
/*   Updated: 2022/05/07 09:28:36 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_str_delete(char **str, int start, int len)
{
	char	*tmp[2];

	tmp[0] = malloc(sizeof(char) * (ft_strlen(*str) - len + 1));
	if (!tmp[0])
		return ;
	ft_strlcpy(tmp[0], *str, start + 1);
	ft_strlcpy(tmp[0] + start, *str + start + len, \
			ft_strlen(*str + start + len) + 1);
	tmp[1] = *str;
	*str = tmp[0];
	free(tmp[1]);
}
