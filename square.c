/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 12:43:15 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/12 11:56:25 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>
#include <stdio.h>

t_vec		get_corner_1(t_object *square)		//upper left
{
	float	horizontal;
	t_vec 	result;

	horizontal = pow(pow(square->normal.x, 2) + pow(square->normal.z, 2), 0.5);
	result.x = -1 * square->d1 * square->normal.z / horizontal - -1 * square->d1 * square->normal.y * square->normal.x / horizontal;
	result.y = -1 * square->d1 * horizontal;
	result.z = square->d1 * square->normal.x / horizontal - -1 * square->d1 * square->normal.y * square->normal.z / horizontal;
	return (result);
}

t_vec		get_corner_2(t_object *square)		//upper right
{
	float	horizontal;
	t_vec 	result;

	horizontal = pow(pow(square->normal.x, 2) + pow(square->normal.z, 2), 0.5);
	result.x = square->d1 * square->normal.z / horizontal - square->d1 * square->normal.y * square->normal.x / horizontal;
	result.y = -1 * square->d1 * horizontal;
	result.z = -1 * square->d1 * square->normal.x / horizontal - square->d1 * square->normal.y * square->normal.z / horizontal;
	return (result);
}

t_vec		get_corner_3(t_object *square)		//lower right
{
	float	horizontal;
	t_vec 	result;

	horizontal = pow(pow(square->normal.x, 2) + pow(square->normal.z, 2), 0.5);
	result.x = -1 * square->d1 * square->normal.z / horizontal - -1 * square->d1 * square->normal.y * square->normal.x / horizontal;
	result.y = square->d1 * horizontal;
	result.z = square->d1 * square->normal.x / horizontal - -1 * square->d1 * square->normal.y * square->normal.z / horizontal;
	return (result);
}

t_vec		get_corner_4(t_object *square)		//lower left
{
	float	horizontal;
	t_vec 	result;

	horizontal = pow(pow(square->normal.x, 2) + pow(square->normal.z, 2), 0.5);
	result.x = square->d1 * square->normal.z / horizontal - square->d1 * square->normal.y * square->normal.x / horizontal;
	result.y = square->d1 * horizontal;
	result.z = -1 * square->d1 * square->normal.x / horizontal - square->d1 * square->normal.y * square->normal.z / horizontal;
	return (result);
}

void		get_corners(t_object *square, t_vec centre)
{
	square->v1 = add_vec(centre, get_corner_1(square));
	square->v2 = add_vec(centre, get_corner_2(square));
	square->v3 = add_vec(centre, get_corner_3(square));
	square->v4 = add_vec(centre, get_corner_4(square));
}

double		square_dist(t_object *square, t_ray ray)
{
	float	dist;
	t_vec	loc;

	dist = plane_dist(*square, ray);
	loc = add_vec(ray.loc, mult_vec(ray.dir, dist));
	if (in_between_def(square->v2, square->v1, square->v4, loc) || in_between_def(square->v3, square->v1, square->v4, loc))
		return (dist);
	return (0);
}