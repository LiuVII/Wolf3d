/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:43:35 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/01 14:43:43 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_putnbr_hex(int octet, int rem)
{
	const char			*base = "0123456789abcdef";

	if (rem > 1)
		ft_putnbr_hex(octet / 16, rem - 1);
	write(1, base + (octet % 16), 1);
}

void		ft_memprint(const void *addr, size_t size)
{
	size_t				c;
	size_t				i;
	const unsigned char	*ptr;

	i = 0;
	while (i < size)
	{
		ptr = addr + i;
		c = -1;
		while (++c < 16 && c + i < size)
		{
			ft_putnbr_hex(*(ptr + c), 2);
			(c % 2) ? (write(1, " ", 1)) : 0;
		}
		while (++c < 17)
			(c % 2) ? (write(1, "  ", 2)) : (write(1, "   ", 3));
		c = -1;
		while (++c < 16 && c + i < size)
			(32 <= *(ptr + c) && *(ptr + c) <= 126) ?
		(write(1, ptr + c, 1)) : write(1, ".", 1);
		write(1, "\n", 1);
		i += 16;
	}
}
