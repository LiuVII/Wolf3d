/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:57:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:57:17 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	int	i;
	int j;

	i = 0;
	if (*little)
	{
		while (big[i])
		{
			j = 0;
			while (big[i + j] && big[i + j] == little[j])
				j++;
			if (!little[j])
				return ((char*)(&big[i]));
			i++;
		}
		return (NULL);
	}
	return ((char*)(big));
}
