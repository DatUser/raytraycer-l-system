#include "scene.hh"
#include <cmath>

const unsigned int ALIASING_RAY = 5;
const Color ambient{0.05,0.05,0.05};

Scene::Scene(Camera camera)
        : objects(std::vector<Object *>()),
          lights(std::vector<Light>()),
          camera(camera) {}

// Angle in degree
void rotateAroundY(Vector3 &v, float angle) {
    float rad_angle = angle * (M_PI / 180);
    float tmp_x = v.x;
    float tmp_z = v.z;
    v.x = tmp_x * cos(rad_angle) + tmp_z * sin(rad_angle);
    v.z = -tmp_x * sin(rad_angle) + tmp_z * cos(rad_angle);
}

void rotateAroundX(Vector3 &v, float angle) {
    float rad_angle = angle * (M_PI / 180);
    float tmp_y = v.y;
    float tmp_z = v.z;
    v.y = tmp_y * cos(rad_angle) - tmp_z * sin(rad_angle);
    v.z = tmp_y * sin(rad_angle) + tmp_z * cos(rad_angle);
}

Vector3 Scene::project_vector(const Vector3 &v, const Vector3 &x_basis,
                              const Vector3 &y_basis, const Vector3 &z_basis,
                              const Vector3 &translation) const {
    float x_world = v.x * x_basis.x + v.y * y_basis.x + v.z * z_basis.x
                    + translation.x;
    float y_world = v.x * x_basis.y + v.y * y_basis.y + v.z * z_basis.y
                    + translation.y;
    float z_world = v.x * x_basis.z + v.y * y_basis.z + v.z * z_basis.z
                    + translation.z;

    return Vector3(x_world /*- camera.center.x*/, y_world /*- camera.center.y*/,z_world /*- camera.center.z*/);
}

Color Scene::find_color(const Point3 &origin, const Vector3 &forward, int depth, const Object* source) const {
    if (depth >= 3)
        return Color(0, 0, 0);

    float closest = std::numeric_limits<float>::max();

    Color color = ambient;//{0, 0, 0};
    std::optional<Vector3> intersection;
    float p_norm = 0;

    for (unsigned int i = 0; i < objects.size(); i++) {
        const Object *obj = objects[i];
        if ((intersection = obj->intersect(origin, forward)).has_value() &&
            (p_norm = norm(camera.center, intersection.value())) < closest &&
            dotProd(camera.z, (intersection.value() - camera.center)) > 0) //
        {
            if (obj != source) {
                closest = p_norm;
                color = compute_light(origin, intersection.value(), obj, depth);
            }
        }
    }

    return color;
}

bool Scene::intersect(const Point3& origin, const Vector3& direction, const Object* source) const
{
    std::optional<Vector3> intersection;
    Object* closest_obj = NULL;
    float closest = std::numeric_limits<float>().max();
    float p_norm =0;
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        Object *obj = objects[i];
        if ((intersection = obj->intersect(origin, direction)).has_value() &&
            (p_norm = norm(camera.center, intersection.value())) < closest)
        {
            closest = p_norm;
            closest_obj = obj;
        }
    }

    return closest_obj != source;
}

Color Scene::compute_light(const Point3 &origin, const Point3 &hitpoint, const Object *object, int depth) const {
    /*if (depth >= 2)
        return Color(0, 0, 0);*/
    Color color = ambient;//{0, 0, 0};
    (void) origin;
    Vector3 incoming = Vector3(origin, hitpoint).get_normalized();

    for (unsigned int i = 0; i < lights.size(); i++) {

        Light light = lights[i];
        Vector3 light_rev = Vector3(light.get_position(), hitpoint).get_normalized();

        if (intersect(light.get_position(), light_rev, object))
            break;

        //Compute diffuse
        SurfaceInfo info = object->get_texture(hitpoint);
        //Collision to light
        Vector3 light_v = Vector3(hitpoint, light.get_position()).get_normalized();
        Vector3 n = object->get_normal(hitpoint);
        float d = dotProd(light_v, n);
        if (d >= 0)
            color += info.color * light.get_color() * info.kd * (d);

        //Compute specular component

        //Calculate reflected vector
        Vector3 s = incoming - n * 2 * dotProd(incoming.get_normalized(), n);// - incoming;

        float d2 = dotProd(s, light_v);

        if (d2 > 0)
        {
            Color spec = light.get_color() * info.ks * std::pow(d2, info.ns);
            color += spec;
        }

        if (dotProd(n, s) > 0)
            color += find_color(hitpoint, s, depth + 1, object);
    }
    return color;
}

void Scene::capture_image(Image &image) const {
    float width = (camera.z_pos * tan(camera.x_angle / 2 * M_PI / 180)) * 2;
    float left_shift = width / 2;
    float height = (camera.z_pos * tan(camera.y_angle / 2 * M_PI / 180)) * 2;
    float down_shift = height / 2;

    /*Vector3 y = camera.up;
    Vector3 z = Vector3(camera.center, camera.target).get_normalized();
    Vector3 x = crossProd(y, z);*/
    Vector3 translation = Vector3(camera.center.x, camera.center.y,
                                  camera.center.z);

    std::ofstream os("projected.txt");

    for (unsigned int i = 0; i < image.height; i++) {
        for (unsigned int j = 0; j < image.width; j++) {
            Color color = Color(0,0,0);
            //multiple ray per pixel (anti-aliasing)
            for (unsigned int k = 0; k < ALIASING_RAY; k++) {
                float v_y = (image.height - i - 0.5) * height / image.height - down_shift;
                float v_x = (image.width * ALIASING_RAY - (j * ALIASING_RAY + k) - 0.5) * width / (image.width * ALIASING_RAY) - left_shift;
                Vector3 projection = project_vector(Vector3(v_x, v_y, camera.z_pos),
                                                    camera.x, camera.y, camera.z, translation);

                if (k == 0)
                    os << projection;

                Color color_tmp = find_color(projection, /*z*/(projection - camera.center).get_normalized(), 0);
                color_tmp.clamp();
                color += color_tmp;
            }
            color = color * (0.2);
            image.put_pixel(i, j, color);
        }
        os << std::endl;
    }

    os.close();
}

void Scene::add_object(Object *object) {
    objects.push_back(object);
}

void Scene::add_light(Light &light) {
    lights.push_back(light);
}
