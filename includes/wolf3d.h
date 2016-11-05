/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:27:50 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/23 15:27:52 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "window.h"

# define FOV (M_PI / 3.0)
# define GR_S 256
# define PP_DST (XS / 2.0 / tan(FOV / 2.0))
# define ANIX (FOV / (double)XS)
# define ANIY (FOV / (double)YS)
# define PP_CX (XS / 2)
# define PP_CY (YS / 2)
# define PP_SCL sqrt(XS * XS + YS * YS)
# define GRAV_C 1
# define JUMP_IMP (((int)sqrt(GRAV_C * YS / 2.0) / GRAV_C) * GRAV_C)
# define TEXT_S GR_S

int				draw_win(t_data *d);
void			draw_3dmap(t_data *d, t_3d p1, double dist, double nesw);

#endif
