/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 15:25:47 by mfilipch          #+#    #+#             */
/*   Updated: 2016/08/23 15:25:50 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclr(t_list **begin_list)
{
	t_list	*tmp;

	while (*begin_list)
	{
		tmp = (*begin_list)->next;
		if ((*begin_list)->content)
			free((*begin_list)->content);
		free(*begin_list);
		*begin_list = tmp;
	}
}
