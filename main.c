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

int main(void)
{
    t_data  	data;

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
