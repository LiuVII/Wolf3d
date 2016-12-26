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
	ft_putstr("\
____________________________________\n\
CONTROLS:\n\
Movement:\n\
	W, S: forward, back\n\
	A, D: rotatiion left, right\n\
	Mouse move: rotations left, right, up, down\n\
	Jump: Space\n\
	Run: Shift(hold)\n\
Exit:\n\
	ESC\n\
____________________________________\n");
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
