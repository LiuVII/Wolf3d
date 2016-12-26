/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 21:48:16 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 21:48:18 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	ft_read_to_list(int fd, t_list **img_l, t_data *d)
{
	t_list	*tmp;
	char	*line;
	int		ret;
	int		rows;

	rows = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0 && ++rows)
		if (!(*img_l))
		{
			if (!(*img_l = ft_lstnew(line, ft_strlen(line) + 1)))
				ft_free_n_exit(d, img_l, line, -5);
			tmp = *img_l;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(line, ft_strlen(line) + 1)))
				ft_free_n_exit(d, img_l, line, -5);
			tmp = tmp->next;
		}
	(line) ? free(line) : 0;
	if (ret == -1)
		ft_free_n_exit(d, img_l, NULL, -4);
	return (rows);
}

/*
** actually there's no need for t_3d array to read a grid
** but it might be useful later for objects or textures:
** if just using diff numbers for img.z wouldn't be good enough
*/

static int	ft_split_n_rec(t_data *d, t_list *img_l, int rows)
{
	char	**tab_line;
	int		i;
	int		j;

	i = -1;
	while (++i < rows && (j = -1))
	{
		if (!(tab_line = ft_strsplit(img_l->content, ' ')) ||
			!((d->img)[0][i] = (t_3d*)ft_memalloc(sizeof(t_3d) * img_l->c_s)))
			return (-1);
		while (tab_line[++j])
		{
			(d->img)[0][i][j].z = ft_atoi(tab_line[j]);
			((d->img)[0][i][j].z == -2) ? d->plrc.x = GR_S * (j + 0.5) : 0;
			((d->img)[0][i][j].z == -2) ? d->plrc.y = GR_S * (i + 0.5) : 0;
		}
		ft_mapfree(&tab_line);
		if (i > 0 && d->img_size.x != j)
			ft_free_n_exit(d, &img_l, NULL, -10);
		(i == 0) ? (d->img_size.x = j) : 0;
		img_l = img_l->next;
	}
	return (0);
}

int			ft_read(char *filename, t_data *d)
{
	int		rows;
	int		fd;
	t_list	*img_l;

	img_l = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_free_n_exit(d, &img_l, NULL, -4);
	if ((rows = ft_read_to_list(fd, &img_l, d)) <= 0)
		ft_free_n_exit(d, &img_l, NULL, -10);
	if (!(d->img = (t_3d***)ft_memalloc(sizeof(t_3d**))))
		ft_free_n_exit(d, &img_l, NULL, -5);
	d->img_size.z = 1;
	if (!((d->img)[0] = (t_3d**)ft_memalloc(sizeof(t_3d*) * rows)))
		ft_free_n_exit(d, &img_l, NULL, -5);
	d->img_size.y = rows;
	if (ft_split_n_rec(d, img_l, rows) < 0)
		ft_free_n_exit(d, &img_l, NULL, -5);
	ft_lstclr(&img_l);
	return (0);
}
