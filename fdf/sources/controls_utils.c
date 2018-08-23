/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 16:04:52 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/08/09 16:04:53 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** "fdf.h" for t_fdf type and draw()
** "key_macos.h" for key codes
*/

#include "fdf.h"
#include "key_macos.h"

/*
** Zoom map
*/

void	zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS ||
		key == MAIN_PAD_PLUS ||
		key == MOUSE_SCROLL_UP)
		fdf->camera->zoom++;
	else if (key == NUM_PAD_MINUS ||
		key == MAIN_PAD_MINUS ||
		key == MOUSE_SCROLL_DOWN)
		fdf->camera->zoom--;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	draw(fdf->map, fdf);
}

/*
** Move map
*/

void	move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->camera->x_offset -= 10;
	else if (key == ARROW_RIGHT)
		fdf->camera->x_offset += 10;
	else if (key == ARROW_UP)
		fdf->camera->y_offset -= 10;
	else
		fdf->camera->y_offset += 10;
	draw(fdf->map, fdf);
}

/*
** Rotate map
*/

void	rotate(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_2 || key == MAIN_PAD_2)
		fdf->camera->alpha += 0.05;
	else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
		fdf->camera->alpha -= 0.05;
	else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
		fdf->camera->beta -= 0.05;
	else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
		fdf->camera->beta += 0.05;
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_3 || key == MAIN_PAD_3)
		fdf->camera->gamma += 0.05;
	else if (key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		fdf->camera->gamma -= 0.05;
	draw(fdf->map, fdf);
}

/*
** Change z value. Make map more flatten
*/

void	flatten(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_LESS)
		fdf->camera->z_divisor -= 0.1;
	else if (key == MAIN_PAD_MORE)
		fdf->camera->z_divisor += 0.1;
	if (fdf->camera->z_divisor < 0.1)
		fdf->camera->z_divisor = 0.1;
	else if (fdf->camera->z_divisor > 10)
		fdf->camera->z_divisor = 10;
	draw(fdf->map, fdf);
}

/*
** Change projection type
*/

void	change_projection(int key, t_fdf *fdf)
{
	fdf->camera->alpha = 0;
	fdf->camera->beta = 0;
	fdf->camera->gamma = 0;
	if (key == MAIN_PAD_I)
		fdf->camera->projection = ISO;
	else if (key == MAIN_PAD_P)
		fdf->camera->projection = PARALLEL;
	draw(fdf->map, fdf);
}
