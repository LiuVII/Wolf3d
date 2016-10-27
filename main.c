/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:48:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/13 14:48:18 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	ft_displayit(t_data *d, int flag)
{
// 	ft_putstr("\
// ____________________________________\n\
// PARAMETERS:\n\
// Mandelbrot Set : 1\n\
// Julia Set      : 2\n\
// Newton Set (mode root or mode iter):\n\
// 	z^3-1      : 30 OR 31\n\
// 	cosh(z)-1  : 40 OR 41\n\
// 	sin(z)     : 50 OR 51\n\n\
// CONTROLS:\n\
// Translation:\n\
// 	Y: Key: UP, DOWN\n\
// 	X: Key: LEFT, RIGHT\n\n\
// Zoom:\n\
// 	IN-OUT : mouse scroll\n\n\
// Center:\n\
// 	Mouse click: Btn 2\n\
// ____________________________________\n");
	(flag == 0) ? ft_free_n_exit(d, NULL, NULL, -1) : 0;
	mlx_expose_hook(d->win, ft_drawit, d);
	mlx_key_hook(d->win, ft_key_hook, d);
	mlx_hook(d->win, 4, 1, ft_mouse_down, d);
	mlx_hook(d->win, 6, 1, ft_mouse_drag, d);
	mlx_hook(d->win, 5, 1, ft_mouse_up, d);
	mlx_loop(d->mlx);
}

void	ft_puterr_msg(int err)
{
	if (err == -1)
		ft_putendl("usage: .fractol/ $(param)");
	else if (err == -2)
		ft_putendl("error: mlx initializing failed");
	else if (err == -3)
		ft_putendl("error: window initializing failed");
	else if (err == -4)
		ft_putendl("error: while opening/reading a file");
	else if (err == -5)
		ft_putendl("error: memory allocation");
	else if (err == -10)
		ft_putendl("error: invalid map");
	else
		ft_putendl("error: unknown");
}

void	ft_free_n_exit(t_data *d, t_list **img_l, char *line, int err)
{
	int i;
	int j;

	(d && d->mlx && d->win) ? mlx_destroy_window(d->mlx, d->win) : 0;
	i = -1;
	if (d && d->img)
	{
		while (++i < d->img_size.z && (j = -1))
		{
			while (++j < d->img_size.y)
				free(d->img[i][j]);
			free(d->img[i]);
		}
		free(d->img);
	}
	(d && d->mlx) ? free(d->mlx) : 0;
	(d) ? free(d) : 0;
	(img_l && *img_l) ? ft_lstclr(img_l) : 0;
	(line) ? free(line) : 0;
	(err < 0) ? ft_puterr_msg(err) : 0;
	(err >= 0) ? exit(0) : exit(1);
}

void	data_init(t_data *d)
{
	d->img = NULL;
	d->o1.x = XS * 1 / 2;
	d->o1.y = YS / 2;
	d->oz.x = XS / 2;
	d->oz.y = YS / 2;
	d->zoom = 1;
	d->phi = 0;
	d->teta = 0;
	d->scale.x = 25;
	d->scale.y = 25;
	d->scale.z = 25;
	d->iter = 84;
	d->clr = 0;
	d->plrc.x = GR_S + GR_S / 2;
	d->plrc.y = 2 * GR_S + GR_S / 2;
	d->vwan.y = M_PI / 4;
	d->vwan.x = 0;
}

int		main(int argc, char **argv)
{
	t_data *d;

	if (!(argc > 1 && argv[1]))
	{
		ft_puterr_msg(-1);
		return (1);
	}
	if (!(d = (t_data*)malloc(sizeof(t_data))))
	{
		ft_puterr_msg(-5);
		return (1);
	}
	data_init(d);
	if (!(d->mlx = mlx_init()))
		ft_free_n_exit(d, NULL, NULL, -2);
	if (!(d->win = mlx_new_window(d->mlx, XS, YS, argv[1])))
		ft_free_n_exit(d, NULL, NULL, -3);
	ft_read(argv[1], d);
	ft_displayit(d, 1);
	return (0);
}
