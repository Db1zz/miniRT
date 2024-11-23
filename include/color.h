#ifndef COLOR_H
# define COLOR_H

# define COLOR_MIN 0
# define COLOR_MAX 255
# define COLOR_MAX_SIZE 3

# include "ft_error.h"
# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_error	set_color(t_color *color, int r, int g, int b);
bool	check_color(int c);
bool	validate_colors(int r, int g, int b);
t_error	str_to_color(t_color *color, const char *str);
void	print_color(t_color *c);

#endif // COLOR_H