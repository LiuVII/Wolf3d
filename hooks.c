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

int	ft_close(t_data *d)
{
	ft_free_n_exit(d, NULL, NULL, 0);
	return (0);
}

int	ft_key_down(int keycode, t_data *d)
{
	static int sit;

	(keycode == KEY_ESC) ? ft_free_n_exit(d, NULL, NULL, 0) : 0;
	if (keycode == KEY_W && (d->mevent = 1))
		d->oz.y = 1;
	if (keycode == KEY_S && (d->mevent = 2))
		d->oz.y = -1;
	(keycode == KEY_A) ? d->teta = 3 * M_PI / 120 : 0;
	(keycode == KEY_D) ? d->teta = -3 * M_PI / 120 : 0;
	(keycode == KEY_LSHFT) ? d->run = 1 : 0;
	if (keycode == KEY_C)
	{
		d->plrc.z += (1 - sit * 2.0) * (3 * YS) / 8.0;
		sit = (sit + 1) % 2;
	}
	if (keycode == KEY_SPACE && d->param == 0)
	{
		d->jump_v += JUMP_IMP;
		d->param = 1;
		system("afplay sound/jump2.mp3 &");
	}
	d->oz.y = ((d->oz.y != 0) ? SIGN(d->oz.y) : 0)
	* 15000 * (1 + 0.5 * d->run) / PP_SCL;
	return (0);
}

int	ft_key_up(int keycode, t_data *d)
{
	if ((keycode == KEY_W && (d->mevent == 1)) ||
		(keycode == KEY_S && (d->mevent == 2)))
	{
		d->mevent = 0;
		d->oz.y = 0;
	}
	(keycode == KEY_A) ? d->teta = 0 : 0;
	(keycode == KEY_D) ? d->teta = 0 : 0;
	(keycode == KEY_LSHFT) ? d->run = 0 : 0;
	d->oz.y = ((d->oz.y != 0) ? SIGN(d->oz.y) : 0)
	* 15000 * (1 + 0.5 * d->run) / PP_SCL;
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

/*
**FNCTIONS LEFT FROM MOUSE-BASED CONTROL (COULD BE USED AGAIN LATER)
**int	ft_mouse_down(int button, int x, int y, t_data *d)
**{
**	if (x >= 0 && x <= XS && y >= 0 && YS <= YS)
**	 	d->mevent = button;
**	if (button == 1 || button == 2)
**	{
**		d->mevent += 1;
**		d->oz.y = (1 - (button - 1) * 2) * 15000 * (1 + 0.5 * d->run) / PP_SCL;
**	}
**	return (0);
**}
**int	ft_mouse_up(int button, int x, int y, t_data *d)
**{
**	if (button)
**	 	d->mevent = 0 * (x - y);
**	if (button == 1 || button == 2)
**	{
**		d->mevent = 0;
**		d->oz.y = 0;
**	}
**	return (0);
**}
**
**OLD KEYHOOK FUNC: if it would be useful to return back to mousce controls
**int	ft_key_hook(int keycode, t_data *d)
**{
**	static int sit;
**
**	(keycode == KEY_ESC) ? ft_free_n_exit(d, NULL, NULL, 0) : 0;
**	(keycode == KEY_UP) ? d->plrc.y -= 10.0 * sin(d->vwan.y) : 0;
**	(keycode == KEY_UP) ? d->plrc.x += 10.0 * cos(d->vwan.y) : 0;
**	(keycode == KEY_DOWN) ? d->plrc.y += 10.0 * sin(d->vwan.y) : 0;
**	(keycode == KEY_DOWN) ? d->plrc.x -= 10.0 * cos(d->vwan.y) : 0;
**	(keycode == KEY_LEFT) ? d->plrc.x -= 10.0 * sin(d->vwan.y) : 0;
**	(keycode == KEY_LEFT) ? d->plrc.y -= 10.0 * cos(d->vwan.y) : 0;
**	(keycode == KEY_RIGHT) ? d->plrc.x += 10.0 * sin(d->vwan.y) : 0;
**	(keycode == KEY_RIGHT) ? d->plrc.y += 10.0 * cos(d->vwan.y) : 0;
**	(keycode == 15) ? d->run = (d->run + 1) % 2 : 0;
**	if (keycode == KEY_C)
**	{
**		d->plrc.z += (1 - sit * 2.0) * (3 * YS) / 8.0;
**		sit = (sit + 1) % 2;
**	}
**	if (keycode == KEY_SPACE && d->param == 0)
**	{
**		d->jump_v += JUMP_IMP;
**		d->param = 1;
**		system("afplay sound/jump2.mp3 &");
**	}
**	return (0);
**}
*/
