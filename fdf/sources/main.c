/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 19:37:47 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/07/29 19:37:49 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** "fdf.h" for t_map type, t_coord_val type, t_fdf type, terminate(),
**  map_init(), read_map(), fdf_init(), stack_to_arrays(), camera_init(),
**  draw() and setup_controls()
** "mlx.h" for mlx_loop()
** "error_message.h" for ERR_MAP macros, ERR_MAP_READING macros
**  and ERR_USAGE macros
** <errno.h> for errno variable
** <fcntl.h> for open() and O_RDONLY flag
** <stdlib.h> for NULL macros
*/

#include "fdf.h"
#include "mlx.h"
#include "error_message.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int			fd;
	t_map		*map;
	t_coord_val	*coords_stack;
	t_fdf		*fdf;

	errno = 0;
	coords_stack = NULL;
	if (argc == 2)
	{
		if (!((fd = open(argv[1], O_RDONLY)) >= 0))
			terminate(ERR_MAP);
		map = map_init();
		if (read_map(fd, &coords_stack, map) == -1)
			terminate(ERR_MAP_READING);
		fdf = fdf_init(map);
		stack_to_arrays(&coords_stack, map);
		fdf->camera = camera_init(fdf);
		draw(fdf->map, fdf);
		setup_controls(fdf);
		mlx_loop(fdf->mlx);
	}
	terminate(ERR_USAGE);
	return (0);
}
