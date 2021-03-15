#include <utils/triangle.hh>

Triangle::Triangle(Point3& a, Point3& b, Point3& c, Texture_Material* texture)
: a(a),
  b(b),
  c(c),
  texture(texture),
  normal(Vector3(a, b) * Vector3(a, c))
{
    normal.normalize();
}

std::optional<Vector3> Triangle::intersect(const Vector3& origin,
    const Vector3& direction) const
{
    float D = normal ^ a;
    //Here we do not need to negate since the z vector of the camera
    //and projection vector have the same orientation
    float t = ((normal ^ origin) + D) / (normal ^ direction);
    if ((normal ^ direction) != 0 && t > 0)
    {
        Vector3 hit = origin + direction * t;
        Vector3 A(a, b);
        Vector3 B(b, c);
        Vector3 C(c, a);

        if ((A ^ Vector3(hit.x - a.x, hit.y - a.y, hit.z - a.z)) > 0 &&
            (B ^ Vector3(hit.x - b.x, hit.y - b.y, hit.z - b.z)) > 0 &&
            (C ^ Vector3(hit.x - c.x, hit.y - c.y, hit.z - c.z)) > 0)
            return std::optional<Vector3>{ hit };

        return std::nullopt;
    }

    return std::nullopt;
}

Vector3 Triangle::get_normal(const Point3& p) const
{
    (void) p;
    return normal;
}

SurfaceInfo Triangle::get_texture(const Vector3& p) const
{
    (void) p;
    return texture->get_point_info(0, 0);
}
