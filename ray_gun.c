/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_gun.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 17:30:43 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 18:31:30 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

t_ray           get_ray(t_ray camera, t_data data, int x, int y)
{
    t_ray   result;
	t_vec	grid;
	double	horizontal;
	double	grid_offset_x;
	double	grid_offset_y;

    result.loc = camera.loc;
	grid = camera.loc;
	horizontal = pow(pow(camera.dir.x, 2) + pow(camera.dir.z, 2), 0.5);
	grid_offset_x = (double)x / data.x * data.fov_x * 2;
	grid_offset_y = (double)y / data.y * data.fov_y * 2;
	grid.x += camera.dir.x + grid_offset_x * camera.dir.z / horizontal - grid_offset_y * camera.dir.y * camera.dir.x / horizontal;
	grid.y += camera.dir.y + grid_offset_y * horizontal;
	grid.z += camera.dir.z + grid_offset_x * camera.dir.x * -1 / horizontal - grid_offset_y * camera.dir.y * camera.dir.z / horizontal;
	result.dir = get_vector(result.loc, grid);
	return (result);
}

t_img   ray_gun(t_data data)
{
    int x;
    int y;

    y = -1 * data.y / 2;
    while (y < data.y / 2)
    {
        x = -1 * data.x / 2;
        while (x < data.x / 2)
        {
            ft_put_pixel(&data.buf, x + data.x / 2, y + data.y / 2, get_color_uns_int(get_color(data, get_ray(data.camera, data, x, y))));
            x++;
        }
        y++;
    }
    return (data.buf);
}