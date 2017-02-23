/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:56:51 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:56:54 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_power(double base, int power)
{
	long double	total;

	total = 1;
	if (power >= 1)
		while (power--)
			total *= base;
	else if (power <= -1)
		while (power++)
			total /= base;
	return (total);
}
