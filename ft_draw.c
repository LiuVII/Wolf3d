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
#include <time.h>

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
	mem = (d->bpp >> 3) * x + d->ls * y;
	while (i++ < (d->bpp >> 3) - 1)
	{
		d->img_p0[mem + i] = c % 256;
		c = c >> 8;
	}
}

double	raytrace(t_data *d, double ang, double *nesw)
{
	double y;
	double x;
	double dist[2];

	dist[0] = -1;
	dist[1] = -1;
	// ang = fmod(ang, 2.0 * M_PI) + ((ang < 0) ? (2.0 * M_PI) : 0);
	// printf("| %f |", ang);
	if (ang && ang != M_PI)
	{
		y = floor(d->plrc.y / GR_S) * GR_S + ((ang < M_PI) ? -1 : GR_S + 1);
		x = d->plrc.x + (d->plrc.y - y) * cos(ang) / sin(ang);
		while (x > 0 && x < GR_S * d->img_size.x && y > 0 && y < GR_S * d->img_size.y)
		{
			//printf("| %d %d %d %f %f |", i,  (int)y / GR_S, (int)x / GR_S, d->img[0][(int)y / GR_S][(int)x / GR_S].z, ang);
			if (d->img[0][(int)y / GR_S][(int)x / GR_S].z > 0)
			{
				// printf("| %d %d %d %f %f |", i,  (int)y / GR_S, (int)x / GR_S, d->img[0][(int)y / GR_S][(int)x / GR_S].z, ang);
				d->wall.ofs.x = (int)x % GR_S;
				*nesw = (ang < M_PI) ? 4.0 : 2.0;
				dist[0] = ABS((d->plrc.y - y) / sin(ang));
				break ;
			}
			y -= SIGN(M_PI - ang) * GR_S;
			x += GR_S * cos(ang) / ABS(sin(ang));
		}
	}
	if (ang * 2 != M_PI && ang * 2 != M_PI * 3)
	{
		x = floor(d->plrc.x / GR_S) * GR_S + ((ABS(ang - M_PI) * 2 < M_PI) ? -1 : GR_S + 1);
		y = d->plrc.y + (d->plrc.x - x) * sin(ang) / cos(ang);
		while (x > 0 && x < GR_S * d->img_size.x && y > 0 && y < GR_S * d->img_size.y)
		{
			// printf("| %d %d %d %f |", i,  y / GR_S, x / GR_S, d->img[0][y / GR_S][x / GR_S].z);
			if (d->img[0][(int)y / GR_S][(int)x / GR_S].z > 0 &&
				(dist[0] > (dist[1] = ABS((d->plrc.x - x) / cos(ang))) || *nesw == 0))
			{
				d->wall.ofs.x = (int)y % GR_S;
				dist[0] = dist[1];
				*nesw = (ABS(ang - M_PI) * 2 < M_PI) ? 0.1 : 1.0;
				break ;
			}
			x += SIGN(ABS(ang - M_PI) * 2 - M_PI) * GR_S;
			y -= GR_S * sin(ang) / ABS(cos(ang));
		}
	}
	return (dist[0]);
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

int		get_color_im(int x, int y, t_img img, double shade)
{
	int		c;
	int		i;
	long	mem;

	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
		return (0);
	c = 0;
	i = (img.bpp >> 3) - 1;
	mem = (img.bpp >> 3) * x + img.ls * y;
	while (i--)
	{
		c = c << 8;
		c += (unsigned char)(img.inf[mem + i]) * (1 - shade);
	}
	return (c);
}

void	draw_line_im(t_data *d, t_3d p1, t_3d p2, t_img img)
{
	t_3d	p;
	t_2di	text_p;
	double	shade;
	double	dist;

	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
		return ;
	p.x = p1.x;
	p.y = (p1.y < 0) ? -SIGN(p2.y - p1.y) : (int)(p1.y) - SIGN(p2.y - p1.y);
	p.y = (p1.y > YS) ? YS : p.y;
	text_p.x = img.ofs.x;
	p.z = 0;
	// printf("|%d %d|", text_p.x, text_p.y);
	// (img.id == 2) ? printf("\n%.2f\n ", p.x) : 0;
	(img.id == 1) ? dist = (PP_DST * PP_DST + (XS / 2 - p.x) * (XS / 2 - p.x) + d->plrc.z * d->plrc.z) : 0;
	if (ABS(p1.y - p2.y) >= 0.01)
	{
		while ((p2.y - (p.y += SIGN(p2.y - p1.y))) * SIGN(p2.y - p1.y) >= 0 && ((SIGN(p2.y - p1.y) > 0) ? p.y <= YS : p.y >= 0))
		{
			if (img.id == 1)
			{
				text_p.y = TEXT_S * ((p.y - p1.y) / (p2.y - p1.y));
				// p.z = sqrt(dist - 2.0 * p.y * d->plrc.z + p.y * p.y) * GR_S / ABS(p2.y - p1.y);
			}
			else if (img.id == 0)
			{
				p.z = p1.z * (p1.y - PP_CY - (d->vwan.x / ANIY)) / (p.y - PP_CY - (d->vwan.x / ANIY));
				text_p.x = ((int)(d->plrc.x + floor(p.z * cos(d->ang)))) % GR_S;
				text_p.y = ((int)(d->plrc.y - floor(p.z * sin(d->ang)))) % GR_S;
			}
			else if (img.id == 2)
			{
				text_p.x = (int)(p.x) % ((img.ls * 8) / img.bpp);
				text_p.y = (int)(p.y) % YS;
			}
			shade = (p.z < 2.5 * PP_SCL) ? 0.9 * (double)p.z / PP_SCL / 2.5 : 0.9;
			draw_pixel(d, p.x, p.y, get_color_im(text_p.x, text_p.y, img, shade));
		}
	}
}

void	raycast_map(t_data *d)
{
	double	dist;
	double	h;
	t_3d	p1;
	t_3d	p2;
	double 	nesw;

	p1.x = -1;
	// d->vwan.x = 0;
	// printf("\n\n");
	// clock_t start0;
	// float start1 = 0;
	// float start2 = 0;
	// float start3 = 0;
	// float start4 = 0;
	while (++p1.x < XS)
	{
		// start0 = clock();
		h = 0;
		nesw = 0;
		d->ang = (double)(XS / 2 - p1.x) * ANIX + d->vwan.y;
		d->ang = fmod(d->ang, 2.0 * M_PI) + ((d->ang < 0) ? (2.0 * M_PI) : 0);
		dist = raytrace(d, d->ang, &nesw);
		//distance to edges of the map
		if (!nesw)
		{
			p2.y = -1;
			p2.x = -1;
			if (sin(d->ang) != 0)
				p2.y = ABS(((d->ang < M_PI) ? d->plrc.y : (d->img_size.y * GR_S - d->plrc.y)) / sin(d->ang));
			if (cos(d->ang) != 0)
				p2.x = ABS(((ABS(d->ang - M_PI) * 2 < M_PI) ? d->plrc.x : (d->img_size.x * GR_S - d->plrc.x)) / cos(d->ang));
			dist = ((p2.y >= 0 && p2.y < p2.x) || p2.x == -1) ? p2.y : p2.x;
		} 
		p2.y = YS;
		p2.x = p1.x;
		dist = dist * cos((double)(XS / 2 - p1.x) * ANIX);
		// start1 += clock() - start0;
		// start0 = clock();
		if ((h = (GR_S * PP_DST) / dist) && nesw > 0)
		{	
			// p1.z = hsv_rgb(nesw, 1, (dist < 1.5 * PP_SCL) ? 1 - 0.9 * (double)dist / PP_SCL / 1.5 : 0.1);
			p1.z = dist;
			p2.z = p1.z;
			p1.y = PP_CY + (h * (1 - d->plrc.z / YS)) + (d->vwan.x / ANIY);
			p2.y = PP_CY - (h * (d->plrc.z / YS)) + (d->vwan.x / ANIY);			
			draw_line_im(d, p1, p2, d->wall);
		}
		// start2 += clock() - start0;
		// start0 = clock();
		p1.y = 0;
		(p2.y > p1.y) ? draw_line_im(d, p1, p2, d->sky) : 0;
		// start3 += clock() - start0;
		// start0 = clock();
		p1.y = PP_CY + (h * (1 - d->plrc.z / YS)) + (d->vwan.x / ANIY);
		p2.y = YS;
		if (p1.y < p2.y)
		{
			p1.z = dist / cos((double)(XS / 2 - p1.x) * ANIX); 
			p2.z = (double)PP_DST / cos((double)(XS / 2 - p1.x) * ANIX);
			draw_line_im(d, p1, p2, d->floor);
		}
		// start4 += clock() - start0;
		if (dist < d->min_dist)
			d->min_dist = dist;
	}
	// start1 /= CLOCKS_PER_SEC;
	// start2 /= CLOCKS_PER_SEC;
	// start3 /= CLOCKS_PER_SEC;
	// start4 /= CLOCKS_PER_SEC;
	// if (d->vwan.y > -2.0 * M_PI && d->vwan.y < 2.0 * M_PI)
	// 	printf("%.2f %.3f | %.3f %.3f %.3f\n", d->vwan.y, start1 + start2 + start3 + start4, start2, start3, start4);
}

int		ft_drawit(t_data *d)
{
	d->img_p = mlx_new_image(d->mlx, XS, YS);
	d->img_p0 = mlx_get_data_addr(d->img_p, &(d->bpp), &(d->ls), &(d->endian));
	raycast_map(d);
	mlx_clear_window(d->mlx, d->win);
	// mlx_put_image_to_window(d->mlx, d->win, d->sky.ptr, 0, 0);
	mlx_put_image_to_window(d->mlx, d->win, d->img_p, 0, 0);
	mlx_destroy_image(d->mlx, d->img_p);
	return (0);
}

int		draw_win(t_data *d)
{
	t_3d p1;
	t_3d p2;
	t_3d p;

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
	mlx_put_image_to_window(d->mlx, d->win, d->img_p, (XS - d->youwin.width) / 2, (YS - d->youwin.height) / 2);
	mlx_destroy_image(d->mlx, d->img_p);
	d->mevent = 0;
	return (0);
}
