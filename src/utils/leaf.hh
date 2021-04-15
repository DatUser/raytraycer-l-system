#pragma once

#include "object.hh"
#include "triangle.hh"
#include "scene.hh"

class Leaf : public Object
{
public:
    Leaf(Point3& origin, Point3& dest, float angle, std::shared_ptr<Texture_Material> texture);

    std::optional<Vector3> intersect(const Vector3& origin,
                                     const Vector3& direction) const final;

    Vector3 get_normal(const Point3& p) const final;

    SurfaceInfo get_texture(const Vector3& p) const final;

private:
    Triangle top;
    Triangle bot;
    std::shared_ptr<Texture_Material> texture;
};