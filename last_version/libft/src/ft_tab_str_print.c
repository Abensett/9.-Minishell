/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_str_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:44:31 by abensett          #+#    #+#             */
/*   Updated: 2021/12/10 12:35:09 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_tab_str_print(char **tabstr)
{
	int	i;

	i = -1;
	while (tabstr[++i])
		ft_putstr_fd(tabstr[i], 1);
}
