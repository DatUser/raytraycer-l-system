#pragma once

#include "object.hh"
#include "vector3.hh"
#include "scene.hh"
#include "ppm-texture.hh"

class Cylinder : public Object {
public:
//    Cylinder(Vector3& c, float r, float h, Texture_Material* texture);
    Cylinder(Vector3& bas, Vector3 haut, float r, Texture_Material* texture);

    std::optional<Vector3> intersect(const Vector3& origin,
                                     const Vector3& direction) const final;

    Vector3 get_normal(const Point3& p) const final;

    SurfaceInfo get_texture(const Vector3& p) const final;

private:
    Vector3 bas;
    Vector3 haut;
    Vector3 center;
    Vector3 dir;
    Vector3 vx;
    float radius;
    float height;
    Texture_Material* texture;
};