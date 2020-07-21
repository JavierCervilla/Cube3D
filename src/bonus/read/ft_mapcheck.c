/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:53:17 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/21 03:05:46 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_map_check(int row, int col, t_file *f)
{
	int ok;

	if (row < 0 || col < 0 || row >= f->nfil || col >= f->ncolmax ||
		f->c_map[row][col] == 4)
		return (-1);
	else if (f->c_map[row][col] == 3 || f->c_map[row][col] == 1)
		return (0);
	f->c_map[row][col] = 3;
	ok = ft_map_check(row, col - 1, f);
	ok = ok == 0 ? ft_map_check(row, col + 1, f) : ok;
	ok = ok == 0 ? ft_map_check(row - 1, col, f) : ok;
	ok = ok == 0 ? ft_map_check(row + 1, col, f) : ok;
	return (f->rtn = ok);
}

