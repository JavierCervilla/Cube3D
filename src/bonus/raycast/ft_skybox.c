/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skybox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42madrid.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 04:04:14 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/19 16:48:56 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_init_texture(t_file *f)
{
    int i;
    char *texture;
    texture = "./textures/skybox.xpm";
    f->ml.text[5].img = mlx_xpm_file_to_image(f->ml.mlx, texture,
        &f->ml.text[5].width, &f->ml.text[5].height);
    f->ml.text[5].data = (int*)mlx_get_data_addr(f->ml.text[5].img,
        &f->ml.text[5].bits_per_pixel, &f->ml.text[5].size_line,
        &f->ml.text[5].endian);
    texture = "./textures/metal.xpm";
    f->ml.text[6].img = mlx_xpm_file_to_image(f->ml.mlx, texture,
        &f->ml.text[6].width, &f->ml.text[6].height);
    f->ml.text[6].data = (int*)mlx_get_data_addr(f->ml.text[6].img,
        &f->ml.text[6].bits_per_pixel, &f->ml.text[6].size_line,
        &f->ml.text[6].endian);
}

void    ft_draw_floor(t_file *f)
{
    int p;
    int y;
    int x;
    int color;
    int seg;
    
    y = -1;
    ft_bzero((void*)&f->fl, sizeof(t_floor));
    while (++y < f->h)
    {
        f->fl.raydir0.x = f->ml.dir.x - f->ml.plane.x;
        f->fl.raydir0.y = f->ml.dir.y - f->ml.plane.y;
        f->fl.raydir1.x = f->ml.dir.x + f->ml.plane.x;
        f->fl.raydir1.y = f->ml.dir.y + f->ml.plane.y;
        p = y - f->h / 2;
        f->fl.posz = 0.5 * f->h;
        f->fl.rowdist = f->fl.posz / p;
        f->fl.flst.x = f->fl.rowdist * (f->fl.raydir1.x - f->fl.raydir0.x) / f->w;
        f->fl.flst.y = f->fl.rowdist * (f->fl.raydir1.y - f->fl.raydir0.y) / f->w;
        f->fl.floor.x = f->ml.pos.x + f->fl.rowdist * f->fl.raydir0.x;
        f->fl.floor.y = f->ml.pos.y + f->fl.rowdist * f->fl.raydir0.y;
        x = -1;
        while (++x < f->h)
        {
            f->fl.cellx = (int)f->fl.floor.x;
            f->fl.celly = (int)f->fl.floor.y;
            f->fl.tx = (int)(f->ml.text[6].width * (f->fl.floor.x - f->fl.cellx)) & f->ml.text[6].width - 1;
            f->fl.ty = (int)(f->ml.text[6].height * (f->fl.floor.y - f->fl.celly)) & f->ml.text[6].height - 1;
            f->fl.floor.x += f->fl.flst.x;
            f->fl.floor.y += f->fl.flst.y;
            seg = 256 * f->fl.ty + f->fl.tx;
            if (seg >= 0)
                color = f->ml.text[6].data[seg];
            f->ml.frame.data[y * f->w + x] = color;
            /* seg = f->ml.text[6].width * f->fl.ty + f->fl.tx;
            if (seg >= 0)
                color = f->ml.text[6].data[seg];
            f->ml.frame.data[(f->h - y - 1) * f->w + x] = color; */
        }
        
    }
}

void    ft_draw_sky(t_file *f)
{
    int x;
    int y;
    int color;

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