/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_words(char **arr, int wc)
{
	while (wc--)
		free(arr[wc]);
}

static char	**ft_strrealsplit(char const *s, char c, char **arr, int i)
{
	int		wc;
	int		len;
	int		j;

	wc = 0;
	len = 0;
	while (s[i])
	{
		(s[i] != c) ? len++ : (len = 0);
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
		{
			arr[wc] = (char*)malloc(len + 1);
			if (!arr[wc])
				free_words(arr, wc);
			if (!arr[wc])
				return (NULL);
			arr[wc][len] = '\0';
			j = 0;
			while (len-- && ++j)
				arr[wc][j - 1] = s[i - len];
			wc++;
		}
		i++;
	}
	return (arr);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		wc;

	i = 0;
	wc = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			wc++;
		i++;
	}
	arr = (char**)malloc(sizeof(char*) * (wc + 1));
	if (!arr)
		return (NULL);
	arr[wc] = 0;
	return (ft_strrealsplit(s, c, arr, 0));
}
