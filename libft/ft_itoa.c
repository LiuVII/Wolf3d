/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long		num;
	long		sign;
	char		*str;
	int			i;

	i = 1;
	sign = 1;
	num = (n < 0) ? -1 * (long)n : n;
	if (n < 0 && i++)
		sign = -1;
	while ((num /= 10) >= 1)
		i++;
	str = (char*)malloc(i + 1);
	str[i] = '\0';
	(n < 0) ? str[0] = '-' : 0;
	num = (n < 0) ? -1 * (long)n : n;
	while (i-- + (sign - 1) / 2)
	{
		str[i] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
