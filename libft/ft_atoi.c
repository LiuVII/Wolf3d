/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:56:51 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:56:54 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *nptr)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	while (*nptr && (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		sign = 44 - *nptr;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if ((num / 922337203685477580U == 1 && (*nptr - '0' >= 8 ||
			num % 922337203685477580U >= 1)) || (num / 922337203685477580U > 1))
			return ((-sign - 1) / 2);
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	num *= sign;
	return (num);
}
