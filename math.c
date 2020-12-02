/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 18:37:21 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 17:28:20 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

t_vec		normalize_vector(t_vec vector)
{
	t_vec		result;
    double		scalar;

	scalar = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	return (result);
}

t_vec		get_vector(t_vec loc1, t_vec loc2)
{
	t_vec	result;

	result.x = loc2.x - loc1.x;
	result.y = loc2.y - loc1.y;
	result.z = loc2.z - loc1.z;
	result = normalize_vector(result);
	return (result);
}

t_vec		subs_vec(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec		add_vec(t_vec v1, t_vec v2)
{
	t_vec	result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);

}

t_vec		mult_vec(t_vec v, double scalar)
{
	t_vec	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);

}

double		dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		get_dist_vec(t_vec v)
{
	return (pow(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2), 0.5));
}