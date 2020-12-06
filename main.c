/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/13 13:03:56 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/06 15:10:36 by hsillem       ########   odam.nl         */
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
    float         x[3];
    float         y[3];

    x[0] = 5;
    x[1] = 4;
    x[2] = 2;
    y[0] = 3;
    y[1] = -1;
    y[2] = 9;
    printf("result: %f - correct: %f\n", solve_dist2(x, y), (float)17 / 38);
	srand((unsigned int)(time(0)));
	data = parcer();
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
