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
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int		ft_displayit(t_data *d/*, int flag*/)
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
	// (flag == 0) ? ft_free_n_exit(d, NULL, NULL, -1) : 0;
	static pid_t pid = -1;
	int wstatus;
	mlx_expose_hook(d->win, ft_drawit, d);
	mlx_key_hook(d->win, ft_key_hook, d);
	mlx_hook(d->win, 17, 1, ft_close, d);
	mlx_hook(d->win, 4, 1, ft_mouse_down, d);
	//mlx_hook(d->win, 6, 1, ft_mouse_drag, d);
	mlx_hook(d->win, 6, 1, ft_mouse_move, d);
	mlx_hook(d->win, 5, 1, ft_mouse_up, d);
	if (d->img[0][(int)(d->plrc.y) / GR_S][(int)(d->plrc.x) / GR_S].z == -1)
		draw_win(d);
	else
	{
		if (d->param == 0 && d->mevent == 1 && (waitpid(pid, &wstatus, WNOHANG)))
		{
			pid = fork();
			while (pid == 0)
			{
				execlp("afplay", "-q", "sound/ftstp.mp3", 0);
				exit (0);
			}
		}
		d->vwan.y = fmod(d->vwan.y + d->teta + M_PI, 2.0 * M_PI) - M_PI;
		if (d->param == 1)
		{
			d->plrc.z -= d->jump_v;
			if (d->jump_v > -JUMP_IMP + GRAV_C / 2)
				d->jump_v -= GRAV_C;
			else
			{
				d->jump_v = 0;
				d->param = 0;
				system("afplay sound/land.mp3 &");
			}			
		}
		if (d->vwan.x + (d->plrc.z - YS / 2) * ANIY + d->phi < M_PI / 3.0
			&& d->vwan.x + d->phi > -M_PI / 3.0)
			d->vwan.x += d->phi;
		if (d->img[0][(int)(d->plrc.y - (d->oz.y + 10 * SIGN(d->oz.y)) * SIGN(sin(d->vwan.y))) / GR_S]
			[(int)(d->plrc.x) / GR_S].z <= 0)
			d->plrc.y -= d->oz.y * sin(d->vwan.y);
		if (d->img[0][(int)(d->plrc.y) / GR_S]
			[(int)(d->plrc.x + (d->oz.x + 10 * SIGN(d->oz.y)) * SIGN(cos(d->vwan.y))) / GR_S].z <= 0)
			d->plrc.x += d->oz.y * cos(d->vwan.y);
		// clock_t start = clock();
		ft_drawit(d);
		// clock_t end = clock();
		// float seconds = (float)(end - start) / CLOCKS_PER_SEC;
		// printf("angle %.2f seconds %.2f \n", d->vwan.y, seconds);
	}
	if (pid != -1 && (d->mevent == 0 || d->param == 1))
	{
		// execlp("kill", "-s", ft_itoa(pid), 9);
		kill(pid, SIGKILL);
		pid = -1;
	}
	// mlx_loop(d->mlx);
	return (0);
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
	// system("killall afplay");
	(err >= 0) ? exit(0) : exit(1);
}

void	data_init(t_data *d, char *map_name)
{
	// int width;
	// int height;

	// width = XS;
	// height = YS;
	d->img = NULL;
	d->run = 0;
	d->oz.x = 0;
	d->oz.y = 0;
	d->jump_v = 0;
	d->min_dist = PP_SCL;
	d->phi = 0;
	d->teta = 0;
	if (ft_strcmp(map_name, "maps/01") == 0)
	{
		d->plrc.x = GR_S + GR_S / 2;
		d->plrc.y = 2 * GR_S + GR_S / 2;
	}
	else if (ft_strcmp(map_name, "maps/medium") == 0)
	{
		d->plrc.x = GR_S + GR_S / 2;
		d->plrc.y = 22 * GR_S + GR_S / 2;
	}		
	d->param = 0;
	d->plrc.z = PP_CY;
	d->vwan.y = M_PI / 4;
	d->vwan.x = 0;
	// d->img_p= mlx_xpm_file_to_image(d->mlx, "wallwindow2.xpm", &width, &height);
	(d->wall).ptr= mlx_xpm_file_to_image(d->mlx, "textures/wl_da.xpm", &(d->wall.width), &(d->wall.height));
	(d->wall).inf = mlx_get_data_addr((d->wall).ptr, &((d->wall).bpp), &((d->wall).ls), &((d->wall).endian));
	(d->floor).ptr= mlx_xpm_file_to_image(d->mlx, "textures/flr_wd.xpm", &(d->floor.width), &(d->floor.height));
	(d->floor).inf = mlx_get_data_addr((d->floor).ptr, &((d->floor).bpp), &((d->floor).ls), &((d->floor).endian));
	(d->sky).ptr= mlx_xpm_file_to_image(d->mlx, "textures/sky.xpm", &(d->sky.width), &(d->sky.height));
	(d->sky).inf = mlx_get_data_addr((d->sky).ptr, &((d->sky).bpp), &((d->sky).ls), &((d->sky).endian));
	(d->youwin).ptr= mlx_xpm_file_to_image(d->mlx, "textures/youwin.xpm", &(d->youwin.width), &(d->youwin.height));
	(d->youwin).inf = mlx_get_data_addr((d->youwin).ptr, &((d->youwin).bpp), &((d->youwin).ls), &((d->youwin).endian));
	// printf("sky width %d height %d\n", width, height);
	d->wall.id = 1;
	d->floor.id = 0;
	d->sky.id = 2;
	d->youwin.id = 2;
	// printf("sky bpp %d ls %d endian %d\n", (d->sky.bpp >> 3), d->sky.ls, d->sky.endian);
}

int		main(int argc, char **argv)
{
	t_data *d;
	// pid_t	x;

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
	if (!(d->mlx = mlx_init()))
		ft_free_n_exit(d, NULL, NULL, -2);
	if (!(d->win = mlx_new_window(d->mlx, XS, YS, argv[1])))
		ft_free_n_exit(d, NULL, NULL, -3);
	data_init(d, argv[1]);
	ft_read(argv[1], d);
	// x = fork();
	// if (x < 0)
	// 	ft_free_n_exit(d, NULL, NULL, -2);
	// else if (!x)
		// system("afplay music/Koan_Castle.mp3 &");
	// else
	{
		mlx_loop_hook(d->mlx, ft_displayit, d);
		mlx_loop(d->mlx);
	}
	// ft_displayit(d, 1);
	return (0);
}
