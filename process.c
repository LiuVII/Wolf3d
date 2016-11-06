/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:41:34 by mfilipch          #+#    #+#             */
/*   Updated: 2016/11/05 13:41:36 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	display_controls(void)
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
}

void	jump(t_data *d)
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
