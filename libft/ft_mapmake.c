/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapmake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:00:52 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/30 13:00:53 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_mapmake(int rows, int cols, char c)
{
	int		i;
	char	**map;

	map = (char**)malloc(sizeof(char*) * (rows + 1));
	if (!map)
		return (NULL);
	map[rows] = 0;
	i = -1;
	while (++i < rows)
	{
		map[i] = (char*)malloc(cols + 1);
		if (!map[i])
		{
			ft_mapfree(&map);
			return (NULL);
		}
		ft_memset(map[i], c, cols);
		map[i][cols] = '\0';
	}
	return (map);
}
