/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 16:48:58 by hsillem       #+#    #+#                 */
/*   Updated: 2020/06/22 19:05:17 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>


double		sphere_dist(t_object sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	double	result1;
	double	result2;

	a = dot(ray.dir, ray.dir);
	b = 2 * dot(ray.dir, subs_vec(ray.loc, sphere.v1));
	c = dot(subs_vec(ray.loc, sphere.v1), subs_vec(ray.loc, sphere.v1)) - pow(sphere.d1, 2);
	dis = pow(b, 2) - 4 * a * c;
	if (dis < 0)
		return (0);
	result1 = (-b - sqrt(dis)) / (2 * a);
	result2 = (-b + sqrt(dis)) / (2 * a);
	if (result1 > 0 && result1 < result2)
		return (result1);
	else if (result2 > 0)
		return (result2);
	return (0);
}

t_vec	get_normal_sphere(t_object sphere, t_vec loc)
{
	return (get_vector(sphere.v1, loc));
}