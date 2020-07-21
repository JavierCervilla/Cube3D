/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 00:27:15 by jcervill          #+#    #+#             */
/*   Updated: 2020/07/21 02:57:43 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	ft_read_src_file:
**	devuelve 0 por default y -1 en error.
*/

int			ft_isspace(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\f' || s[i] == '\r' ||
			s[i] == '\t' || s[i] == '\v')
			i++;
		break ;
	}
	return (i);
}

int			ft_read_src_file(t_file *f)
{
	if (f->line[0] == 'R' && f->line[1] == ' ')
		f->rtn = ft_handle_resolution(f);
	else if ((f->line[0] == 'N' && f->line[1] == 'O') || (f->line[0] == 'S' &&
		f->line[1] == 'O') || (f->line[0] == 'W' && f->line[1] == 'E') ||
		(f->line[0] == 'E' && f->line[1] == 'A'))
		f->rtn = ft_handle_textures(f);
	else if (f->line[0] == 'S' && f->line[1] == ' ')
		f->rtn = ft_handle_spritex(f);
	else if (f->line[0] == 'F' && f->line[1] == ' ')
		f->rtn = ft_handle_cfloor(f);
	else if (f->line[0] == 'C' && f->line[1] == ' ')
		f->rtn = ft_handle_croof(f);
	else if (ft_isdigit(f->line[0]) || f->line[0] == ' ')
		f->rtn = ft_handle_map_read(f);
	else if (ft_isspace(f->line) == ft_strlen_int(f->line))
		f->rtn = 1;
	else
		ft_handle_error("ERROR: CONFIG LINE FORBIDEN\n");
	return (f->rtn);
}

int			ft_read(t_file *f)
{
	int		br;
	char	*line;

	ft_init_file_struct(f);
	while ((br = get_next_line(f->fd, &line)) >= 0)
	{
		f->line = line;
		if (ft_read_src_file(f) == -1)
			ft_handle_error("ERROR: AN ERROR READING CONFIG\n");
		if (br == 0)
			break ;
		free(line);
	}
	free(line);
	ft_handle_rgb(f);
	ft_init_mlx_struct(f);
	if (alloc_map(f) != -1)
	{
		ft_copy_map(f);
		if (ft_map_check(f->pos[0], f->pos[1], f) == -1)
			ft_handle_error("MAP ERROR.Error al checkear el mapa\n");
	}
	close(f->fd);
	return (f->rtn);
}
