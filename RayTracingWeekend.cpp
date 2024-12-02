#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>



//P(t) = orig + t*dir - ray
//a*t2 + bt + c = 0
double hit_sphere(const point3& center, double radius, const ray& r) {

    // Ray origin to sphere center
    vec3 oc = center - r.origin();

    // Squared length of ray's direction vector
    auto a = r.direction().length_squared();

    // Solving intersection
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    // Squared root
    auto discriminant = h * h - a * c;

    // Discriminant < 0 - No intersection
    // Discriminant = 0 - Tangent intersection
    // Discriminant > 0 - Two intersections

    // Determines if ray intersects sphere
    if (discriminant < 0) {
        return -1.0;
    }
    else {
        // Nearest interesection point (smaller t) from quadratic formula 
        return (h - std::sqrt(discriminant)) / a;
    }
}

// Create sky gradient background
color ray_color(const ray& r) {

    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    // Extract direction vector of ray
    vec3 unit_direction = unit_vector(r.direction());

    // Extract y and scale from 0.0 to 1.0
    // a = 0 - ray downward
    // a = 1 - ray upward
    auto a = 0.5 * (unit_direction.y() + 1.0);

    // Blend white and blue based on a's direction
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate size of a single pixel's width and height in the viewport space.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Upper left corner of the viewport
    auto viewport_upper_left = camera_center
        - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

    // Position of top left pixel of viewport
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            // Calculate the center of the current pixel(i, j).
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

            // Compute the ray direction from the camera to the pixel.
            auto ray_direction = pixel_center - camera_center;

            // Create a ray from the camera through the pixel.
            ray r(camera_center, ray_direction);

            //Determine the pixel's color based on the ray's interactions with the scene.
            color pixel_color = ray_color(r);

            // Write the pixel's color to the output for inclusion in the final image
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}