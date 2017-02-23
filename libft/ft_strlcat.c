/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:57:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:57:17 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t l;
	size_t j;

	i = 0;
	l = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	while (dst[l] != '\0')
	{
		if (l == size)
			return (l + j);
		l++;
	}
	while (src[i] != '\0' && i + l + 1 < size)
	{
		dst[l + i] = src[i];
		i++;
	}
	dst[l + i] = '\0';
	return (l + j);
}
