/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:32:11 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/21 03:30:45 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_check_config(t_file *f)
{
	int		i;

	i = -1;
	while (i < 8)
		if (f->read[++i] > 1)
			return (-1);
	return (0);
}

int			ft_handle_map_read(t_file *f)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
	{
		if (ft_check_config(f) == -1)
			ft_handle_error("ERROR: DUPLICATE LINE IN CONFIG\n");
		i = ft_strlen(f->line);
		if (f->buff == NULL)
			temp = ft_strdup(f->line);
		else
			temp = ft_strjoin(f->buff, f->line);
		free(f->buff);
		f->buff = temp;
		temp = ft_strjoin(f->buff, "\n");
		free(f->buff);
		f->buff = temp;
		if (f->ncolmax == 0 || f->ncolmax < i)
			f->ncolmax = i;
		f->nfil++;
	}
	return (f->rtn);
}

/*
** static void	ft_filling_matrix(t_file *f, int k, int i, int j)
** input: struct t_file f, int k(buffer), int i(row),
*/

static void	ft_filling_matrix(t_file *f, int k, int i, int j)
{
	if (f->buff[k] == '0' || f->buff[k] == '1' || f->buff[k] == '2')
	{
		f->map[i][j] = (int)f->buff[k] - '0';
		if (f->buff[k] == '2')
			f->sprite_num++;
	}
	else if (f->buff[k] == ' ')
		f->map[i][j] = 4;
	else if ((f->buff[k] == 'N' || f->buff[k] == 'S' || f->buff[k] == 'E'
		|| f->buff[k] == 'W') && f->dir == '\0')
	{
		f->map[i][j] = 0;
		f->dir = f->buff[k];
		f->pos[0] = i;
		f->ml.pos.x = i + 0.5;
		f->pos[1] = j;
		f->ml.pos.y = j + 0.5;
		ft_cast_init_dir(f);
	}
	else
		ft_handle_error_ptr("ERROR IN MAP\n", (void *)f->map);
}

int			alloc_map(t_file *f)
{
	int i[3];

	i[0] = -1;
	i[2] = 0;
	if (!(f->map = ft_calloc(f->nfil, sizeof(int *))))
		return (f->rtn = -1);
	else
	{
		while (++i[0] < f->nfil && f->buff[i[2]])
		{
			if (!(f->map[i[0]] = ft_calloc(f->ncolmax, sizeof(int *))))
				return (f->rtn = -1);
			i[1] = -1;
			while (++i[1] < f->ncolmax && f->buff[i[2]] != '\n')
			{
				ft_filling_matrix(f, i[2], i[0], i[1]);
				i[2]++;
			}
			i[2]++;
		}
		f->mapreaded = 1;
		if (f->dir == '\0')
			ft_handle_error("ERROR: NO DIR\n");
	}
	return (0);
}

int			ft_copy_map(t_file *f)
{
	int i;
	int j;

	i = -1;
	if (!(f->c_map = ft_calloc(f->nfil, sizeof(int *))))
		return (0);
	else
	{
		while (++i < f->nfil)
		{
			if (!(f->c_map[i] = ft_calloc(f->ncolmax, sizeof(int *))))
				return (0);
			j = -1;
			while (++j < f->ncolmax)
			{
				f->c_map[i][j] = f->map[i][j];
			}
		}
	}
	return (0);
}
