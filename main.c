/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 13:03:56 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 18:31:40 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    t_data  	data;
	t_object	plane;
	t_ray		ray;

	srand((unsigned int)(time(0)));
	plane.v1 = (t_vec){10, -3, -4};
	plane.v2 = (t_vec){0.01, 0.2, 0.64};
	plane.v2 = normalize_vector(plane.v2);
	ray.loc = (t_vec){-10, 0, 0};
	ray.dir = (t_vec){0, -1, -1};
	ray.dir = normalize_vector(ray.dir);
	data = parcer();
	plane = *data.objects;
	while (plane.shape != 1)
		plane = *plane.next;
	display_vec(plane.v2);
	data.fov_y = data.fov_x * ((double)data.y / (double)data.x);
    data.window.mlx = mlx_init();
    data.window.mlx_win = mlx_new_window(data.window.mlx, data.x, data.y, "sukkel");
    data.buf.img = mlx_new_image(data.window.mlx, data.x, data.y);
    data.buf.addr = mlx_get_data_addr(data.buf.img, &data.buf.bits_per_pixel, &data.buf.line_length, &data.buf.endian);
    data.buf = ray_gun(data);
    mlx_put_image_to_window(data.window.mlx, data.window.mlx_win, data.buf.img, 0, 0);
    mlx_key_hook(data.window.mlx_win, ft_exit_esc, &data.window.mlx);
    mlx_loop(data.window.mlx);
    return (0);
}
