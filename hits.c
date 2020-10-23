#include "miniRT.h"

int sphereHandler(ray r, t_objects *p, double *distance, double *t, t_objects *lights, int color)
{
    *t = equationSphere(r, p, distance);
    if (*t > 0)
		return colorSphere(r, *(t_Sphere*)p->content, *t, lights);
    return (color);
}

int planeHandler(ray r, t_objects *p, double *distance, double *t, t_objects *lights)
{
    t_Plane pl;

    *t = equationPlane(r, p, distance);
	pl = *(t_Plane*)p->content;
    if (scalar(r.B, pl.plane_norm) > 0)
	{
		pl.plane_norm = multiple(-1, pl.plane_norm);	
	}
	return colorPlane(r, pl, *t, lights);
}
