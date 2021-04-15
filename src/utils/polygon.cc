#include "polygon.hh"

Polygon::Polygon(const std::vector<Point3>& points, std::shared_ptr<Texture_Material> texture)
{
    triangles = std::vector<Triangle>();
    Point3 last = points[points.size() - 1];
    for (unsigned int i = 0; i < points.size() - 2; i++)
    {
        triangles.push_back(Triangle(points[i], points[i + 1], last, texture));
    }

    this->texture = static_cast<const std::shared_ptr<Texture_Material>>(texture);
}

std::optional<Vector3> Polygon::intersect(const Vector3 &origin, const Vector3 &direction) const
{
    std::optional<Vector3> intersection;
    for (Triangle triangle : triangles) {
        if ((intersection = triangle.intersect(origin, direction)).has_value())
            return intersection;
    }
    return std::nullopt;
}

Vector3 Polygon::get_normal(const Point3 &p) const
{
    //Here we do not care since all triangles belong to the same 2D plan
    return triangles[0].get_normal(p);
}

SurfaceInfo Polygon::get_texture(const Vector3 &p) const
{
    //For now we will use uniform color for texture
    return triangles[0].get_texture(p);
}