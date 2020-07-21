/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 04:05:51 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/21 03:08:46 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int ft_choose_color(t_file *f, int x, int y)
{
	if (x >= f->nfil || y >= f->ncolmax)
		return (0);
	if (x == (int)f->ml.pos.x && y == (int)f->ml.pos.y)
		return (0);
	else if (f->map[x][y] == 1)
		return (C_WALL);
	else if (f->map[x][y] == 0)
		return (C_FLOOR);
	else if (f->map[x][y] == 2)
		return (C_SPRITE);
	else if (f->map[x][y] == 4)
		return (C_BORDER);
	
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
	
	texelx = M_SIZE_H / f->nfil;
	texely = M_SIZE_W / f->ncolmax;
	f->m_size_h = texelx * f->nfil;
	f->m_size_w = texely * f->ncolmax;
	f->ml.minimap.img = mlx_new_image(f->ml.mlx, f->m_size_w, f->m_size_h);
	f->ml.minimap.data = (int*)mlx_get_data_addr(f->ml.minimap.img,
		&f->ml.minimap.bits_per_pixel, &f->ml.minimap.size_line,
		&f->ml.minimap.endian);
	ft_draw_minimap(f, texelx, texely);
}
