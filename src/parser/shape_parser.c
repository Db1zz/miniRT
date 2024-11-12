#include "parser.h"
#include "minirt.h"

t_error	parse_sphere(t_scene *scene, const char **line_data)
{
	t_error		errorn;
	t_sphere	*sphere;

	errorn = ERR_NO_ERROR;
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&sphere->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR && is_string_number(line_data[2]))
		sphere->diameter = ft_atof(line_data[2]);
	else
		errorn = ERR_ATOI_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color(&sphere->color, line_data[3]);
	if (errorn)
		free(sphere);
	else
		// TODO: add sphere to the list in scene->sphere
	return (errorn);
}

t_error	parse_cylinder(t_scene *scene, const char **line_data)
{
	t_error		errorn;
	t_cylinder	*cylinder;

	errorn = ERR_NO_ERROR;
	cylinder = malloc(sizeof(cylinder));
	if (!cylinder)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&cylinder->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_vector(&cylinder->axis, line_data[2]);
	if (errorn == ERR_NO_ERROR)
		errorn = normalize_vector(&cylinder->axis);
	if (is_string_number(line_data[3]) && is_string_number(line_data[4]))
	{
		cylinder->diameter = ft_atof(line_data[3]);
		cylinder->height = ft_atof(line_data[4]);
	}
	else
		errorn = ERR_ATOI_FAILED;
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color(&cylinder->color, line_data[5]);
	if (errorn)
		free(cylinder);
	else
		// TODO: add cylinder to the list in scene->cylinders
	return (errorn);
}

t_error	parse_plane(t_scene *scene, char **line_data)
{
	t_error	errorn;
	t_plane	*plane;

	errorn = ERR_NO_ERROR;
	plane = malloc(sizeof(plane));
	if (!plane)
		return (ERR_MALLOC_FAILED);
	errorn = str_to_vector(&plane->vector, line_data[1]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_vector((&plane->axis), line_data[2]);
	if (errorn == ERR_NO_ERROR)
		errorn = str_to_color((&plane->color), line_data[3]);
	if (!normalize_vector(&plane->axis)
			|| !normalize_vector(&plane->vector))
		errorn = ERR_FAILED_TO_NORM_VECTOR;
	if (errorn)
		free(plane);
	else
		// TODO: add plane to the list in scene->plane
	return (errorn);	
}
