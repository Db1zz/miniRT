#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "vector.h"

typedef struct t_scene;

typedef	struct s_viewport
{
	double		height;
	double		width;
	t_vector	upper_left;
	t_vector	horizontal_vec;
	t_vector	verical_vec;
}	t_viewport;

t_error	update_viewport(t_camera *cam);

#endif	// VIEWPORT_H