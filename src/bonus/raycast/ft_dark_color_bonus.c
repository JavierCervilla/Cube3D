/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dark_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:05:30 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/22 03:59:54 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_dark_color(double distance, int color)
{
	double	dark;
	int		c[3];
	int		dc[3];
	int		rtn;

	dark = (D_COLOR / distance);
	c[0] = (color >> 16) & 255;
	c[1] = (color >> 8) & 255;
	c[2] = color & 255;
	dc[0] = (int)(c[0] * dark);
	dc[1] = (int)(c[1] * dark);
	dc[2] = (int)(c[2] * dark);
	if (dc[0] > c[0])
		dc[0] = c[0];
	if (dc[1] > c[1])
		dc[1] = c[1];
	if (dc[2] > c[2])
		dc[2] = c[2];
	rtn = (dc[0] * 256 * 256) + (dc[1] * 256) + dc[2];
	return (rtn);
}
