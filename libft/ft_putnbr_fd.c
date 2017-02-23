/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	num;
	long	trunc;

	trunc = 10;
	num = n;
	(n < 0) ? (num = -(long)(n)) : 0;
	while ((num /= 10) >= 1)
		trunc *= 10;
	num = n;
	(n < 0) ? (num = -(long)(n)) : 0;
	(n < 0) ? write(fd, "-", 1) : 0;
	while ((trunc /= 10) >= 1)
	{
		c = num / trunc + '0';
		num %= trunc;
		write(fd, &c, 1);
	}
}
