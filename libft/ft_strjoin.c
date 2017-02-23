/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	if (s2)
		while (s2[i])
			i++;
	len = i;
	i = 0;
	if (s1)
		while (s1[i])
			i++;
	len += i;
	new = (char*)malloc(sizeof(char) * (len + 1));
	if (new)
	{
		new[len] = '\0';
		while (len > i && len-- && s2)
			new[len] = s2[len - i];
		while (len-- > 0 && s1)
			new[len] = s1[len];
		return (new);
	}
	return (NULL);
}
