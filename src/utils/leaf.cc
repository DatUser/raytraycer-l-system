#include "leaf.hh"

void rotate_leaf(Vector3& v, float angle)
{
    float abs_x = abs(v.x);
    float abs_y = abs(v.y);
    float abs_z = abs(v.z);
    if (abs_x >= abs_y && abs_x >= abs_z)
    {
        rotateAroundZ(v, angle);
    } else if (abs_y >= abs_z) {
        rotateAroundZ(v, angle);
    } else {
        rotateAroundY(v, angle);
    }
}

Leaf::Leaf(Point3 &origin, Point3 &dest, float angle, std::shared_ptr<Texture_Material> texture)
{
    //Point3 middle = origin + ((dest - origin) / 2);
    Vector3 direction_a = (dest - origin).get_normalized();
    Vector3 direction_b = direction_a;
    float dist = sqrt(direction_a.x * direction_a.x +
            direction_a.y * direction_a.y +
            direction_a.z * direction_a.z);

    rotate_leaf(direction_a, angle);
    rotate_leaf(direction_b, -angle);

    float h = dist / cos(angle * M_PI/180);

    Point3 a = origin + (direction_a * h);
    Point3 b = origin + (direction_b * h);

    top = Triangle(a,b, dest, texture);
    bot = Triangle(a,b, origin, texture);

    this->texture = static_cast<const std::shared_ptr<Texture_Material>>(texture);
}

std::optional<Vector3> Leaf::intersect(const Vector3 &origin, const Vector3 &direction) const
{
    std::optional<Vector3> intersection;
    if ((intersection = top.intersect(origin, direction)).has_value())
        return intersection;
    return bot.intersect(origin, direction);
}

Vector3 Leaf::get_normal(const Point3 &p) const
{
    //Here we do not care since top and bot triangle belong to the same 2D plan
    return top.get_normal(p);
}

SurfaceInfo Leaf::get_texture(const Vector3 &p) const
{
    //For now we will use uniform color for texture
    return top.get_texture(p);
}