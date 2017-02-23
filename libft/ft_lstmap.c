/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstfree(t_list **alst)
{
	if (!alst || !*alst)
		return (NULL);
	if ((*alst)->next)
		ft_lstfree(&((*alst)->next));
	if ((*alst)->content)
	{
		free((*alst)->content);
		(*alst)->content = NULL;
	}
	free(*alst);
	*alst = NULL;
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*head;
	t_list		*tail;
	t_list		*curr;

	head = NULL;
	curr = NULL;
	while (lst)
	{
		tail = (t_list*)malloc(sizeof(t_list));
		tail = f(lst);
		if (!tail)
			return (ft_lstfree(&lst));
		if (!head)
		{
			head = tail;
			curr = head;
		}
		else
		{
			curr->next = tail;
			curr = curr->next;
		}
		lst = lst->next;
	}
	return (head);
}
