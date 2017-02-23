/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:57:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:57:17 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == (char)(c))
			j = i;
		i++;
	}
	if (s[i] == (char)(c))
		return ((char*)(&s[i]));
	if (j == 0 && s[0] != (char)(c))
		return (NULL);
	return ((char*)(&s[j]));
}
