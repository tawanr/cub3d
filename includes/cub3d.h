/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:24:18 by tratanat          #+#    #+#             */
/*   Updated: 2022/08/11 10:41:24 by spoolpra         ###   ########.fr       */
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
# include "input_keys.h"

# define WWIDTH 800
# define WHEIGHT 600
# define MWIDTH 11
# define MHEIGHT 9
# define MAPSIZE 150
# define MMPLSIZE 3
# define USEC 1000000
# define BLK 0x00FFFFFF

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

typedef struct s_fpos
{
	double	x;
	double	y;
}	t_fpos;

typedef struct s_player
{
	int		moved;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
	double	movespeed;
	double	rot_speed;
	t_fpos	last_pos;
}	t_player;

typedef struct s_input
{
	int	mouse_cam;
	int	mouse_pressed;
	int	rmouse_pressed;
	int	mouse_x;
	int	mouse_y;
	int	w_down;
	int	a_down;
	int	s_down;
	int	d_down;
	int	up_down;
	int	left_down;
	int	down_down;
	int	right_down;
	int	q_down;
	int	e_down;
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

typedef struct s_object
{
	t_pos			pos;
	t_texture		**textures;
	int				frames;
	double			scale;
	int				animate;
	int				visible;
	int				time;
	double			ani_loop;
	double			depth;
	double			sx;
	double			sy;
	struct s_object	*next;
	struct s_object	*prev;
}	t_object;

typedef struct s_draw
{
	int		height;
	int		width;
	int		screenx;
	int		startx;
	int		starty;
	int		endx;
	int		endy;
	int		off;
	double	tx;
	double	ty;
}	t_draw;

typedef struct s_sprite
{
	t_texture	**frames;
	int			count;
}	t_sprite;

typedef struct s_debug
{
	int	border;
}	t_debug;

typedef struct s_gamevars
{
	int			scale;
	int			tex_count;
	int			time;
	int			framecount;
	void		*mlx;
	void		*mlx_win;
	double		frametime;
	double		zd[WWIDTH];
	t_map		map;
	t_cub		*map_data;
	t_data		*img;
	t_data		*buffer[2];
	t_player	*player;
	t_minimap	*minimap;
	t_input		*input;
	t_texture	textures[5];
	t_sprite	sprite;
	t_door		**doorcalls;
	t_object	**objectque;
	t_debug		debug;
}	t_gamevars;

// Initializations
void			init_gamevars(t_gamevars *gamevars);
void			inithooks(void *mlx_win, t_gamevars *gamevars);
void			init_player(t_gamevars *gv, t_player *player);
void			init_minimap(t_minimap *minimap);
void			init_keys(t_gamevars *gv);
void			init_debug(t_gamevars *gv);

// Input and player movement
void			player_play(t_gamevars *gv);
int				mousectl(int button, int x, int y, t_gamevars *gamevars);
int				mouserel(int button, int x, int y, t_gamevars *gamevars);
int				mouserot(int x, int y, t_gamevars *gamevars);
int				keymod(int keycode, t_gamevars *gamevars);
void			player_move_ad(t_gamevars *gamevars, int fwd);
void			player_move_ws(t_gamevars *gamevars, int fwd);
void			player_rotate(t_gamevars *gamevars, int dir);
int				keypress(int keycode, t_gamevars *gv);
int				keypress_cont(int keycode, t_gamevars *gv);
int				keyrelease(int keycode, t_gamevars *gv);
int				keyrelease_cont(int keycode, t_gamevars *gv);
void			check_pos(t_gamevars *gv);
int				mousetrack(t_gamevars *gv);

// Minimap handling
void			draw_grid(t_gamevars *gv, t_minimap *m);
void			draw_player(t_gamevars *gv, int scale, int off_h, int off_w);
int				drawframe(t_gamevars *gamevars);
void			draw_map(t_gamevars *gamevars);
void			mini_fill(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini);
void			mini_shift(t_gamevars *gv, t_pos *m, t_pos *d, t_minimap *mini);
int				tile_color(int type);

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
void			dda_stepy(t_ray *ray, int *map_y);
double			get_dis(t_gamevars *gamevars, t_ray *ray, int map_x, int map_y);
int				ray_door(t_gamevars *gv, t_ray *ray, int map_x, int map_y);

// Draw calls
void			pixel_put(t_data *data, int x, int y, int color);
void			draw_wall_col(t_gamevars *gamevars, int x, t_ray *ray);
void			draw_ceiling(t_gamevars *gamevars);
void			draw_floor(t_gamevars *gamevars);

// Debug functions
int				check_border(double x_off, double tex_pos, int *color, int b);

// Texture handling
int				texture_load(t_gamevars *gamevars);
void			assign_textures(t_gamevars *gv, char **path);
int				texture_file(t_gamevars *gv, t_texture *tex, char *path, int i);

// Sprite handling
int				new_sprite(t_gamevars *gv, char *path);
int				sprite_texture(t_gamevars *gv, int frame, char *path, int pos);
int				sprite_load(t_gamevars *gv);

// Object handling
void			add_object(t_gamevars *gv, int map_x, int map_y);
t_object		*new_object(t_gamevars *gv, int map_x, int map_y);
void			run_objectque(t_gamevars *gv);
void			draw_object(t_gamevars *gv, t_object *obj);
void			draw_obj_col(t_gamevars *gv, t_draw *s, t_object *obj, int x);
void			init_object_draw(t_gamevars *gv, t_object *obj, t_draw *s);

// Frame time and FPS display
unsigned int	gettime(void);
unsigned int	getfps(t_gamevars *gamevars);
unsigned int	ft_difftime(unsigned int t1);
void			display_fps(t_gamevars *gamevars);

// Cleanup
void			cleanup(t_gamevars *gamevars);
int				end_win(t_gamevars *gamevars);
void			clean_sprite(t_gamevars *gv, int couunt);
void			clean_textures(t_gamevars *gv, int count);
void			clean_doorcalls(t_gamevars *gv);
void			clean_objque(t_gamevars *gv);

// Utils
double			dbl_abs(double n);
int				rgb_to_int(t_rgb *rgb);

// Error handling
int				texture_err(t_gamevars *gv, int loaded);
int				sprite_err(t_gamevars *gv, int frame, char *path);
int				cleanup_err(t_gamevars *gv);

#endif
