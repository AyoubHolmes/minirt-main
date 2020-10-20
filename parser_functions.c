#include "miniRT.h"

void R_insertion(t_data *D, char **data)
{
    D->R.x = atoi(data[1]);
    D->R.y = atoi(data[2]);
    D->R.done = 1;
}

void A_insertion(t_data *D, char **data)
{
    char **ambient_color;
    D->A.perc = strtof(data[1], NULL);
    ambient_color = ft_split(data[2], ',');
    D->A.t_ambient_color = (t_vector){ strtof(ambient_color[0], NULL)\
        , strtof(ambient_color[1], NULL), strtof(ambient_color[2], NULL) };
}

void c_insertion(t_data *D, char **data)
{
    char **view_point;
    char **cam_normal;
    t_objects *p;

    view_point = ft_split(data[1], ',');
    cam_normal = ft_split(data[2], ',');
	if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
		D->obj = camInitializer(view_point, cam_normal, data[3]);
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
		p->next = camInitializer(view_point, cam_normal, data[3]);
    }
}


void l_insertion(t_data *D, char **data)
{
    char		**light_pos;
    char		**light_color;
    t_objects	*p;

    light_pos = ft_split(data[1], ',');
    light_color = ft_split(data[3], ',');
    if (!D->obj)
    {
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(D->obj->content = (t_Light*)malloc(sizeof(t_Light))))
            return ;
        D->obj = ligthInitializer(light_pos, light_color, data[2]);
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(p->next->content = (t_Light*)malloc(sizeof(t_Light))))
            return ;
        p->next = ligthInitializer(light_pos, light_color, data[2]);
    }
}

void sp_insertion(t_data *D, char **data)
{
    char		**sphere_center;
    char		**color_sphere;
    t_objects	*p;

    sphere_center = ft_split(data[1], ',');
    color_sphere = ft_split(data[3], ',');
    if (!D->obj)
    {
        
		if (!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(D->obj->content = (t_Sphere*)malloc(sizeof(t_Sphere))))
            return ;
        D->obj= sphereInitialize(sphere_center, color_sphere, data[2]);
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
		if (!(p->next = (t_objects*)malloc(sizeof(t_objects))))
			return ;
        if(!(p->next->content = (t_Sphere*)malloc(sizeof(t_Sphere))))
            return ;
        p->next = sphereInitialize(sphere_center, color_sphere, data[2]);
    }
}

void pl_insertion(t_data *D, char **data)
{
	char **plane_center;
	char **plane_norm;
	char **color_plane;
	t_objects *p;

	plane_center = ft_split(data[1], ',');
	plane_norm = ft_split(data[2], ',');
	color_plane = ft_split(data[3], ',');
    if (!D->obj)
    {
        if(!(D->obj = (t_objects*)malloc(sizeof(t_objects))))
            return ;
		if(!(D->obj->content = (t_Plane*)malloc(sizeof(t_Plane))))
            return ;
        D->obj->content = planeInitialize(plane_center, plane_norm, color_plane);
		D->obj->id = 5;
        D->obj->next = NULL;
    }
    else
    {
        p = D->obj;
        while (p->next != NULL)
            p = p->next;
        if(!(p->next = (t_objects*)malloc(sizeof(t_objects))))
            return ;
		if(!(p->next->content = (t_Plane*)malloc(sizeof(t_Plane))))
            return ;
        p->next->content = planeInitialize(plane_center, plane_norm, color_plane);
		p->next->id = 5;
        p->next->next = NULL;
    }
}
 