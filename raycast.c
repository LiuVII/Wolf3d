/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:26:57 by mfilipch          #+#    #+#             */
/*   Updated: 2016/11/05 00:26:59 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	raytrace_vert(t_data *d, double ang, double *nesw, double dist)
{
	double	y;
	double	x;

	if (ang * 2 != M_PI && ang * 2 != M_PI * 3)
	{
		x = floor(d->plrc.x / GR_S) * GR_S +
		((ABS(ang - M_PI) * 2 < M_PI) ? -1 : GR_S + 1);
		y = d->plrc.y + (d->plrc.x - x) * sin(ang) / cos(ang);
		while (x > 0 && x < GR_S * d->img_size.x &&
			y > 0 && y < GR_S * d->img_size.y)
		{
			if (d->img[0][(int)y / GR_S][(int)x / GR_S].z > 0 &&
				(dist > ABS((d->plrc.x - x) / cos(ang)) || *nesw == 0))
			{
				d->wall.ofs.x = (int)y % GR_S;
				dist = ABS((d->plrc.x - x) / cos(ang));
				*nesw = (ABS(ang - M_PI) * 2 < M_PI) ? 0.1 : 1.0;
				break ;
			}
			x += SIGN(ABS(ang - M_PI) * 2 - M_PI) * GR_S;
			y -= GR_S * sin(ang) / ABS(cos(ang));
		}
	}
	return (dist);
}

double	raytrace(t_data *d, double ang, double *nesw, double dist)
{
	double	y;
	double	x;

	dist = -1;
	if (ang && ang != M_PI)
	{
		y = floor(d->plrc.y / GR_S) * GR_S + ((ang < M_PI) ? -1 : GR_S + 1);
		x = d->plrc.x + (d->plrc.y - y) * cos(ang) / sin(ang);
		while (x > 0 && x < GR_S * d->img_size.x
			&& y > 0 && y < GR_S * d->img_size.y)
		{
			if (d->img[0][(int)y / GR_S][(int)x / GR_S].z > 0)
			{
				d->wall.ofs.x = (int)x % GR_S;
				*nesw = (ang < M_PI) ? 4.0 : 2.0;
				dist = ABS((d->plrc.y - y) / sin(ang));
				break ;
			}
			y -= SIGN(M_PI - ang) * GR_S;
			x += GR_S * cos(ang) / ABS(sin(ang));
		}
	}
	return (raytrace_vert(d, ang, nesw, dist));
}

void	raycast_map(t_data *d)
{
	double	dist;
	t_3d	p1;
	t_3d	p2;
	double	nesw;

	p1.x = -1;
	while (++p1.x < XS)
	{
		nesw = 0;
		d->ang = (double)(XS / 2 - p1.x) * ANIX + d->vwan.y;
		d->ang = fmod(d->ang, 2.0 * M_PI) + ((d->ang < 0) ? (2.0 * M_PI) : 0);
		dist = raytrace(d, d->ang, &nesw, -1);
		if (!nesw && (p2.y = -1))
		{
			if ((p2.x = -1) && sin(d->ang) != 0)
				p2.y = ABS(((d->ang < M_PI) ? d->plrc.y :
					(d->img_size.y * GR_S - d->plrc.y)) / sin(d->ang));
			if (cos(d->ang) != 0)
				p2.x = ABS(((ABS(d->ang - M_PI) * 2 < M_PI) ? d->plrc.x :
					(d->img_size.x * GR_S - d->plrc.x)) / cos(d->ang));
			dist = ((p2.y >= 0 && p2.y < p2.x) || p2.x == -1) ? p2.y : p2.x;
		}
		draw_3dmap(d, p1, dist, nesw);
	}
}

int		ft_drawit(t_data *d)
{
	d->img_p = mlx_new_image(d->mlx, XS, YS);
	d->img_p0 = mlx_get_data_addr(d->img_p, &(d->bpp), &(d->ls), &(d->endian));
	raycast_map(d);
	mlx_clear_window(d->mlx, d->win);
	mlx_put_image_to_window(d->mlx, d->win, d->img_p, 0, 0);
	mlx_destroy_image(d->mlx, d->img_p);
	return (0);
}

int		draw_win(t_data *d)
{
	t_3d	p1;
	t_3d	p2;
	t_3d	p;

	d->img_p = mlx_new_image(d->mlx, XS, YS);
	d->img_p0 = mlx_get_data_addr(d->img_p, &(d->bpp), &(d->ls), &(d->endian));
	p1.x = -1;
	p1.y = 0;
	p2.x = d->youwin.width + 1;
	p2.y = d->youwin.height;
	p = p1;
	while (++p.x < p2.x)
		draw_line_im(d, p, p2, d->youwin);
	mlx_clear_window(d->mlx, d->win);
	mlx_put_image_to_window(d->mlx, d->win, d->img_p,
		(XS - d->youwin.width) / 2, (YS - d->youwin.height) / 2);
	mlx_destroy_image(d->mlx, d->img_p);
	d->mevent = 0;
	return (0);
}
