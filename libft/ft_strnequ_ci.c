/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ_ci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 09:56:51 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 09:56:54 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strnequ_ci(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && i < n
			&& ft_tolower(s1[i]) == ft_tolower(s2[i]))
			i++;
		if (i == n)
			return (1);
		else
			return ((ft_tolower(s1[i]) == ft_tolower(s2[i])) ? 1 : 0);
	}
	if (s1 == s2 || n == 0)
		return (1);
	return (0);
}
