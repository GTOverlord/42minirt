#include "header.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

float		get_dist(t_object object, t_ray ray)
{
	if (object.shape == 0)
		return (sphere_dist(object, ray));
	if (object.shape == 1)
		return (plane_dist(object, ray));
	if (object.shape == 2)
		return (triangle_dist(object, ray));
	if (object.shape == 3)
		return (square_dist(&object, ray));
	return (sphere_dist(object, ray));
}

int			closest_object(t_data data, t_ray ray)
{
	float	temp;
	float	dist;
	int		id;

	temp = 0;
	dist = 0;
	id = 0;
	while (data.objects)
	{
		temp = get_dist(*(data.objects), ray);
		if (temp > 0 && (temp < dist || !dist))
		{
			id = data.objects->id;
			dist = temp;
		}
		data.objects = data.objects->next;
	}
	return (id);
}

float				direct_path(t_data data, t_vec loc1, t_vec light_loc, int id1)
{
	t_ray	ray;
	int		id2;
	float	dist;

	ray.loc = light_loc;
	ray.dir = get_vector(light_loc, loc1);
	data.lights = data.lights->next;
	id2 = closest_object(data, ray);
	dist = get_dist(search_list(id2, data.objects), ray);
	if (id2 == id1)
		return (dist);
	return (0);
}

t_col			add_col(t_col col1, t_col col2)
{
	t_col	result;

	result.r = col1.r + col2.r;
	if (result.r > 255)
		result.r = 255;
	result.g = col1.g + col2.g;
	if (result.g > 255)
		result.g = 255;
	result.b = col1.b + col2.b;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

t_col			mult_col(t_col col1, t_col col2, float factor)
{
	t_col	result;

	result.r = col1.r * col2.r * factor / 0x00000100;
	if (result.r < 0)
		result.r = 0;
	result.g = col1.g * col2.g * factor / 0x00000100;
	if (result.g < 0)
		result.g = 0;
	result.b = col1.b * col2.b * factor / 0x00000100;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

t_col			calculate_light(t_col object_col, t_col col, t_light *light, float dist, float mult)
{
	t_col	add;

	if (mult < 0)
		mult *= -1;
	mult = mult * light->bright / pow(dist, 2);
	add = mult_col(object_col, light->col, mult);
	col = add_col(col, add);
	return (col);
}

t_vec			get_normal(t_object object, t_vec loc)
{
	if (object.shape == 0)
		return (get_normal_sphere(object, loc));
	else
		return (object.normal);
	return ((t_vec){0, 0, 1});
}

float		absolute(float x)
{
	if (x < 0)
		return (-1 * x);
	else
		return (x);
}

int			correct_side(t_object object, t_vec loc, t_light light, t_ray cam_ray)
{
	if (object.shape == 0)
	{
		if (dot(get_vector(loc, object.v1), get_vector(loc, light.loc)) < 0)
			return (1);
		else
			return (0);
	}
	else
	{
		cam_ray.loc = light.loc;
		if (plane_dist(object, cam_ray) > 0)
			return (1);
		else
			return (0);
	}
	return (1);
}

t_col    	get_color(t_data data, t_ray ray)
{
	int				id;
	t_object		object;
	t_vec			loc;
	float			dist;
	t_col			col;

	id = closest_object(data, ray);
	loc = add_vec(data.camera.loc, mult_vec(ray.dir, get_dist(search_list(id, data.objects), ray)));
	object = search_list(id, data.objects);
	col = mult_col(object.col, data.ambient_col, data.ambient_bright);
	if (id)
	{
		while (data.lights->next)
		{
			data.lights = data.lights->next;
			if (correct_side(object, loc, *data.lights, ray))
			{
				dist = direct_path(data, loc, data.lights->loc, id);
				if (dist)
					col = calculate_light(object.col, col, data.lights, dist, absolute(dot(get_normal(object, loc), get_vector(data.lights->loc, loc))));
			}
		}
	}
	return (col);
}