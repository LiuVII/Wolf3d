/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 22:00:05 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 22:00:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_key_hook(int keycode, t_data *d)
{
	static int sit;

	(keycode == KEY_ESC) ? ft_free_n_exit(d, NULL, NULL, 0) : 0;
	(keycode == KEY_UP) ? d->plrc.y -= 10.0 * sin(d->vwan.y) : 0;
	(keycode == KEY_UP) ? d->plrc.x += 10.0 * cos(d->vwan.y) : 0;
	(keycode == KEY_DOWN) ? d->plrc.y += 10.0 * sin(d->vwan.y): 0;
	(keycode == KEY_DOWN) ? d->plrc.x -= 10.0 * cos(d->vwan.y) : 0;
	(keycode == KEY_LEFT) ? d->plrc.x -= 10.0 * sin(d->vwan.y) : 0;
	(keycode == KEY_LEFT) ? d->plrc.y -= 10.0 * cos(d->vwan.y) : 0;
	(keycode == KEY_RIGHT) ? d->plrc.x += 10.0 * sin(d->vwan.y) : 0;
	(keycode == KEY_RIGHT) ? d->plrc.y += 10.0 * cos(d->vwan.y) : 0;
	(keycode == KEY_4) ? d->phi += 0.05 : 0;
	(keycode == KEY_1) ? d->phi -= 0.05 : 0;
	(keycode == KEY_5) ? d->teta -= 0.05 : 0;
	(keycode == KEY_2) ? d->teta += 0.05 : 0;
	if (keycode == KEY_C)
	{
		if (sit == 0 && ++sit)
			d->plrc.z += (3 * YS) / 8.0;
		else if (sit == 1 && sit--)
			d->plrc.z -= (3 * YS) / 8.0;		 
	}
	if (keycode == KEY_SPACE && d->param == 0) 
	{
		d->jump_v += JUMP_IMP;
		d->param = 1;
	}
	if (keycode == KEY_E)
	{
		d->phi = 0;
		d->teta = 0;
	}
	if (keycode == KEY_I)
	{
		d->phi = M_PI * (35.264 / 180);
		d->teta = M_PI / 4;
	}
	// ft_putnbr(keycode);
	return (0);
}

int	ft_mouse_down(int button, int x, int y, t_data *d)
{
	if (x >= 0 && x <= XS && y >= 0 && YS <= YS)
		d->mevent = button;
	if (button == 1 || button == 2)
		d->oz.y = ((button - 1) * 2 - 1) * 5000 / PP_SCL;
	// if (button == 2)
	// {
	// 	d->o1.x += (XS / 2 - x) / d->zoom;
	// 	d->o1.y += (YS / 2 - y) / d->zoom;
	// }
	// if (button == 5)
	// {
	// 	d->o1.x -= x / d->zoom * (1 - 1 / 1.2);
	// 	d->o1.y -= y / d->zoom * (1 - 1 / 1.2);
	// 	d->zoom *= 1.2;
	// }
	// else if (button == 4)
	// {
	// 	d->o1.x -= x / d->zoom * (1 - 1.2);
	// 	d->o1.y -= y / d->zoom * (1 - 1.2);
	// 	d->zoom /= 1.2;
	// }
	return (0);
}

int	ft_mouse_up(int button, int x, int y, t_data *d)
{
	if (button)
		d->mevent = 0 * (x - y);
	if (button == 1 || button == 2)
		d->oz.y = 0;
	return (0);
}

int	ft_mouse_move(int x, int y, t_data *d)
{
	if (x >= 0 && x <= XS && y >= 0 && y <= YS)
	{
		d->teta = (XS / 2 - x) * ANIX * PP_SCL / 5000;
		if (ABS(d->teta) > M_PI / 120)
			d->teta -= SIGN(XS / 2 - x) * M_PI / 120;
		else
			d->teta = 0;
		d->phi = (YS / 2 - y) * ANIY * PP_SCL / 7000;
		if (ABS(d->phi) > M_PI / 120)
			d->phi -= SIGN(YS / 2 - y) * M_PI / 120;
		else
			d->phi = 0;
	}
	return (0);
}

int	ft_mouse_drag(int x, int y, t_data *d)
{
	if (d->mevent == 1 && x >= 0
		&& x <= XS && y >= 0 && y <= YS)
	{

	}
	return (0);
}
