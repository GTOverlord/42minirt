/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parcer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/24 15:47:57 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 17:20:42 by hsillem       ########   odam.nl         */
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

unsigned int	atoc(char *s, int *i)
{
	int red;
	int green;
	int blue;
	t_vec temp;

	temp = atov(s, i);
	red = (unsigned int)temp.x;
	green = (unsigned int)temp.y;
	blue = (unsigned int)temp.z;
	return (red * 256 * 256 + green * 256 + blue);
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
	t_sphere	sphere;

	i = 0;
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	sphere.loc = atov(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
		i++;
	sphere.radius = ft_atod(line, &i);
	while (!is_number(line[i]) && line[i] != '-'&& line[i] != '.')
	{
//		printf("dafuq? %s\n", line);
		i++;
	}
	sphere.col = atoc(line, &i);
	add_sphere(sphere, data.spheres);
}

t_data	parce_line(t_data data, char *line)
{
	if (line[0] == 'R')
		data = parce_r(data, line);
	if (line[0] == 'c' && line[1] != 'y')
		data = parce_c(data, line);
	if (line[0] == 's' && line[1] == 'p')
		parce_sp(data, line);
	return (data);
}

t_data	parcer(void)
{
	t_data	data;
	int		fd;
	char	**line;

	data = (t_data){0};
	data.spheres = malloc(sizeof(t_sphere));
	*(data.spheres) = (t_sphere){0};
	fd = open("test.rt", O_RDONLY);
	line = malloc(sizeof(char *));
	while (get_next_line(fd, line))
	{
//		printf("line: %s\n", *line);
		data = parce_line(data, *line);
	}
	return (data);
}
