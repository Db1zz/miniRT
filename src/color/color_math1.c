#include "color.h"
#include "minirt.h"

t_color	clr_div_clr(t_color c1, t_color c2)
{
	return (create_color(div_c(c1.r, c2.r), div_c(c1.g, c2.g), div_c(c1.b, c2.b)));
}

t_color	clr_mult_clr(t_color c1, t_color c2)
{
	return (create_color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}

t_color	clr_sub_clr(t_color c1, t_color c2)
{
	return (create_color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b));
}

t_color	clr_add_clr(t_color c1, t_color c2)
{
	return (create_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}
