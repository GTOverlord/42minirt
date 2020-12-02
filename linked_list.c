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


t_object	*create_object(t_object object)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	*new = object;
	return (new);
}

t_light	*create_light(t_light light)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	*new = light;
	return (new);
}

void		add_object(t_object object, t_object *list)
{
	while (list->next)
		list = list->next;
	list->next = create_object(object);
	list->next->next = 0;
	list->next->id = list->id + 1;
}

void		add_light(t_light light, t_light *list)
{
	t_light	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
	}
	temp->next = create_light(light);
	temp->next->next = 0;
	temp->next->id = temp->id + 1;
}

t_object	search_list(int	id, t_object *list)
{
	while (list)
	{
		if (list->id == id)
			return (*list);
		list = list->next;
	}
	return ((t_object){0});
}