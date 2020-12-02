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

unsigned int	get_color_uns_int(t_col color)
{
	unsigned int	result;

	result = 0;
	result += color.r * 0x00010000;
	result += color.g * 0x00000100;
	result += color.b * 0x00000001;
	return (result);
}

t_col			get_color_tcol(unsigned int color)
{
	t_col			result;

	result = (t_col){0};
	result.r = (color % 0x01000000) / 0x00010000;
	result.g = (color % 0x00010000) / 0x00000100;
	result.b = (color % 0x00000100) / 0x00000001;
	return (result);
}