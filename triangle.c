/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 15:33:52 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/09 20:04:35 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int			in_between_def(t_vec dir, t_vec v1, t_vec v2, t_vec p)
{
	t_vec	p1;
	t_vec	p2;

	p1 = add_vec(v1, mult_vec(dir, (p.x - v1.x) / dir.x));
	p2 = add_vec(v2, mult_vec(dir, (p.x - v2.x) / dir.x));
	if ((p1.y < p.y && p2.y > p.y) || (p1.y > p.y && p2.y < p.y))
		return (1);
	return (0);
}

t_vec	find_p(t_vec v1, t_vec v2, t_vec v3)
{
	t_vec	v1_2;
	t_vec	v1_3;

	v1_2 = subs_vec(v2, v1);
	v1_3 = subs_vec(v3, v1);
	return (add_vec(v1, mult_vec(v1_2, dot(v1_3, v1_2) / (dot(v1_2, v1_3)))));
}

t_vec       get_normal_triangle(t_object triangle)
{
	t_vec	v1_2;
	t_vec	v1_3;
    t_vec	result;

	v1_2 = subs_vec(triangle.v2, triangle.v1);
	v1_3 = subs_vec(triangle.v3, triangle.v1);
	result.x = (v1_2.y * v1_3.z) - (v1_2.z * v1_3.y);
	result.y = (v1_2.z * v1_3.x) - (v1_2.x * v1_3.z);
	result.z = (v1_2.x * v1_3.y) - (v1_2.y * v1_3.x);
	return (result);
}

double		triangle_dist(t_object triangle, t_ray ray)
{
	float	dist;
	t_vec	loc;
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;

	dist = plane_dist(triangle, ray);
	loc = add_vec(ray.loc, mult_vec(ray.dir, dist));
	v1 = subs_vec(triangle.v2, triangle.v3);
	v2 = subs_vec(triangle.v3, triangle.v1);
	v3 = subs_vec(triangle.v1, triangle.v2);
	if (in_between_def(v1, triangle.v1, triangle.v2, loc) && in_between_def(v2, triangle.v2, triangle.v3, loc) && in_between_def(v3, triangle.v3, triangle.v1, loc))
		return (dist);
	return (0);
}