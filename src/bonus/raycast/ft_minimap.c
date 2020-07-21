/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 04:05:51 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/21 18:40:04 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define MANO "./textures/images/horror/mano_ipad.xpm"

static int ft_choose_color(t_file *f, int x, int y)
{
	if (x >= f->nfil || y >= f->ncolmax)
		return (0);
	if (x == (int)f->ml.pos.x && y == (int)f->ml.pos.y)
		return (C_PLAYER);
	else if (f->map[x][y] == 1)
		return (C_WALL);
	else if (f->map[x][y] == 0)
		return (C_FLOOR);
	else if (f->map[x][y] == 2)
		return (C_SPRITE);
	else if (f->map[x][y] == 4)
		return (C_FLOOR);
	
}

void	ft_draw_minimap(t_file *f, int texx, int texy)
{
	int x;
	int y;
	int k;
	int l;

	k = 0;
	l = 0;
	y = -1;
	while (++y < f->m_size_h)
	{
		x = -1;
		while (++x < f->m_size_w)
		{
			l = x / texx;
			k = y / texy;
			*(f->ml.minimap.data + (y * (f->m_size_w)) +(x)) = ft_choose_color(f, k, l);
		}
	}
}

void	ft_init_minimap(t_file *f)
{
	int texelx;
	int texely;
	int	aux_w;
	int aux_h;
	
	if (f->h < M_SIZE_H)
		aux_h = f->h;
	else
		aux_h = M_SIZE_H;
	if (f->w < M_SIZE_W)
		aux_w = f->w;
	else
		aux_w = M_SIZE_W;
	texelx = aux_h / f->nfil;
	texely = aux_w / f->ncolmax;
	f->m_size_h = texelx * f->nfil;
	f->m_size_w = texely * f->ncolmax;
	f->ml.minimap.img = mlx_new_image(f->ml.mlx, f->m_size_w, f->m_size_h);
	f->ml.minimap.data = (int*)mlx_get_data_addr(f->ml.minimap.img,
		&f->ml.minimap.bits_per_pixel, &f->ml.minimap.size_line,
		&f->ml.minimap.endian);
	f->ml.mano.img = mlx_xpm_file_to_image(f->ml.mlx, MANO,
	&f->ml.mano.width, &f->ml.mano.height);
	ft_draw_minimap(f, texelx, texely);
}
