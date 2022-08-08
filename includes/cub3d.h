/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:24:18 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/08 19:15:06 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"
# include "preprocess.h"

# define WWIDTH 800
# define WHEIGHT 600
# define MWIDTH 11
# define MHEIGHT 9
# define MAPSIZE 150
# define MMPLSIZE 3

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
}	t_data;

typedef struct s_texture
{
	int		width;
	int		height;
	t_data	*img;
}	t_texture;

typedef struct s_ray
{
	double		ray_x;
	double		ray_y;
	double		side_dx;
	double		side_dy;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	int			count_x;
	int			count_y;
	int			map_x;
	int			map_y;
	int			side;
	int			door;
	double		init_y;
	double		init_x;
	double		tex_offset;
	double		distance;
	t_texture	*texture;
}	t_ray;

typedef struct s_minimap
{
	int	scale;
	int	pos_x;
	int	pos_y;
}	t_minimap;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
	double	movespeed;
	double	rot_speed;
}	t_player;

typedef struct s_input
{
	int	mouse_pressed;
	int	rmouse_pressed;
	int	mouse_x;
	int	mouse_y;
}	t_input;

typedef struct s_door
{
	t_pos			pos;
	int				opening;
	double			animate;
	int				visible;
	int				time;
	double			tto;
	struct s_door	*next;
	struct s_door	*prev;
}	t_door;

typedef struct s_gamevars
{
	int			scale;
	void		*mlx;
	void		*mlx_win;
	t_data		*img;
	t_map		map;
	t_player	*player;
	t_minimap	*minimap;
	t_input		*input;
	t_texture	textures[5];
	int			tex_count;
	t_cub		*map_data;
	int			time;
	double		frametime;
	t_door		**doorcalls;
}	t_gamevars;

void			draw_grid(t_gamevars *gv, int scale, int off_h, int off_w);
void			draw_player(t_gamevars *gv, int scale, int off_h, int off_w);
int				drawframe(t_gamevars *gamevars);
void			draw_map(t_gamevars *gamevars);

// Initializations
void			init_gamevars(t_gamevars *gamevars);
void			inithooks(void *mlx_win, t_gamevars *gamevars);
void			init_player(t_player *player);
void			init_minimap(t_minimap *minimap);

// Input and player movement
int				mousectl(int button, int x, int y, t_gamevars *gamevars);
int				mouserel(int button, int x, int y, t_gamevars *gamevars);
int				mouserot(int x, int y, t_gamevars *gamevars);
int				keymod(int keycode, t_gamevars *gamevars);
void			player_move_ad(t_gamevars *gamevars, int fwd);
void			player_move_ws(t_gamevars *gamevars, int fwd);
void			player_rotate(t_gamevars *gamevars, int dir);

// Minimap handling
void			mini_fill(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini);
void			mini_shift(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini);

// Door animation
t_door			*new_door(int map_x, int map_y);
int				draw_door(t_gamevars *gv, int map_x, int map_y);
void			run_door(t_gamevars *gv);
void			chk_door_open(t_gamevars *gv, t_door *door, double x, double y);
int				animate_door(t_door *door, int playerhold);
double			door_ray_open(t_gamevars *gv, t_ray *ray, int map_x, int map_y);
t_door			*get_doorcall(t_gamevars *gv, int map_x, int map_y);
int				check_door_tile(t_gamevars *gv, t_ray *ray);

// Camera calculations
void			calc_ray(t_gamevars *gamevars);
double			wall_distance(t_gamevars *gamevars, t_ray *ray);
void			calc_sidedist(t_gamevars *gamevars, t_ray *ray);
double			dda(t_gamevars *gamevars, t_ray *ray);
double			get_dis(t_gamevars *gamevars, t_ray *ray, int map_x, int map_y);
int				ray_door(t_gamevars *gv, t_ray *ray, int map_x, int map_y);

// Draw calls
void			pixel_put(t_data *data, int x, int y, int color);
void			draw_wall_col(t_gamevars *gamevars, int x, t_ray *ray);
void			draw_ceiling(t_gamevars *gamevars);
void			draw_floor(t_gamevars *gamevars);

// Texture handling
int				texture_load(t_gamevars *gamevars);

// Frame time and FPS display
unsigned int	gettime(void);
unsigned int	getfps(t_gamevars *gamevars);
void			display_fps(t_gamevars *gamevars);

// Cleanup
void			cleanup(t_gamevars *gamevars);
int				end_win(t_gamevars *gamevars);

// Utils
double			dbl_abs(double n);

#endif