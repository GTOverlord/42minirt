#include "header.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double		solve_dist(float *x, float *y, float *z)
{
	double	P;
	double	Q;
	double	R;

	P = y[1] / x[1];
	Q = z[1] / x[1];
	R = (z[2] - Q * x[2]) / (y[2] - P * x[2]);
	return ( - 1 * (x[0] * Q - z[0] + R * y[0] - P * R * x[0]) / (z[3] - Q * x[3] - R * (y[3] - P * x[3])));
}

t_vec		get_v1(t_vec normal)
{
	t_vec	result;

	result.x = normal.x + 1;
	result.y = normal.y;
	result.z = (result.x * normal.x + result.y * normal.y) / normal.z;
	result = normalize_vector(result);
	return (result);
}

t_vec		get_v2(t_vec normal)
{
	t_vec	result;

	result.x = normal.x;
	result.y = normal.y + 1;
	result.z = (result.x * normal.x + result.y * normal.y) / normal.z;
	result = normalize_vector(result);
	return (result);
}

double		plane_dist_def(t_object plane, t_ray ray)
{
	t_vec	v1;
	t_vec	v2;
	float		x[4];
	float		y[4];
	float		z[4];

	v1 = get_v1(plane.v2);
	v2 = get_v2(plane.v2);

	x[0] = plane.v1.x - ray.loc.x;
	x[1] = v1.x;
	x[2] = v2.x;
	x[3] = ray.dir.x;
	y[0] = plane.v1.y - ray.loc.y;
	y[1] = v1.y;
	y[2] = v2.y;
	y[3] = ray.dir.y;
	z[0] = plane.v1.z - ray.loc.z;
	z[1] = v1.z;
	z[2] = v2.z;
	z[3] = ray.dir.z;
	return (solve_dist(x, y, z));
}

double		plane_dist(t_object plane, t_ray ray)
{
//	t_vec	v1;
//	t_vec	v2;
//	int		x[3];
//	int		y[3];
//	int		z[3];

	if (plane.v2.x == 1)
		return ((plane.v1.x - ray.loc.x) / ray.dir.x);
	if (plane.v2.y == 1)
		return ((plane.v1.y - ray.loc.y) / ray.dir.y);
	if (plane.v2.z == 1)
		return ((plane.v1.z - ray.loc.z) / ray.dir.z);
	return (plane_dist_def(plane, ray));
}