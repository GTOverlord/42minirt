#ifndef HEADER_H
# define HEADER_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
#  endif


typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_window
{
	void	*mlx;
	void	*mlx_win;
}				t_window;

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct	s_sphere
{
	struct s_sphere		*next;
	t_vec				loc;
	double				radius;
	unsigned int		col;
	int					id;
}				t_sphere;

typedef struct	s_ray
{
	t_vec			loc;
	t_vec			dir;
	double			tork;
}				t_ray;

typedef struct	s_light
{
	t_vec			loc;
	unsigned int	col;
}				t_light;

typedef struct	s_data
{
	t_sphere	*spheres;
	t_light		*lights;
	t_ray		camera;
	t_window	window;
	t_img		buf;
	int			x;
	int			y;
	double		fov_x;
	double		fov_y;
}				t_data;


void			ft_get_img(t_ray camera, t_sphere *objects, t_img *img);
void			ft_put_pixel(t_img *img, int x, int y, unsigned int color);
int				ft_exit_esc(int key, t_window *win);
t_img   		ray_gun(t_data data);
void			print_loc(t_vec loc);
void			print_dir(t_vec dir);
t_vec			get_vector(t_vec loc1, t_vec loc2);
t_vec			subs_vec(t_vec v1, t_vec v2);
t_vec			add_vec(t_vec v1, t_vec v2);
double			dot(t_vec v1, t_vec v2);
double			sphere_dist(t_sphere sphere, t_ray ray);
t_data			parcer(void);
void			print_data(t_data data);
void			add_sphere(t_sphere sphere, t_sphere *list);
t_sphere		search_list(int	id, t_sphere *list);
t_vec			normalize_vector(t_vec vector);

#endif