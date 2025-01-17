#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "parser.h"
# include "object.h"
# include "dependencies.h"
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# ifdef __APPLE__
	#  include "key_macos.h"
# elif __linux__
	#  include "key_linux.h"
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720
# define ANTIALIASING_SAMPLES 6

/* Rendering functions */
void	draw_pixel(t_scene *scene, int x, int y, t_color color);
void	render(t_scene *scene);

/* Utility functions */
void	free_2dmatrix(char **matrix);
bool	is_string_number(char *line);
bool	check_str_numbers(char **numbers, int expected_size);
size_t	get_2dmatrix_size(char **matrix);
double	div_c(double v1, double v2);

#endif //	MINIRT_H
