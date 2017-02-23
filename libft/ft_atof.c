/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:56:51 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:56:54 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_checkval(const char *nptr)
{
	if (ft_strnequ_ci(nptr, "nan", 3))
		return (-1);
	else if (ft_strnequ_ci(nptr, "inf", 3))
		return (1);
	return (0.0);
}

static float	ft_isval(int i)
{
	int nan;
	int inf;

	nan = 0x7F800001;
	inf = 0x7F800000;
	if (i == 0)
		return (*(float*)&nan);
	return (i * *(float*)&inf);
}

double			ft_atof(const char *nptr)
{
	int				sign;
	long double		num;
	long double		trunc;

	sign = 1;
	num = 0;
	trunc = 1;
	if (!nptr)
		return (num);
	while (*nptr && (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	(*nptr == '+' || *nptr == '-') ? sign = 44 - *(nptr++) : 0;
	sign = (sign == -1 && (ft_isdigit(*nptr) ||
		(*nptr == '.' && ft_isdigit(*(nptr + 1))))) ? -1 : 1;
	if ((num = ft_checkval(nptr)) != 0.0)
		return (ft_isval((num + 1) / 2 * sign));
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	if (*nptr == '.' && *nptr++)
		while (ft_isdigit(*nptr) && *nptr++ && (trunc *= 10))
			num += ((*(nptr - 1) - '0')) / trunc;
	if (*nptr++ == 'e' && (ft_isdigit(*nptr) || ((*nptr == '+'
		|| *nptr == '-') && ft_isdigit(*(nptr + 1)))))
		num *= ft_power(10, ft_atoi(nptr));
	return (sign * num);
}
