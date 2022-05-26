/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:01:57 by abensett          #+#    #+#             */
/*   Updated: 2022/05/07 09:31:23 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_str_add(char **str, int start, char *str2)
{
	char	*tmp[2];

	tmp[0] = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(str2) + 1));
	if (!tmp[0])
		return ;
	ft_strlcpy(tmp[0], *str, start + 1);
	ft_strlcpy(tmp[0] + start, str2, start + ft_strlen(str2) + 1);
	ft_strlcpy(tmp[0] + start + ft_strlen(str2), *str + start, \
			ft_strlen(*str) + ft_strlen(str2) + 1);
	tmp[1] = *str;
	*str = tmp[0];
	free(tmp[1]);
}
