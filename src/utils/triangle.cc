#include <utils/triangle.hh>

Triangle::Triangle(Point3& a, Point3& b, Point3& c, Texture_Material* texture)
: a(a),
  b(b),
  c(c),
  texture(texture),
  normal(crossProd(Vector3(a, b), Vector3(a, c)))
{
    normal.normalize();
}

std::optional<Vector3> Triangle::intersect(const Vector3& origin,
    const Vector3& direction) const
{
    // algorithme de Moller-Trumbore
    const float EPSILON = 0.0000001;
    Vector3 vertex0 = a;
    Vector3 vertex1 = b;
    Vector3 vertex2 = c;
    Vector3 edge1, edge2, h, s, q;
    float A, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = crossProd(direction, edge2);
    A = dotProd(edge1, h);
    if (A > -EPSILON && A < EPSILON) {
        return std::nullopt;
    }

    f = 1.0 / A;
    s = origin - vertex0;
    u = f * dotProd(s, h);
    if (u < 0.0 || u > 1.0) {
        return std::nullopt;
    }

    q = crossProd(s, edge1);
    v = f * dotProd(direction, q);
    if (v < 0.0 || u + v > 1.0) {
        return std::nullopt;
    }

    float t = f * dotProd(edge2, q);
    if (t > EPSILON) {
        Vector3 intersection = origin + (direction * t);
        return intersection;
    } else {
        return std::nullopt;
    }

    /*float D = dotProd(normal, a);
    //Here we do not need to negate since the z vector of the camera
    //and projection vector have the same orientation
    float t = - (dotProd(normal, origin) + D) / dotProd(normal, direction);
    if (dotProd(normal, direction) != 0 && t > 0)
    {
        Vector3 hit = origin + direction * t;
        Vector3 A(a, b);
        Vector3 B(b, c);
        Vector3 C(c, a);

        if (dotProd(A, Vector3(hit.x - a.x, hit.y - a.y, hit.z - a.z)) > 0 &&
            dotProd(B, Vector3(hit.x - b.x, hit.y - b.y, hit.z - b.z)) > 0 &&
            dotProd(C, Vector3(hit.x - c.x, hit.y - c.y, hit.z - c.z)) > 0)
            return std::optional<Vector3>{ hit };

        return std::nullopt;
    }

    return std::nullopt;
     */
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
