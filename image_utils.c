/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 20:26:50 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 15:21:23 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include "minilibx/mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>

void	ft_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int*)(img->addr + x * (img->bits_per_pixel / 8) 
	+ y * img->line_length) = color;
}

void	print_loc(t_vec loc)
{
	printf("location:  		x: %14f, 			y: %14f, 			z: %14f\n", loc.x, loc.y, loc.z);
}

void	print_dir(t_vec dir)
{
	printf("direction: 		x: %14f, 			y: %14f, 			z: %14f\n", dir.x, dir.y, dir.z);
}

void	print_data(t_data data)
{
	printf("data.x: %i	data.y: %i\nfovx: %f	fovy: %f\n\ncamera:\n", data.x, data.y, data.fov_x, data.fov_y);
	print_loc(data.camera.loc);
	print_dir(data.camera.dir);
}

//unsigned int	ft_jump_col(t_object object, t_ray ray)
//{
//	unsigned int	(*functions[5])(t_object, t_ray);

//	functions[0] = ft_plane_col;
//	functions[1] = ft_sphere_col;
//	functions[2] = ft_cylinder_col;
//	functions[3] = ft_square_col;
//	functions[4] = ft_triangle_col;
//	return (functions[object.shape])(object, ray);
//}

int		ft_exit_esc(int key, t_window *win)
{
	if (key == 53)
	{
		mlx_destroy_window(win->mlx, win->mlx_win);
		exit(0);
	}
	return (0);
}