/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:41:46 by mfilipch          #+#    #+#             */
/*   Updated: 2016/11/05 13:41:48 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	load_txtr(t_data *d)
{
	(d->wall).ptr = mlx_xpm_file_to_image(d->mlx, "textures/wl_da.xpm",
		&(d->wall.width), &(d->wall.height));
	(d->wall).inf = mlx_get_data_addr((d->wall).ptr, &((d->wall).bpp),
		&((d->wall).ls), &((d->wall).endian));
	(d->floor).ptr = mlx_xpm_file_to_image(d->mlx, "textures/flr_wd.xpm",
		&(d->floor.width), &(d->floor.height));
	(d->floor).inf = mlx_get_data_addr((d->floor).ptr, &((d->floor).bpp),
		&((d->floor).ls), &((d->floor).endian));
	(d->sky).ptr = mlx_xpm_file_to_image(d->mlx, "textures/360sky_10c.xpm",
		&(d->sky.width), &(d->sky.height));
	(d->sky).inf = mlx_get_data_addr((d->sky).ptr, &((d->sky).bpp),
		&((d->sky).ls), &((d->sky).endian));
	(d->sky1).ptr = mlx_xpm_file_to_image(d->mlx, "textures/360sky_11c.xpm",
		&(d->sky1.width), &(d->sky1.height));
	(d->sky1).inf = mlx_get_data_addr((d->sky1).ptr, &((d->sky1).bpp),
		&((d->sky1).ls), &((d->sky1).endian));
	(d->youwin).ptr = mlx_xpm_file_to_image(d->mlx, "textures/youwin.xpm",
		&(d->youwin.width), &(d->youwin.height));
	(d->youwin).inf = mlx_get_data_addr((d->youwin).ptr, &((d->youwin).bpp),
		&((d->youwin).ls), &((d->youwin).endian));
	d->wall.id = 1;
	d->floor.id = 0;
	d->sky.id = 2;
	d->sky1.id = 2;
	d->youwin.id = 3;
}

void	destroy_txtr(t_data *d)
{
	if (d && d->mlx)
	{
		(d->wall.ptr) ? mlx_destroy_image(d->mlx, d->wall.ptr) : 0;
		(d->floor.ptr) ? mlx_destroy_image(d->mlx, d->floor.ptr) : 0;
		(d->sky.ptr) ? mlx_destroy_image(d->mlx, d->sky.ptr) : 0;
		(d->sky1.ptr) ? mlx_destroy_image(d->mlx, d->sky1.ptr) : 0;
		(d->youwin.ptr) ? mlx_destroy_image(d->mlx, d->youwin.ptr) : 0;
	}
}
