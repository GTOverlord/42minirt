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
}				t_ray;

typedef struct	s_col
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}				t_col;

typedef struct	s_light
{
	struct s_light			*next;
	t_vec					loc;
	t_col					col;
	float					bright;
	int						id;
}				t_light;

typedef struct	s_object
{
	struct s_object		*next;
	int					id;
	int					shape;
	t_col				col;
	t_vec				v1;
	t_vec				v2;
	t_vec				v3;
	t_vec				v4;
	t_vec				normal;
	double				d1;
	double				d2;
}				t_object;

typedef struct	s_data
{
	t_sphere	*spheres;
	t_object	*objects;
	t_col		ambient_col;
	float		ambient_bright;
	t_light		*lights;
	t_ray		camera;
	t_window	window;
	t_img		buf;
	int			x;
	int			y;
	double		fov_x;
	double		fov_y;
}				t_data;


void			ft_put_pixel(t_img *img, int x, int y, unsigned int color);
int				ft_exit_esc(int key, t_window *win);
t_img   		ray_gun(t_data data);
void			print_loc(t_vec loc);
void			print_dir(t_vec dir);
t_vec			get_vector(t_vec loc1, t_vec loc2);
t_vec			subs_vec(t_vec v1, t_vec v2);
t_vec			add_vec(t_vec v1, t_vec v2);
double			dot(t_vec v1, t_vec v2);
double			sphere_dist(t_object sphere, t_ray ray);
t_data			parcer(void);
void			print_data(t_data data);
void			add_object(t_object object, t_object *list);
t_object		search_list(int	id, t_object *list);
t_vec			normalize_vector(t_vec vector);
t_vec			mult_vec(t_vec v, double scalar);
t_col			get_color_tcol(unsigned int color);
unsigned int	get_color_uns_int(t_col color);
void			add_light(t_light light, t_light *list);
double			get_dist_vec(t_vec v);
void			display_vec(t_vec v);
void			display_ray(t_ray ray);
void			display_col(t_col col);
t_col 		   	get_color(t_data data, t_ray ray);
double			plane_dist(t_object plane, t_ray ray);
t_vec			get_normal_sphere(t_object sphere, t_vec loc);
double			solve_dist2(float *x, float *y);
t_vec			get_v1(t_vec normal);
t_vec			get_v2(t_vec normal);
t_vec   	    get_normal_triangle(t_object triangle);
double			triangle_dist(t_object triangle, t_ray ray);
void			display_object(t_object object);
void			get_corners(t_object *square, t_vec centre);
double			square_dist(t_object *square, t_ray ray);
int				in_between_def(t_vec dir, t_vec v1, t_vec v2, t_vec p);

#endif