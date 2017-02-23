/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:03:05 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 17:03:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ub;
	size_t			i;

	i = 0;
	ub = b;
	while (i++ < len)
		*(ub + i - 1) = (unsigned char)(c);
	return (ub);
}
