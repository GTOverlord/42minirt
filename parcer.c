/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 15:47:57 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/09 16:15:42 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "minilibx/mlx.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

int		is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_atoi(char *s, int *i)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (s[0] == '-')
	{
		sign = -1;
		(*i)++;
	}
	while (is_number(s[*i]))
	{
		result = result * 10 + (s[*i] - '0');
		(*i)++;
	}
	result *= sign;
	return (result);
}

float	ft_atod(char *s, int *i)
{
	double	result;
	int		d;
	int		sign;

	result = 0;
	sign = 1;
	if (s[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	while (is_number(s[*i]))
	{
		result = result * 10 + (s[*i] - '0');
		(*i)++;
	}
	if (s[*i] == '.')
	{
		d = 1;
		(*i)++;
		while (is_number(s[*i]))
		{
			d *= 10;
			result += (s[*i] - '0') / (double)d;
			(*i)++;
		}
	}
	result *= sign;
	return (result);
}

t_vec	atov(char *s, int *i)
{
	t_vec	result;

	result.x = ft_atod(s, i);
	while (s[*i] != ',')
		(*i)++;
	(*i)++;
	result.y = ft_atod(s, i);
	while (s[*i] != ',')
		(*i)++;
	(*i)++;
	result.z = ft_atod(s, i);
	return (result);
}

t_col	atoc(char *s, int *i)
{
	t_col	result;
	t_vec	temp;

	temp = atov(s, i);
	result.r = (unsigned int)temp.x;
	result.g = (unsigned int)temp.y;
	result.b = (unsigned int)temp.z;
	return (result);
}

t_data	parce_r(t_data data, char *line)
{
	int	i;

	i = 1;
	while (!is_number(line[i]))
		i++;
	data.x = ft_atoi(line, &i);
	while (is_number(line[i]))
		i++;
	while (!is_number(line[i]))
		i++;
	data.y = ft_atoi(line, &i);
	return (data);
}

t_data	parce_c(t_data data, char *line)
{
	int		i;
	float	fov_degrees;
	float	fov_radials;

	i = 1;
	while (!is_number(line[i]) && line[i] != '-' && line[i] != '.')
		i++;
	data.camera.loc = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-' && line[i] != '.')
		i++;
	data.camera.dir = atov(line, &i);
	data.camera.dir = normalize_vector(data.camera.dir);
	while (!is_number(line[i]) && line[i] != '-' && line[i] != '.')
		i++;
	fov_degrees = ft_atod(line, &i);
	if (fov_degrees > 180 || fov_degrees <= 0)
		return (data);
	fov_radials = fov_degrees / 180 * M_PI;
	data.fov_x = tan(fov_radials / 2);
	return (data);
}

void	parce_sp(t_data data, char *line)
{
	int			i;
	t_object	sphere;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	sphere.v1 = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	sphere.d1 = ft_atod(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	sphere.col = atoc(line, &i);
	sphere.shape = 0;
	add_object(sphere, data.objects);
}

void	parce_pl(t_data data, char *line)
{
	int			i;
	t_object	plane;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	plane.v1 = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	plane.normal = atov(line, &i);
	plane.normal = normalize_vector(plane.normal);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	plane.col = atoc(line, &i);
	plane.shape = 1;
	add_object(plane, data.objects);
}

void	parce_tr(t_data data, char *line)
{
	int			i;
	t_object	triangle;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	triangle.v1 = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	triangle.v2 = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	triangle.v3 = atov(line, &i);
	triangle.normal = get_normal_triangle(triangle);
	triangle.normal = normalize_vector(triangle.normal);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	triangle.col = atoc(line, &i);
	triangle.shape = 2;
	add_object(triangle, data.objects);
}

void	parce_l(t_data data, char *line)
{
	int			i;
	t_light		light;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	light.loc = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	light.bright = ft_atod(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	light.col = atoc(line, &i);
	add_light(light, data.lights);
}

t_data	parce_a(t_data data, char *line)
{
	int		i;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	data.ambient_bright = ft_atod(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	data.ambient_col = atoc(line, &i);
	return (data);
}

t_data	parce_line(t_data data, char *line)
{
	if (line[0] == 'R')
		data = parce_r(data, line);
	if (line[0] == 'c' && line[1] != 'y')
		data = parce_c(data, line);
	if (line[0] == 's' && line[1] == 'p')
		parce_sp(data, line);
	if (line[0] == 'p' && line[1] == 'l')
		parce_pl(data, line);
	if (line[0] == 't' && line[1] == 'r')
		parce_tr(data, line);
	if (line[0] == 'l')
		parce_l(data, line);
	if (line[0] == 'A')
		data = parce_a(data, line);
	return (data);
}

t_data	parcer(void)
{
	t_data	data;
	int		fd;
	char	**line;

	data = (t_data){0};
	data.objects = malloc(sizeof(t_object));
	*(data.objects) = (t_object){0};
	data.lights = malloc(sizeof(t_light));
	*(data.lights) = (t_light){0};
	fd = open("test.rt", O_RDONLY);
	line = malloc(sizeof(char *));
	while (get_next_line(fd, line))
	{
//		printf("line: %s\n", *line);
		data = parce_line(data, *line);
	}
	return (data);
}
