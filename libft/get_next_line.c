/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:59:20 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/07 12:59:25 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_rem_node(t_list *node)
{
	free((node)->content);
	(node)->content = 0;
	free(node);
}

static int		ft_freenret(int ret, t_list **bfd, char **buf, int fd)
{
	t_list			*tmp;
	t_list			*tmp0;

	(buf && *buf) ? free(*buf) : 0;
	if (ret <= 0 && bfd && *bfd)
	{
		if ((*bfd)->id == fd)
		{
			tmp = (*bfd)->next;
			ft_rem_node(*bfd);
			*bfd = tmp;
		}
		else if ((tmp = *bfd))
			while (tmp->next)
				if (tmp->next->id == fd)
				{
					tmp0 = tmp->next;
					tmp->next = tmp->next->next;
					ft_rem_node(tmp0);
					break ;
				}
	}
	if (ret == -1 || (ret == 0))
		return (ret);
	return (1);
}

static char		*ft_set_nbf(int ret, size_t inc, char *buf, char *nbf)
{
	if (!nbf && inc + 1 < (size_t)ret)
		return (ft_strndup(&buf[inc + 1], ret - inc - 1));
	else if (nbf && (!nbf[inc] || !nbf[inc + 1]))
	{
		free(nbf);
		return (NULL);
	}
	else if (nbf)
		return (ft_memmove(nbf, &nbf[1 + inc], 1 + ft_strlen(&nbf[1 + inc])));
	return (nbf);
}

static t_list	*ft_get_nbf(t_list **bfd, int fd)
{
	t_list			*new;

	if (!(*bfd))
	{
		if (!(new = ft_lstnew(NULL, 0)))
			return (NULL);
		new->id = fd;
		*bfd = new;
		return (new);
	}
	else if ((*bfd)->id != fd)
	{
		new = *bfd;
		while (new->next)
			if ((new = new->next)->id == fd)
				return (new);
		if (!(new->next = ft_lstnew(NULL, 0)))
			return (NULL);
		new->next->id = fd;
		return (new->next);
	}
	return (*bfd);
}

int				get_next_line(const int fd, char **line)
{
	int				ret;
	char			*bf;
	static t_list	*bfd;
	t_list			*nbf;
	int				pos[2];

	if (!line || fd < 0 || BUFF_SIZE < 1
		|| !(bf = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	pos[1] = 0;
	pos[0] = 0;
	nbf = ft_get_nbf(&bfd, fd);
	*line = ft_strndup("", 0);
	while (bf[pos[1]] != '\n' && (ret = (nbf && nbf->content) ? (int)
		ft_strlcpy(bf, nbf->content, BUFF_SIZE) : read(fd, bf, BUFF_SIZE)) > 0)
	{
		pos[1] = ft_strnchr(bf, ret, 10);
		pos[1] = (pos[1] < 0) ? ret : pos[1];
		if (!(*line = (char*)ft_memrealloc(*line, pos[0] + pos[1] + 1, pos[0])))
			return (ft_freenret(-1, &bfd, &bf, fd));
		ft_strncpy(&(*line)[pos[0]], bf, pos[1]);
		nbf->content = ft_set_nbf(ret, pos[1], bf, nbf->content);
		pos[0] += pos[1];
	}
	return (ft_freenret(ret + (!ret && strlen(*line)), &bfd, &bf, fd));
}
