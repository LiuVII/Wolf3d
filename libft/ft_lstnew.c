/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t c_s)
{
	t_list		*new;
	size_t		cs;

	new = (t_list*)malloc(sizeof(t_list));
	cs = c_s;
	if (!new)
		return (NULL);
	if (content)
	{
		new->c_s = cs;
		new->content = (char*)malloc(cs);
		if (!new->content)
			return (NULL);
		while (cs--)
			((char*)(new->content))[cs] = ((char const*)(content))[cs];
	}
	else
	{
		new->content = NULL;
		new->c_s = 0;
	}
	new->next = NULL;
	return (new);
}
