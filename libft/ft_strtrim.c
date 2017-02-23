/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		i;
	int		start;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	while (s[i])
		i++;
	if (i > start && i--)
	{
		while (i && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i--;
		i++;
	}
	new = (char*)malloc(sizeof(char) * (i - start + 1));
	if (!new)
		return (NULL);
	new[i - start] = '\0';
	while (i-- > start)
		new[i - start] = s[i];
	return (new);
}
