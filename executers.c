#include "miniRT.h"


t_vector light_dif_spec(t_vector newStart, t_vector N, t_vector V, t_objects *lights, t_vector color)
{
	t_vector	somme;
	t_vector	L;
	t_vector	R;
	t_objects	*l;
	t_Light		light;

	somme = (t_vector){0, 0, 0};
	l = lights;
	color = multiple((double)1 / 255, color);
	while (l != NULL)
	{
		light = *(t_Light*)l->content;
		light.light_color = multiple((double)1 / 255, light.light_color);
		L = make_unit_vector(subtract(light.light_pos, newStart));
		R = make_unit_vector(subtract(multiple(2 * scalar(N, L), N), L));
		somme = add(somme, color_diffuse(color, light.light_color, L, N, light.brightness));
		somme = add(somme, color_spec(light.light_color, R, V, light.brightness));
		l = l->next;
	}
	return (somme);
}


int colorSphere(ray R, t_Sphere sp, double t, t_objects *lights)
{
	t_vector ambient_dif_spec[2];
	t_vector Vecs[3];
	t_objects *l;
	t_vector color;

	ambient_dif_spec[0] = (t_vector){0, 0, 0};
	sp.color_sphere = multiple((double)1 / 255, sp.color_sphere);
	color = (t_vector){0, 0, 0};
	l = lights;
	ambient_dif_spec[0] = multiple(0.3, sp.color_sphere);
	Vecs[0] = line_point(R, t);
	Vecs[1] = make_unit_vector(subtract(Vecs[0] ,sp.sphere_center));
	Vecs[2] = make_unit_vector(multiple(-1, R.B));
	ambient_dif_spec[1] = light_dif_spec(Vecs[0], Vecs[1], Vecs[2], lights, sp.color_sphere);
	color = add(ambient_dif_spec[0], ambient_dif_spec[1]);
	return (rgb_maker(color_clamping(color)));
}


int colorPlane(ray R, t_Plane pl, double t, t_objects *lights)
{
	t_vector ambient_dif_spec[2];
	t_vector Vecs[3];
	t_objects *l;
	t_vector color;

	ambient_dif_spec[0] = (t_vector){0, 0, 0};
	color = (t_vector){0, 0, 0};
	l = lights;
	ambient_dif_spec[0] = multiple(0.3, multiple((double)1 / 255, pl.color_plane));
	Vecs[0] = line_point(R, t);
	Vecs[1] = pl.plane_norm;
	Vecs[2] = (multiple(-1, R.B));
	ambient_dif_spec[1] = light_dif_spec(Vecs[0], Vecs[1], Vecs[2], lights, pl.color_plane);
	color = add(ambient_dif_spec[0], ambient_dif_spec[1]);
	return (rgb_maker(color_clamping(color)));
}
