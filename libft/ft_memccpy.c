/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:54:27 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/24 21:54:29 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned const char	*usrc;
	unsigned char		*udst;

	usrc = src;
	udst = dst;
	while (n--)
	{
		*udst++ = *usrc++;
		if (*(usrc - 1) == (unsigned char)(c))
			return (udst);
	}
	return (NULL);
}
