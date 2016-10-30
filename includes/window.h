/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:27:50 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/23 15:27:52 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <math.h>

# define XS 800
# define YS 600
# define ZS 100
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_4 86
# define KEY_1 83
# define KEY_5 87
# define KEY_2 84
# define KEY_7 89
# define KEY_8 91
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_E 14
# define KEY_I 34
# define KEY_C 8
# define KEY_SPACE 49
# define SIGN(x) ((x < 0.0) ? -1.0 : 1.0)
# define ABS(x) ((x) * SIGN(x))

typedef struct	s_2d
{
	double		x;
	double		y;
}				t_2d;

typedef struct	s_2di
{
	int			x;
	int			y;
}				t_2di;

typedef struct	s_3d
{
	double		x;
	double		y;
	double		z;
}				t_3d;

typedef struct	s_3di
{
	int			x;
	int			y;
	int			z;
}				t_3di;

typedef struct	s_img
{
	int			id;
	void		*ptr;
	char		*inf;
	int			bpp;
	int			ls;
	int			endian;
	t_2di		ofs;
}				t_img;

typedef struct	s_data
{
	t_3d		plrc;
	t_2d		vwan;
	t_3d		***img;
	t_3d		img_size;
	void		*mlx;
	void		*win;
	void		*img_p;
	char		*img_p0;
	t_img		wall;
	t_img		floor;
	t_img		sky;
	double		phi;
	double		teta;
	double		min_dist;
	double		jump_v;
	t_2d		oz;
	int			param;
	int			bpp;
	int			ls;
	double		ang;
	int			endian;
	int			mevent;
}				t_data;

int				ft_key_hook(int keycode, t_data *d);
int				ft_mouse_move(int x, int y, t_data *d);
int				ft_mouse_down(int button, int x, int y, t_data *d);
int				ft_mouse_up(int button, int x, int y, t_data *d);
int				ft_mouse_drag(int x, int y, t_data *d);
int				ft_mouse_hook(int button, int x, int y, t_data *d);
int				ft_read(char *filename, t_data *d);
void			ft_free_n_exit(t_data *d, t_list **img_l, char *list, int err);
int				ft_drawit(t_data *d);
void			draw_pixel(t_data *d, int x, int y, int c);
void			draw_newtonset(t_data *d, int iter);
void			draw_juliaset(t_data *d, int iter);
void			draw_mandelset(t_data *d, int iter);
t_3d			ft_tr(t_data *d, t_3d p);
int				get_color(double zmin, double zmax, double zmean, double z);
int				hsv_rgb(float hue, float sat, float val);

#endif
