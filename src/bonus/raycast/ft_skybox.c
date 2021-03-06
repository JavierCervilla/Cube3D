/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skybox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 04:04:14 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/22 04:09:58 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		ft_init_texture(t_file *f)
{
	int		i;
	char	*texture;

	texture = "./textures/images/own/skybox.xpm";
	f->ml.text[5].img = mlx_xpm_file_to_image(f->ml.mlx, texture,
	&f->ml.text[5].width, &f->ml.text[5].height);
	f->ml.text[5].data = (int *)mlx_get_data_addr(f->ml.text[5].img,
	&f->ml.text[5].bits_per_pixel, &f->ml.text[5].size_line,
	&f->ml.text[5].endian);
	texture = "./textures/images/own/suelo_piedra.xpm";
	f->ml.text[6].img = mlx_xpm_file_to_image(f->ml.mlx, texture,
	&f->ml.text[6].width, &f->ml.text[6].height);
	f->ml.text[6].data = (int *)mlx_get_data_addr(f->ml.text[6].img,
	&f->ml.text[6].bits_per_pixel, &f->ml.text[6].size_line,
	&f->ml.text[6].endian);
}

void		ft_init_flooring(t_file *f, int y)
{
	f->fl.raydir0.x = (f->ml.dir.x - f->ml.plane.x) * 1.5;
	f->fl.raydir0.y = (f->ml.dir.y - f->ml.plane.y) * 1.5;
	f->fl.raydir1.x = (f->ml.dir.x + f->ml.plane.x) * 1.5;
	f->fl.raydir1.y = (f->ml.dir.y + f->ml.plane.y) * 1.5;
	f->fl.p = y - f->h / 2;
	f->fl.posz = 0.5 * f->h;
	f->fl.rowdist = f->fl.posz / f->fl.p;
	f->fl.flst.x = f->fl.rowdist * (f->fl.raydir1.x - f->fl.raydir0.x) / f->w;
	f->fl.flst.y = f->fl.rowdist * (f->fl.raydir1.y - f->fl.raydir0.y) / f->w;
	f->fl.floor.x = f->ml.pos.x + f->fl.rowdist * f->fl.raydir0.x;
	f->fl.floor.y = f->ml.pos.y + f->fl.rowdist * f->fl.raydir0.y;
}

void		ft_draw_floor(t_file *f)
{
	int		i[2];
	int		color;
	int		seg;

	i[0] = -1;
	while (++i[0] < f->h)
	{
		ft_init_flooring(f, i[0]);
		i[1] = -1;
		while (++i[1] < f->w)
		{
			f->fl.cellx = (int)f->fl.floor.x;
			f->fl.celly = (int)f->fl.floor.y;
			f->fl.tx = (int)(f->ml.text[6].width * (f->fl.floor.x -
			f->fl.cellx)) & (f->ml.text[6].width - 1);
			f->fl.ty = (int)(f->ml.text[6].height * (f->fl.floor.y -
			f->fl.celly)) & (f->ml.text[6].height - 1);
			f->fl.floor.x += f->fl.flst.x;
			f->fl.floor.y += f->fl.flst.y;
			seg = f->ml.text[6].width * f->fl.ty + f->fl.tx;
			if (seg >= 0)
				color = ft_dark_color(f->fl.rowdist, f->ml.text[6].data[seg]);
			*(f->ml.frame.data + (i[0] * f->w) + i[1]) = color;
		}
	}
}

void		ft_draw_sky(t_file *f)
{
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < f->w)
	{
		y = -1;
		while (++y < f->h / 2)
		{
			color = f->ml.text[5].data[y % 1366 * 1366 + x % 1366];
			f->ml.frame.data[y * f->w + x] = color;
		}
	}
}
