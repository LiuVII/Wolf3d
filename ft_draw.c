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

int		get_col_im(int x, int y, t_img img, double shade)
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

t_2di	get_txtr_coord(t_data *d, t_3d p1, t_3d *p, t_img img)
{
	t_2di	text_p;

	text_p.x = 0;
	text_p.y = 0;
	if (img.id == 1)
	{
		text_p.y = TEXT_S * ((p->y - p1.y) / (p1.x - p1.y));
		text_p.x = img.ofs.x;
		p->z = sqrt(img.ofs.y - 2.0 * p->y * d->plrc.z + p->y * p->y)
		* GR_S / ABS(p1.x - p1.y);
	}
	else if (img.id == 0)
	{
		p->z = p1.z * (p1.y - PP_CY - (d->vwan.x / ANIY)) /
		(p->y - PP_CY - (d->vwan.x / ANIY));
		text_p.x = ((int)(d->plrc.x + floor(p->z * cos(d->ang)))) % GR_S;
		text_p.y = ((int)(d->plrc.y - floor(p->z * sin(d->ang)))) % GR_S;
	}
	else if (img.id == 2)
	{
		text_p.x = (int)(p->x) % ((img.ls * 8) / img.bpp);
		text_p.y = (int)(p->y) % YS;
		p->z = 0;
	}
	return (text_p);
}

void	draw_line_im(t_data *d, t_3d p1, t_3d p2, t_img img)
{
	t_3d	p;
	t_2di	text_p;
	double	shade;

	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
		return ;
	p.x = p1.x;
	p.y = (p1.y < 0) ? -SIGN(p2.y - p1.y) : (int)(p1.y) - SIGN(p2.y - p1.y);
	p.y = (p1.y > YS) ? YS : p.y;
	p.z = 0;
	(img.id == 1) ? img.ofs.y = (PP_DST * PP_DST + (XS / 2 - p.x)
		* (XS / 2 - p.x) + d->plrc.z * d->plrc.z) : 0;
	if (ABS(p1.y - p2.y) >= 0.01)
	{
		while ((p2.y - (p.y += SIGN(p2.y - p1.y))) * SIGN(p2.y - p1.y) >= 0
			&& ((SIGN(p2.y - p1.y) > 0) ? p.y <= YS : p.y >= 0))
		{
			p1.x = p2.y;
			text_p = get_txtr_coord(d, p1, &p, img);
			shade = (p.z < 2.5 * PP_SCL) ? 0.9 * p.z / PP_SCL / 2.5 : 0.9;
			draw_pixel(d, p.x, p.y, get_col_im(text_p.x, text_p.y, img, shade));
		}
	}
}

void	draw_3dmap(t_data *d, t_3d p1, double dist, double nesw)
{
	double	h;
	t_3d	p2;

	p2.y = YS;
	p2.x = p1.x;
	dist = dist * cos((double)(XS / 2 - p1.x) * ANIX);
	if ((h = (GR_S * PP_DST) / dist) && nesw > 0)
	{
		p1.z = dist;
		p2.z = p1.z;
		p1.y = PP_CY + (h * (1 - d->plrc.z / YS)) + (d->vwan.x / ANIY);
		p2.y = PP_CY - (h * (d->plrc.z / YS)) + (d->vwan.x / ANIY);
		draw_line_im(d, p1, p2, d->wall);
	}
	p1.y = 0;
	(p2.y > p1.y) ? draw_line_im(d, p1, p2, d->sky) : 0;
	p1.y = PP_CY + (h * (1 - d->plrc.z / YS)) + (d->vwan.x / ANIY);
	p2.y = YS;
	if (p1.y < p2.y)
	{
		p1.z = dist / cos((double)(XS / 2 - p1.x) * ANIX);
		p2.z = (double)PP_DST / cos((double)(XS / 2 - p1.x) * ANIX);
		draw_line_im(d, p1, p2, d->floor);
	}
}
