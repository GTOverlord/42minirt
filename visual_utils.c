#include "header.h"
#include "minilibx/mlx.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

void	display_vec(t_vec v)
{
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

void	display_ray(t_ray ray)
{
	printf("loc: \n");
	display_vec(ray.dir);
	printf("loc: \n");
	display_vec(ray.dir);
}

void	display_col(t_col col)
{
	printf("g: %i, r: %i, b: %i\n", col.g, col.r, col.b);
}

void	display_object(t_object object)
{
	printf("\nid: %i	shape: %i\n", object.id, object.shape);
	printf("normal:");
	display_vec(object.normal);
}