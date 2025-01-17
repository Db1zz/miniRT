#include "ray.h"

t_vector	get_ray_direction(t_vector origin, t_vector endpoint)
{
	t_vector	direction;

	direction = vec3_normalize(vec3_sub_vec3(origin, endpoint));
	return (direction);
}

t_color	ray_get_background_color(const t_ray *ray)
{
	double		a;
	t_vector	color_vec;

	a = 0.5 * (ray->direction.y + 1.0);
	color_vec = vec3_mult(vec3_add_vec3(
					vec3_mult(create_vector(1.0, 1.0, 1.0), 1.0 - a),
					vec3_mult(create_vector(0.5, 0.7, 1), a)), 255);
	return (create_color(color_vec.x, color_vec.y, color_vec.z));
}

void	ray_hit_record_set_face_normal(
	const t_ray		*ray,
	const t_vector	*outward_normal,
	t_hit_record	*rec)
{
	rec->front_face = vec3_dot(ray->direction, *outward_normal) < 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = vec3_mult(*outward_normal, -1);
	rec->normal = vec3_normalize(rec->normal);
}

t_color	diffuse_material(
	const t_object_list	*objects,
	t_ray_properties	*prop,
	t_hit_record		*rec)
{
	t_ray		ray;
	t_vector	ray_direction;
	t_color		final_ray_color;
	t_color		ambient_light;
	double		ambient_light_intensity;

	ambient_light_intensity = 0.4;
	ray_direction = vec3_random_on_hemisphere(&rec->normal);
	ray = create_ray(rec->intersection_p, ray_direction, create_color(0,0,0));
	prop->max_diffusion_depth--;
	final_ray_color = ray_send(objects, &ray, prop, rec);
	final_ray_color = clr_mult(final_ray_color, 0.01);
	set_color(&ambient_light, 195, 52, 235);
	ambient_light = clr_mult(ambient_light, ambient_light_intensity);
	final_ray_color = clr_add_clr(final_ray_color, rec->color);
	final_ray_color = clr_add_clr(final_ray_color, ambient_light);
	final_ray_color = normalize_color(final_ray_color);
	return (final_ray_color);
}
