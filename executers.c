#include "miniRT.h"

int colorPlane(ray R, t_Plane pl, double t)
{
	t_vector light_pos = initialize_vector(0,100,-100);
	t_vector light_color = initialize_vector(1.0, 1.0, 1.0);
	t_vector color_plane = multiple((double)1 / 255, pl.color_plane);
	t_vector diffuse = (t_vector){0, 0, 0};
	t_vector ambient = (t_vector){0, 0, 0};;
	t_vector specular = (t_vector){0, 0, 0};
	t_vector color = (t_vector){0.5, 0.5, 0.5};
	if (t > 0.0)
	{
		t_vector newStart = line_point(R, t);
		t_vector L = make_unit_vector(subtract(light_pos, newStart));
		t_vector N = pl.plane_norm;
		t_vector R1 = make_unit_vector(subtract(multiple(2 * scalar(N, L), N), L));
		t_vector V = make_unit_vector(multiple(-1, R.B));
		diffuse = color_diffuse(color_plane, light_color, L, N);
		ambient = multiple(0.4, color_plane);
		specular = color_spec(light_color, R1, V);
		printf("%f %f %f\n", specular.x, specular.y, specular.z);
		color = add(diffuse, add(ambient, specular));
	}
	int rgb = rgb_maker(color_clamping(color));
	return (rgb);
}

/*
		t_vector newStart = line_point(R, t);
		t_vector N = make_unit_vector(subtract(newStart ,sp.sphere_center));
		t_vector L = make_unit_vector(subtract(light_pos, newStart));
		t_vector R1 = (subtract(multiple(2 * scalar(N, L), N), L));
		t_vector V = (multiple(-1, R.B));
		diffuse = color_diffuse(multiple((double)1 / 255, sp.color_sphere), light_color, L, N);
		specular = color_spec(light_color, R1, V);
*/

t_vector light_dif_spec(t_vector newStart, t_vector N, t_vector V, t_objects *lights, t_vector color)
{
	t_vector	specular = (t_vector){0, 0, 0};
	t_vector	diffuse = (t_vector){0, 0, 0};
	t_vector	light_pos;
	t_vector	light_color;
	t_objects	*l;
	t_Light		light;
	l = lights;
	color = multiple((double)1 / 255, color);
	while (l != NULL)
	{
		light = *(t_Light*)l->content;
		light_pos = light.light_pos;
		light_color = light.light_color;
		t_vector L = make_unit_vector(subtract(light_pos, newStart));
		t_vector R1 = (subtract(multiple(2 * scalar(N, L), N), L));
		diffuse = add(diffuse, color_diffuse(multiple((double)1 / 255, color), light_color, L, N));
		specular = add(specular, color_spec(light_color, R1, V));
		l = l->next;
	}
	return (add(specular, diffuse));
}



int colorSphere(ray R, t_Sphere sp, double t, t_objects *lights)
{
	t_vector light_pos = initialize_vector(0,100,-100);
	t_vector light_color = initialize_vector(1.0, 1.0, 1.0);
	t_vector ambient = (t_vector){0, 0, 0};
	t_vector spec_diffuse;
	t_objects *l;
	t_vector specular = (t_vector){0, 0, 0};
	t_vector diffuse = (t_vector){0, 0, 0};
	t_vector color = (t_vector){0, 0, 0};
	l = lights;
	if (t > 0.0)
	{
		//(ray R, t_vector newStart, t_vector N, t_objects *lights, t_vector pointHited, t_vector color)
		ambient = multiple(0.2, multiple((double)1 / 255, sp.color_sphere));
		t_vector newStart = line_point(R, t);
		t_vector N = make_unit_vector(subtract(newStart ,sp.sphere_center));
		t_vector V = (multiple(-1, R.B));
		/*light_pos = (*(t_Light*)l->content).light_pos;
		light_color = (*(t_Light*)l->content).light_color;
		t_vector L = make_unit_vector(subtract(light_pos, newStart));
		t_vector R1 = (subtract(multiple(2 * scalar(N, L), N), L));
		diffuse = color_diffuse(multiple((double)1 / 255, sp.color_sphere), multiple((double)1 / 255, light_color), L, N);
		specular = color_spec(light_color, R1, V);*/
		//(t_vector newStart, t_vector N, t_vector V, t_objects *lights, t_vector color)
		spec_diffuse = light_dif_spec(newStart, N, V, lights, sp.color_sphere);
		color = add(ambient, spec_diffuse);
	}
	int rgb = rgb_maker(color_clamping(color));
	return (rgb);
}