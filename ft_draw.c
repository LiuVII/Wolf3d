/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 22:56:04 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/18 22:56:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int		hsv_rgb(float hue, float sat, float val)
{
	float		rgb[3];
	float		x;
	float		c;

	c = sat * val;
	x = c * (1 - ABS(fmod(hue, 2) - 1));
	rgb[0] = (val * (1 - c) + c * (hue < 1 || hue >= 5)
		+ x * ((hue >= 1 && hue < 2) || (hue >= 4 && hue < 5))) * 255;
	rgb[1] = (val * (1 - c) + c * (hue >= 1 && hue < 3)
		+ x * ((hue >= 0 && hue < 1) || (hue >= 3 && hue < 4))) * 255;
	rgb[2] = (val * (1 - c) + c * (hue >= 3 && hue < 5)
		+ x * ((hue >= 2 && hue < 3) || (hue >= 5 && hue < 6))) * 255;
	return (((int)rgb[0] << 16) + ((int)rgb[1] << 8) + rgb[2]);
}

int		set_color(t_3d p1, t_3d p2, t_3d p, int flag)
{
	p.z = p1.z;
	if (flag == 1)
		p.z += (p2.z - p1.z) * (p.x - p1.x) / (p2.x - p1.x);
	else if (flag == 2)
		p.z += (p2.z - p1.z) * (p.y - p1.y) / (p2.y - p1.y);
	return (p.z);
}

void	draw_pixel(t_data *d, int x, int y, int c)
{
	int		i;
	long	mem;

	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
		return ;
	i = -1;
	mem = d->bpp / 8 * x + d->ls * y;
	while (i++ < d->bpp / 8 - 1)
	{
		d->img_p0[mem + i] = c % 256;
		c = c / 256;
	}
}

int	raytrace(t_data *d, double ang)
{
	int y;
	int x;
	int i;
	int dist[2];

	dist[0] = -1;
	dist[1] = -1;
	//correct in case of diff ang
	ang = fmod(ang, 2.0 * M_PI) + ((ang < 0) ? (2.0 * M_PI) : 0);
	i = d->plrc.y / GR_S + 1;
	if (ang && ang != M_PI)
	{
		y = floor(d->plrc.y / GR_S) * GR_S + ((ang < M_PI) ? -1 : GR_S);
		x = d->plrc.x + (d->plrc.y - y) * cos(ang) / sin(ang);
	//correct in case of diff ang
		while (x > 0 && x < XS && y > 0 && y < YS/* && --i*/)
		{
			// printf("| %d %d %d %f |", i,  y / GR_S, x / GR_S, d->img[0][y / GR_S][x / GR_S].z);
			if (d->img[0][y / GR_S][x / GR_S].z > 0)
			{
				dist[0] = ABS((d->plrc.y - y) / sin(ang));
				break ;
			}
			y -= SIGN(M_PI - ang) * GR_S;
			x += GR_S * cos(ang) / sin(ang);
		}
	}
	i = d->plrc.x / GR_S + 1;
	if (ang * 2 != M_PI && ang * 2 != M_PI * 3)
	{
		x = floor(d->plrc.x / GR_S) * GR_S + ((ABS(ang - M_PI) * 2 < M_PI) ? -1 : GR_S);
		y = d->plrc.y + (d->plrc.x - x) * sin(ang) / cos(ang);
	//correct in case of diff ang
		while (x > 0 && x < XS && y > 0 && y < YS/* && --i*/)
		{
			// printf("| %d %d %d %f |", i,  y / GR_S, x / GR_S, d->img[0][y / GR_S][x / GR_S].z);
			if (d->img[0][y / GR_S][x / GR_S].z > 0)
			{
				dist[1] = ABS((d->plrc.x - x) / cos(ang));
				break ;
			}
			x += SIGN(ABS(ang - M_PI) * 2 - M_PI) * GR_S;
			y += GR_S * sin(ang) / cos(ang);
		}
	}
	if ((dist[0] < dist[1] && dist[0] > 0) || dist[1] == -1)
		return (dist[0]);
	return (dist[1]);
}

void	draw_line(t_data *d, t_3d p1, t_3d p2)
{
	t_3d	p;
	t_2d	a;
	t_2d	b;
	float	dist;

	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
		return ;
	p.x = p1.x;
	p.y = p1.y;
	dist = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	if (ABS(p2.x - p1.x) >= ABS(p2.y - p1.y) && ABS(p1.x - p2.x) / dist >= 0.01)
	{
		a.x = (p2.y - p1.y) / (p2.x - p1.x);
		b.x = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
		while ((p2.x - (p.x += (p2.x - p1.x) / dist)) * SIGN(p2.x - p1.x) >= 0)
			draw_pixel(d, p.x, a.x * p.x + b.x, set_color(p1, p2, p, 1));
	}
	else if (ABS(p1.y - p2.y) / dist >= 0.01)
	{
		a.y = (p2.x - p1.x) / (p2.y - p1.y);
		b.y = (p1.x * p2.y - p2.x * p1.y) / (p2.y - p1.y);
		while ((p2.y - (p.y += (p2.y - p1.y) / dist)) * SIGN(p2.y - p1.y) >= 0)
			draw_pixel(d, a.y * p.y + b.y, p.y, set_color(p1, p2, p, 2));
	}
}

void	raycast_map(t_data *d)
{
	int		dist;
	int		h;
	t_3d	p1;
	t_3d	p2;

	p1.x = -1;
	while (++p1.x < XS)
	{
		p2.x = p1.x;
		dist = raytrace(d, (double)(XS / 2 - p1.x) * ANI + d->vwan.y);
		dist = dist * cos((double)(XS / 2 - p1.x) * ANI);
		// ((int)p1.x % 100) ? printf("%d, %f\n", dist, (double)(XS / 2 - p1.x) * ANI + d->vwan.y) : 0;
		if (dist > 0 && (h = (GR_S * PP_DST) / dist))
		{	
			p1.z = hsv_rgb(fmod((double)dist / 1000.0 * 6.0, 6), 1, 1 - (double)dist / 500.0);
			p2.z = p1.z;
			// printf("%d\n", (int)p1.z);
			p1.y = PP_CY + h / 2;
			p2.y = PP_CY - h / 2;
			draw_line(d, p1, p2);
		}
		// p2.y = 0;
		// draw_line(d, p1, p2, dist);
		// p1.y = PP_CY - h / 2;
		// p2.y = YS;
		// draw_line(d, p1, p2, dist);
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
