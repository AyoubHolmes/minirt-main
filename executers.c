#include "miniRT.h"

int colorPlane(ray R, t_Plane pl, double t)
{
	printf("test");
	t_vector light_pos = initialize_vector(0,100,-100);
	t_vector light_color = initialize_vector(1.0, 1.0, 1.0);
	t_vector color_plane = multiple((double)1 / 255, pl.color_plane);
	t_vector diffuse = (t_vector){0, 0, 0};
	t_vector ambient = (t_vector){0, 0, 0};;
	t_vector specular = (t_vector){0, 0, 0};
	t_vector color = (t_vector){0, 0, 0};
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

/*t_vector light_def_spec(ray R, t_vector newStart, t_vector norm, t_objects *lights, t_vector point, t_vector color)
{
	t_vector	specular;
	t_vector	diffuse;
	t_objects	*q;
	t_vector	V[3];

	q = lights;
	specular = (t_vector){0, 0, 0};
	diffuse = (t_vector){0, 0, 0};
	while (q != NULL)
	{

	}	
	return (add(specular, diffuse));
}*/


int colorSphere(ray R, t_Sphere sp, double t)
{
	t_vector light_pos = initialize_vector(0,100,-100);
	t_vector light_color = initialize_vector(1.0, 1.0, 1.0);
	t_vector ambient = (t_vector){0, 0, 0};;
	t_vector specular = (t_vector){0, 0, 0};
	t_vector diffuse = (t_vector){0, 0, 0};
	t_vector color = (t_vector){0, 0, 0};
	if (t > 0.0)
	{
		ambient = multiple(0.2, multiple((double)1 / 255, sp.color_sphere));
		t_vector newStart = line_point(R, t);
		t_vector L = make_unit_vector(subtract(light_pos, newStart));
		t_vector N = make_unit_vector(subtract(newStart ,sp.sphere_center));
		t_vector R1 = (subtract(multiple(2 * scalar(N, L), N), L));
		t_vector V = (multiple(-1, R.B));
		diffuse = color_diffuse(multiple((double)1 / 255, sp.color_sphere), light_color, L, N);
		specular = color_spec(light_color, R1, V);
		color = add(ambient, add(diffuse, specular));
	}
	int rgb = rgb_maker(color_clamping(color));
	return (rgb);
}