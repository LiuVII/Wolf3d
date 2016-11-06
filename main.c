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

int		ft_displayit(t_data *d)
{
	static pid_t pid = -1;
	int wstatus;

	mlx_expose_hook(d->win, ft_drawit, d);
	mlx_key_hook(d->win, ft_key_hook, d);
	mlx_hook(d->win, 17, 1, ft_close, d);
	if (d->img[0][(int)(d->plrc.y) / GR_S][(int)(d->plrc.x) / GR_S].z == -1)
		draw_win(d);
	else
	{
		if (d->param == 0 && d->mevent == 1 && (waitpid(pid, &wstatus, WNOHANG)) && !(pid = fork()))
		{
			execlp("afplay", "-q", "sound/ftstp.mp3", 0);
			exit (0);
		}
		ft_drawit(d);
	}
	if (pid != -1 && (d->mevent == 0 || d->param == 1))
	{
		// execlp("kill", "-s", ft_itoa(pid), 9);
		kill(pid, SIGKILL);
		pid = -1;
	}
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

	destroy_txtr(d);
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
	d->img = NULL;
	d->run = 0;
	d->oz.x = 0;
	d->oz.y = 0;
	d->jump_v = 0;
	d->min_dist = PP_SCL;
	d->phi = 0;
	d->teta = 0;
	if (ft_strcmp(map_name, "maps/0") == 0)
	{
		d->plrc.x = 0 + GR_S / 2;
		d->plrc.y = 0 + GR_S / 2;
	}
	if (ft_strcmp(map_name, "maps/1") == 0)
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
	load_txtr(d);
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
	display_controls();
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
