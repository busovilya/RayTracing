#include <fstream>
#include <iostream>
#include <vector>

#include "light.h"
#include "sphere.h"
#include "camera.h"

#define RED     Vector3f { 255, 0, 0 }
#define GREEN   Vector3f { 0, 255, 0 }
#define BLUE    Vector3f { 0, 0, 255 }

void render(std::vector<Sphere> spheres, std::vector<Light> lights);
Vector3f cast_ray(Ray ray, std::vector<Sphere> spheres, std::vector<Light> lights);

int main()
{
    std::vector<Sphere> spheres{
        Sphere { Vector3f(-5, 0, 25), 5.0f, RED }, 
        Sphere { Vector3f(-10, -5, 20), 5.0f, GREEN }, 
    };

    std::vector<Light> lights {
        Light{ Vector3f { 2, 3, 2 }, 1.0 }
    };
    render(spheres, lights);
}

void render(std::vector<Sphere> spheres, std::vector<Light> lights)
{
    const int IMG_WIDTH = 640;
    const int IMG_HEIGHT = 480;
    const float VIEWPORT_WIDTH = 2;
    const float VIEWPORT_HEIGHT = 2;
    Vector3f lower_left_corner { -1, -1, 1 };
    std::vector<Vector3f> buffer(IMG_WIDTH * IMG_HEIGHT);

    Camera camera(Vector3f {0, 0, 0}, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, lower_left_corner);

    for (int i = 0; i < IMG_WIDTH; i++)
        for (int j = 0; j < IMG_HEIGHT; j++)
        {
            Ray ray = camera.getRay(float(i) / IMG_WIDTH, float(j) / IMG_HEIGHT);
            buffer[j * IMG_WIDTH + i] = cast_ray(ray, spheres, lights);           
        }
        
    std::ofstream out("output.ppm");
    out << "P3\n";
    out << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

    for (int i = 0; i < IMG_HEIGHT; i++)
        for (int j = 0; j < IMG_WIDTH; j++)
            out << int(buffer[i * IMG_WIDTH + j].x) << ' ' << int(buffer[i * IMG_WIDTH + j].y) << ' ' << int(buffer[i * IMG_WIDTH + j].z) << '\n';

    out.close();
}

Vector3f cast_ray(Ray ray, std::vector<Sphere> spheres, std::vector<Light> lights)
{
    for(Sphere& sphere: spheres)
    {
        float dist;
        if (sphere.intersect(ray, dist))
        {
            float diffuse_intensity = 0.0f;
            for(Light light: lights)
            {
                Vector3f light_dir = (light.position - sphere.center).unit();
                Vector3f intersection_point = ray.origin + ray.direction.unit() * dist;
                Vector3f normal_vec = (intersection_point - (sphere.center - ray.origin)).unit();
                diffuse_intensity += light.intensity * std::max(0.0f, light_dir * normal_vec);
            }

            return sphere.color * diffuse_intensity;
        }
    }
    return Vector3f{200, 200, 200};
}