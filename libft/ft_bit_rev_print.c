/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_rev_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:03:51 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/30 13:03:53 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void				ft_bit_rev_print(void *addr, size_t size)
{
	int				i;
	size_t			j;
	unsigned char	*c;
	unsigned char	a;
	unsigned char	b;

	c = addr;
	j = 0;
	while (j++ < size)
	{
		a = c[j - 1];
		i = -1;
		while (++i < 8)
		{
			b = a % 2 + '0';
			write(1, &b, 1);
			a = a / 2;
		}
		write(1, "|", 1);
		if (j % 2 == 0)
			write(1, "\n", 1);
	}
}
