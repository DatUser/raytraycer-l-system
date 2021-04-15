#pragma once
#include <memory>

#include <utils/object.hh>

class Triangle : public Object
{
    public:
        Triangle() = default;

        Triangle(const Point3& a, const Point3& b, const Point3& c, std::shared_ptr<Texture_Material> texture);

        std::optional<Vector3> intersect(const Vector3& origin,
            const Vector3& direction) const final;

        Vector3 get_normal(const Point3& p) const final;

        SurfaceInfo get_texture(const Vector3& p) const final;

    private:
        Point3 a;
        Point3 b;
        Point3 c;
        std::shared_ptr<Texture_Material> texture;
        Vector3 normal;
};
