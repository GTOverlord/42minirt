/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/06 15:33:52 by hsillem       #+#    #+#                 */
/*   Updated: 2020/12/06 18:19:17 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
t_vec		find_p(t_vec v1, t_vec v2, t_vec v3)
{
	t_vec	p;
	t_vec	v1_2;

	v1_2 = subs_vec(v2, v1);
	
}

t_vec       get_normal_triangle(t_object triangle)
{
	t_vec	temp;
    t_vec	plane1_v1;
    t_vec	plane1_v2;
    t_vec	plane2_v1;
    t_vec	plane2_v2;
    t_vec	result;


}

double		triangle_dist(t_object triangle, t_ray ray)
{
    t_vec   normal;

    normal = get_normal_triangle(triangle);
}