#include "ray.h"

t_ray	create_ray(t_vector origin, t_vector direction)
{
	return ((t_ray){origin, direction, (t_color){0, 0, 0}});
}

bool	ray_hit(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	bool			found;

	found = false;
	while (objects)
	{
		if (ray_hit_sphere(objects, ray, &prop->ray_interval, &temp_rec)
				&& temp_rec.t < rec->t)
		{
			rec->t = temp_rec.t;
			rec->normal = temp_rec.normal;
			rec->front_face = temp_rec.front_face;
			rec->obj_type = temp_rec.obj_type;
			rec->p = temp_rec.p;
			rec->color = temp_rec.color;
			found = true;
		}
		objects = objects->next;
	}
	return (found);
}

/*
	TODO: add a bright spot from a light object to the surface of an object
*/
// TODO: delete this
#include "minirt_math.h"
t_color	process_ray_hit(const t_object_list *objects,
			const t_ray_properties *prop, const t_hit_record *rec)
{
	const double	ambient_light_intensity = 0;
	t_color			ambient_light;
	t_color			ray_color;
	t_ray			shadow_ray;
	t_vector		ray_direction;

	set_color(&ambient_light, 195, 52, 235);
	ambient_light = clr_mult(ambient_light, ambient_light_intensity);
	ray_color = normalize_color(clr_add_clr(rec->color, ambient_light));

	if (prop->light && prop->light->data)
	{
		t_light			*light = prop->light->data;
		t_vector		ray_intersection;
		const double	epsilon = 1e-3;

		ray_intersection = vec3_add_vec3(rec->p, vec3_mult(rec->normal, epsilon));
		ray_direction = vec3_normalize(vec3_sub_vec3(light->vector, ray_intersection));
		shadow_ray = create_ray(ray_intersection, ray_direction);
		t_hit_record	shadow_rec;
		shadow_rec.t = FT_INFINITY;

		bool obj_intersected = ray_hit_light(objects, &shadow_ray,
					prop, &shadow_rec);
		if (obj_intersected)
			return (clr_mult(ray_color, 1.3));
		else
			return (clr_mult(ray_color, 0.3));
	}
	return (ray_color);
}

t_color	ray_send(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop, t_hit_record *rec)
{
	if (prop->max_diffusion_depth > 0 && ray_hit(objects, ray, prop, rec))
		return (process_ray_hit(objects, prop, rec));
	return (ray_get_background_color(ray));
}

t_color	ray_color(const t_object_list *objects, const t_ray *ray,
			const t_ray_properties *prop)
{
	t_hit_record		rec;
	t_ray_properties	prop_copy;

	prop_copy = *prop;
	rec.t = FT_INFINITY;
	return (ray_send(objects, ray, &prop_copy, &rec));
}
