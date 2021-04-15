#pragma once

#include "object.hh"
#include "triangle.hh"
#include "scene.hh"

class Polygon : public Object
{
public:
    //There must be atleast 3 point
    Polygon(const std::vector<Point3>& points, std::shared_ptr<Texture_Material> texture);

    std::optional<Vector3> intersect(const Vector3& origin,
                                     const Vector3& direction) const final;

    Vector3 get_normal(const Point3& p) const final;

    SurfaceInfo get_texture(const Vector3& p) const final;

private:
    std::vector<Triangle> triangles;
    std::shared_ptr<Texture_Material> texture;
};