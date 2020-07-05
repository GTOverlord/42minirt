/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hsillem <hsillem@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 16:41:35 by hsillem       #+#    #+#                 */
/*   Updated: 2020/07/05 15:21:41 by hsillem       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <stdio.h>


t_sphere	*create_sphere(t_sphere sphere)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	*new = sphere;
	return (new);
}

void		add_sphere(t_sphere sphere, t_sphere *list)
{
	t_sphere	*temp;

	temp = list;
	while (list)
	{
		temp = list;
		list = list->next;
	}
	temp->next = create_sphere(sphere);
	temp->next->next = 0;
	temp->next->id = temp->id + 1;
}

t_sphere	search_list(int	id, t_sphere *list)
{
	while (list)
	{
		if (list->id == id)
			return (*list);
		list = list->next;
	}
	return ((t_sphere){0});
}