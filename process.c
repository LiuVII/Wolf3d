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
