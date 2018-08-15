/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 15:27:20 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/08/06 15:27:21 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** "fdf.h" for t_coord_val type, terminate(), ft_isnumber(), ft_atoi_base(),
**  t_map type and push()
** "libft.h" for size_t type ("libft.h" includes <string.h>), ft_memalloc()
**  ft_strsplit(), ft_atoi(), NULL macros ("libft.h" includes <string.h>)
**  and ft_strdel()
** "get_next_line.h" for get_next_line()
** "error_message.h" for ERR_MAP_READING macros and ERR_MAP macros
** <stdlib.h> for free()
*/

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include "error_message.h"
#include <stdlib.h>

/*
** Free array that was returned by ft_strsplit()
*/

static void			free_strsplit_arr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** Create t_coord_val element with information about z and color value
*/

static t_coord_val	*new_coord(char *s)
{
	t_coord_val	*coord;
	char		**parts;

	if (!(coord = (t_coord_val *)ft_memalloc(sizeof(t_coord_val))))
		terminate(ERR_MAP_READING);
	if (!(parts = ft_strsplit(s, ',')))
		terminate(ERR_MAP_READING);
	if (!ft_isnumber(parts[0], 10))
		terminate(ERR_MAP_READING);
	if (parts[1] && !ft_isnumber(parts[1], 16))
		terminate(ERR_MAP_READING);
	coord->z = ft_atoi(parts[0]);
	coord->color = parts[1] ? ft_atoi_base(parts[1], 16) : -1;
	coord->next = NULL;
	free_strsplit_arr(parts);
	return (coord);
}

/*
** Get coordinate values from line, create t_coord_val elements
** and them add to stack
*/

static void			parse_line(char **coords_line,
							t_coord_val **coords_stack,
							t_map *map)
{
	int	width;

	width = 0;
	while (*coords_line)
	{
		push(coords_stack, new_coord(*(coords_line++)));
		width++;
	}
	if (map->height == 0)
		map->width = width;
	else if (map->width != width)
		terminate(ERR_MAP);
}

/*
** Read map from file line by line
*/

int					read_map(const int fd,
							t_coord_val **coords_stack,
							t_map *map)
{
	char	*line;
	int		result;
	char	**coords_line;

	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (!(coords_line = ft_strsplit(line, ' ')))
			terminate(ERR_MAP_READING);
		parse_line(coords_line, coords_stack, map);
		free_strsplit_arr(coords_line);
		ft_strdel(&line);
		map->height++;
	}
	if (!(*coords_stack))
		terminate(ERR_MAP);
	return (result);
}
