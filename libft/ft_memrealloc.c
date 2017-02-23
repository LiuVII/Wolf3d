/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memrealloc(void *src, size_t n_size, size_t size)
{
	void		*new;

	new = (unsigned char*)ft_memalloc(n_size);
	if (!new)
		return (NULL);
	if (src)
	{
		ft_memcpy(new, src, size);
		free(src);
	}
	return (new);
}
