/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 12:43:15 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/09 20:29:11 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

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