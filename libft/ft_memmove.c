/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:57:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:57:17 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned const char	*usrc;
	unsigned char		*udst;

	usrc = src;
	udst = dst;
	if (usrc <= udst)
	{
		i = len;
		while (i--)
			*(udst + i) = *(usrc + i);
	}
	else if (usrc > udst)
	{
		i = 0;
		while (i++ < len)
			*(udst + i - 1) = *(usrc + i - 1);
	}
	return (udst);
}
