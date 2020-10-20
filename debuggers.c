#include "miniRT.h"

void vectorPrinter (t_vector V)
{
    printf("x: %f\n", V.x);
    printf("y: %f\n", V.y);
    printf("z: %f\n", V.z);

}

void resolutionPrinter(t_Resolution res)
{
	printf("------------ Resolution --------\n");
    printf("-> x: %d\n", res.x);
	printf("-> y: %d\n", res.y);
	printf("-> done: %d\n", res.done);
}

void ambientPrinter (t_Ambient ab)
{
    printf("------------ Ambient --------\n");
    printf("-> Ambient Color:\n");
    vectorPrinter(ab.t_ambient_color);
    printf("-> perc: %.1f\n", ab.perc);
}

void cameraPrinter (t_Cam_data *cam)
{
    printf("------------ Camera --------\n");
    printf("-> view_point:\n");
    vectorPrinter(cam->view_point);
    printf("-> fov: %.1f\n", cam->fov);
    printf("-> cam_normal:\n");
    vectorPrinter(cam->cam_normal);
}

void lightPrinter (t_Light *light)
{
    printf("------------ Light --------\n");
    printf("-> light_pos:\n");
    vectorPrinter(light->light_pos);
    printf("-> brightness: %.1f\n", light->brightness);
    printf("-> light_color:\n");
    vectorPrinter(light->light_color);
}

void spherePrinter (t_Sphere *S)
{
    printf("------------ Sphere --------\n");
    printf("-> sphere center:\n");
    vectorPrinter(S->sphere_center);
    printf("-> sphere diametre: %.1f\n", S->sphere_diametre);
    printf("-> sphere color:\n");
    vectorPrinter(S->color_sphere);
}

void planePrinter (t_Plane *P)
{
    printf("------------ Plane --------\n");
    printf("-> plane center:\n");
    vectorPrinter(P->plane_center);
    printf("-> plane norm:\n");
    vectorPrinter(P->plane_norm);
    printf("-> plane color:\n");
    vectorPrinter(P->color_plane);    
}

void objectsDebugger(t_data d)
{
    t_objects *p;

    p = d.obj;
	resolutionPrinter(d.R);
	ambientPrinter(d.A);
    while (p != NULL)
    {
		if (p->id == 2)
            cameraPrinter((t_Cam_data*)(p->content));
        else if (p->id == 3)
            lightPrinter((t_Light*)(p->content));
		else if (p->id == 4)
            spherePrinter((t_Sphere*)(p->content));
        else if (p->id == 5)
            planePrinter((t_Plane*)(p->content));
        p = p->next;
    }

}