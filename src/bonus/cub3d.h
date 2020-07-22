/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:34:16 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/22 02:57:22 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/Xlib.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include "../../includes/minilibx-linux/mlx.h"
# include "../../includes/printf/ft_printf.h"
# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_C 99
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_M 46
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
# else
#  define KEY_ESC 53
#  define KEY_C 8
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_P 35
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_M 46
# endif
# define ROT 0.27
# define MOV 0.27
# define SIZE 640
# define D_COLOR 1.5

/*
** MINIMAP
*/
# define M_SIZE_H 130
# define M_SIZE_W 100

# define C_PLAYER 3407667
# define C_WALL 6316128
# define C_BORDER 0
# define C_FLOOR 16777215
# define C_SPRITE 16515847




typedef struct		s_save
{
	unsigned int	file_size;
	unsigned char	reserved1;
	unsigned char	reserved2;
	unsigned int	offset_bits;
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bmp;

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_sprite
{
	t_vector		pos;
	t_vector		cam_pos;
	double			distance;
	int				used;
}					t_sprite;

typedef struct		s_floor
{
	t_vector		raydir0;
	t_vector		raydir1;
	t_vector		floor;
	t_vector		flst;
	int				cellx;
	int				celly;
	int				tx;
	int				ty;
	double			posz;
	double			rowdist;
}					t_floor;


typedef struct		s_mlx
{
	int				bitspp;
	int				size_line;
	int				end;
	void			*mlx;
	void			*window;
	t_vector		plane;
	t_vector		pos;
	t_vector		dir;
	t_vector		ray;
	t_vector		deltadist;
	t_vector		raylength;
	t_vector		step;
	t_vector		map;
	double			*zbuff;
	t_sprite		*sp;
	int				*sp_order;
	t_vector		transform;
	double			inv_det;
	int				sp_screen_x;
	int				sp_height;
	int				sp_width;
	int				start_sp_x;
	int				start_sp_y;
	int				end_sp_x;
	int				end_sp_y;
	int				tex_x;
	int				tex_y;
	double			camerax;
	int				lineheight;
	double			perpwalldist;
	int				drawstart;
	int				drawend;
	int				color;
	int				x;
	int				side;
	t_img			frame;
	t_img			text[7];
	t_img			minimap;
	t_img			mano;
	t_img			bat;
	int				t_side;
	double			wallx;
	int				textx;
	int				texty;
	double			textstep;
	double			textpos;
}					t_mlx;

typedef struct		s_mov
{
	int				a;
	int				s;
	int				w;
	int				d;
	int				r;
	int				l;
	int				m;
}					t_mov;

typedef struct		s_readfile
{
	int				fd;
	int				w;
	int				h;
	int				texture[4];
	int				sprite;
	char			*line;
	int				c_f;
	int				cf[3];
	int				c_c;
	int				cc[3];
	int				**map;
	int				**c_map;
	char			dir;
	int				pos[2];
	int				mapreaded;
	int				ncolmax;
	int				nfil;
	char			*buff;
	int				rtn;
	int				sprite_num;
	int				save;
	int				read[8];
	int				**minimap;
	int				m_size_h;
	int				m_size_w;
	t_sprite		*spr;
	t_mlx			ml;
	t_mov			mv;
	t_floor			fl;
}					t_file;

/*
** errors
*/

void				ft_handle_error_aux(char *str, void *aux);
void				ft_handle_error_ptr(char *str, void ***aux);
void				ft_handle_error(char *str);
void				ft_free(void ***ptr);

/*
** ft_read_src_file(); utils
*/

int					ft_read(t_file *f);
int					ft_read_src_file(t_file *f);
int					ft_read_src_file2(t_file *f);
int					ft_handle_resolution(t_file *f);
int					ft_handle_textures(t_file *f);
int					ft_check_extension(char *str);
int					ft_handle_spritex(t_file *f);
int					ft_handle_rgb(t_file *f);
int					alloc_map(t_file *f);
int					ft_map_check(int row, int col, t_file *f);
int					ft_handle_croof(t_file *f);
int					ft_handle_cfloor(t_file *f);
int					ft_handle_map_read(t_file *f);
int					ft_check_config(t_file *f);
int					ft_copy_map(t_file *f);
/*
** RAY CASTER ENGINE
*/

int					ft_initraycast(t_file *f);
int					ft_exit_game(t_file *f);
void				ft_init_rc(t_file *f);
void				ft_fixing_def(t_file *f);
void				ft_init_mlx_struct(t_file *f);
void				ft_init_mlx_struct2(t_file *f);
void				ft_init_file_struct(t_file *f);
void				ft_init_file_struct2(t_file *f);
void				ft_calc_step(t_file *f);
void				ft_calc_side(t_file *f);
int					ft_dark_color(double distance, int color);

/*
** MOVIMIENTO ARCHIVO: ft_move.c
*/

void				ft_print_map(t_file *f);
int					ft_check_and_move(t_file *f);
void				ft_draw_line(t_file *f);
void				ft_cast_init_dir(t_file *f);
int					ft_move_and_draw(t_file *f);
int					ft_key_press(int key, t_file *f);
int					ft_key_release(int key, t_file *f);
void				ft_move_l(t_file *f);
void				ft_move_r(t_file *f);
void				ft_rot_l(t_file *f, double dirxaux, double planexaux);
void				ft_rot_r(t_file *f, double dirxaux, double planexaux);
void				ft_move_dwn(t_file *f);
void				ft_move_up(t_file *f);
int					ft_canmove(int x);

/*
**	SPRITES
*/

void				ft_sprite(t_file *f);
void				ft_init_sp(t_file *f);
void				ft_calc_rel_dist(t_file *f);

/*
** SAVE
*/

void				ft_init_bmp_header(t_file *f, t_bmp *bmp);
void				ft_create_bmp(t_file *f);

/*
** SKYBOX
*/

void				ft_init_texture(t_file *f);
void				ft_draw_sky(t_file *f);
void    			ft_draw_floor(t_file *f);

/*
** MINIMAP
*/

void				ft_init_minimap(t_file *f);
void				ft_create_minimap(t_file *f);
void				ft_draw_minimap(t_file *f, int texx, int texy);

#endif
