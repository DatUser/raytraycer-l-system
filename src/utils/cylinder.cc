#include "cylinder.hh"

Cylinder::Cylinder(Vector3 &bas, Vector3 haut, float r, Texture_Material *texture)
        : bas(bas),
          haut(haut),
          center(Vector3((bas.x + haut.x) / 2, (bas.y + haut.y) / 2, (bas.z + haut.z) / 2)),
          dir((haut - bas).get_normalized()),
          vx(crossProd(dir, (dir + Vector3(-1, 5, -98)).get_normalized())),
          radius(r),
          height(sqrt(pow((haut.x - bas.x), 2) + pow((haut.y - bas.y), 2) + pow((haut.z - bas.z), 2))),
          texture(texture) {}

SurfaceInfo Cylinder::get_texture(const Vector3 &p) const {
    float x, y;
    Vector3 n = get_normal(p);
    x = acos(dotProd(vx, n) / (sqrt(vx.magnitudeSquared()) * sqrt(n.magnitudeSquared()))) * 180.0 / M_PI;
    y = sqrt((p - (bas + n * radius)).magnitudeSquared());
    return texture->get_point_info(x / 360, y / sqrt((haut - bas).magnitudeSquared()));
}

float distance(Vector3 un, Vector3 deux) {
    return sqrt(pow(deux.x - un.x, 2) + pow(deux.y - un.y, 2) + pow(deux.z - un.z, 2));
}

Vector3 Cylinder::get_normal(const Point3 &p) const {
    if ((p - haut).norm < radius) {
        return dir;
    }
    if ((p - bas).norm < radius) {
        return -dir;
    }
    auto t = dotProd((p - bas), dir);
    auto tmp = bas + dir * t;
    return (p - tmp).get_normalized();
}

std::optional<Vector3> Cylinder::intersect(const Vector3 &origin, const Vector3 &direction) const {


    //intersect du chapeau du haut
    double dotP1 = dotProd(dir, direction);
    if (dotP1 < 0) {
        double d1 = -(dotProd(dir, haut));
        double t1 = -(d1 + dotProd(dir, origin)) / dotP1;
        Vector3 p1 = origin + (direction * t1);

        if ((p1 - haut).magnitudeSquared() <= (radius * radius) * 0.999)
            return origin + (direction * t1);
    }

    //intersect du chapeau du bas
    double dotP2 = dotProd(-dir, direction);
    if (dotP2 < 0) {
        double d2 = -(dotProd((-dir), bas));
        double t2 = -(d2 + dotProd(-dir, origin)) / dotP2;
        Vector3 p2 = origin + (direction * t2);

        if ((p2 - bas).magnitudeSquared() <= (radius * radius) * 0.999)
            return origin + (direction * t2);
    }

    //intersect du cylinder
    Vector3 AB = (bas - haut);
    Vector3 AO = (origin - haut);
    Vector3 AOxAB = crossProd(AO, AB);
    Vector3 VxAB = crossProd(direction, AB);
    double ab2 = dotProd(AB, AB);
    double A = dotProd(VxAB, VxAB);
    double B = 2 * dotProd(VxAB, AOxAB);
    double C = dotProd(AOxAB, AOxAB) - (radius * radius * ab2);

    double discr = B * B - 4 * A * C;

    if (discr < 0) {
        return std::nullopt;
    }

    if (discr >= -0.000001 and discr <= 0.000001) {
        double t = (-B) / (2.0f * A);
        return origin + (direction * t);
    }

    double t2 = (-B - sqrt(discr)) / (2.0f * A);
    double t1 = (-B + sqrt(discr)) / (2.0f * A);


    if (t2 < 0 && t1 < 0) {
        return std::nullopt;
    }
    float t = t2;
    if (t1 < t2) {
        t = t1;
    }

    auto res = origin + (direction * t);
    auto hautRes = haut - res;
    auto basRes = bas - res;
    auto dotHautRes = dotProd(dir, hautRes);
    auto dotBasRes = dotProd(dir, basRes);
    if (dotHautRes >= -0.00001 and dotBasRes <= 0.00001) {
        return res;
    }

    return std::nullopt;
}
