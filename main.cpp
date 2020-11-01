#include <fstream>
#include <iostream>
#include <vector>

#include "light.h"
#include "sphere.h"

#define RED     Vector3f { 255, 0, 0 }
#define GREEN   Vector3f { 0, 255, 0 }
#define BLUE    Vector3f { 0, 0, 255 }

void render(std::vector<Sphere> spheres, std::vector<Light> lights);
Vector3f cast_ray(Vector3f origin, Vector3f directrion, std::vector<Sphere> spheres, std::vector<Light> lights);

int main()
{
    std::vector<Sphere> spheres{
        Sphere { Vector3f(-3, -10, 25), 5.0f, RED }, 
        Sphere { Vector3f(2, 1.5, 120), 25.0f, GREEN }, 
    };

    std::vector<Light> lights {
        Light{ Vector3f { -1, 3, 5 }, 0.8 }
    };
    render(spheres, lights);
}

void render(std::vector<Sphere> spheres, std::vector<Light> lights)
{
    const int width_img = 1024;
    const int height_img = 1024;
    const float viewport_width = 2;
    const float viewport_height = 2;
    Vector3f lower_left_corner { -1, -1, 1 };
    std::vector<Vector3f> buffer(width_img * height_img);
    
    Vector3f camera{0, 0, 0};

    for (int i = 0; i < width_img; i++)
        for (int j = 0; j < height_img; j++)
        {
            Vector3f ray_direction{double(i) / width_img * viewport_width,
                                   double(j) / height_img * viewport_height,
                                   0};
            ray_direction = ray_direction + lower_left_corner;
            buffer[i * width_img + j] = cast_ray(camera, ray_direction, spheres, lights);           
        }
        
    std::ofstream out("output.ppm");
    out << "P3\n";
    out << width_img << ' ' << height_img << "\n255\n";

    for (int i = 0; i < width_img; i++)
        for (int j = 0; j < height_img; j++)
            out << int(buffer[i * width_img + j].x) << ' ' << int(buffer[i * width_img + j].y) << ' ' << int(buffer[i * width_img + j].z) << '\n';

    out.close();
}

Vector3f cast_ray(Vector3f origin, Vector3f directrion, std::vector<Sphere> spheres, std::vector<Light> lights)
{
    for(Sphere& sphere: spheres)
    {
        float dist_i;
        if (sphere.intersect(origin, directrion, dist_i))
        {
            float diffuse_intensity = 0.0f;
            for(Light light: lights)
            {
                Vector3f light_dir = (light.position - sphere.center).unit();
                Vector3f intersection_point = origin + directrion.unit() * dist_i;
                Vector3f normal_vec = (intersection_point - (sphere.center - origin)).unit();
                diffuse_intensity += light.intensity * std::max(0.0f, light_dir * normal_vec);
            }

            return sphere.color * diffuse_intensity;
        }
    }
    return Vector3f{200, 200, 200};
}