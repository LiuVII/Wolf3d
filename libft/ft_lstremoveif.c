/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 15:25:47 by mfilipch          #+#    #+#             */
/*   Updated: 2016/08/23 15:25:50 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstremoveif(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*tmp;
	t_list	*tmp0;

	tmp = *begin_list;
	while (*begin_list && (*cmp)((*begin_list)->content, data_ref) == 0 && tmp)
	{
		*begin_list = tmp->next;
		free(tmp);
		tmp = *begin_list;
	}
	if (tmp)
		while (tmp && tmp->next)
		{
			if ((*cmp)(tmp->next->content, data_ref) == 0)
			{
				tmp0 = tmp->next;
				tmp->next = tmp->next->next;
				free(tmp0);
			}
			tmp = tmp->next;
		}
	else
		*begin_list = NULL;
}
