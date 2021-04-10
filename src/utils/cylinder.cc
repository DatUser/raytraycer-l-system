#include "cylinder.hh"

//Cylinder::Cylinder(Vector3 &c, float r, float h, Texture_Material *texture)
//        : center(c), radius(r), height(h), texture(texture) {}

Cylinder::Cylinder(Vector3 &bas, Vector3 haut, float r, Texture_Material *texture)
        : bas(bas),
          haut(haut),
          center(Vector3((bas.x + haut.x) / 2, (bas.y + haut.y) / 2, (bas.z + haut.z) / 2)),
          dir((haut - bas).get_normalized()),
          radius(r),
          height(sqrt(pow((haut.x - bas.x), 2) + pow((haut.y - bas.y), 2) + pow((haut.z - bas.z), 2))),
          texture(texture) {}

SurfaceInfo Cylinder::get_texture(const Vector3 &p) const {
    if (p.x == 0)
        return texture->get_point_info(0, 0);
    return texture->get_point_info(0, 0);
}

float distance(Vector3 un, Vector3 deux) {
    return sqrt(pow(deux.x - un.x,2) + pow(deux.y - un.y ,2) + pow(deux.z - un.z ,2));
}

Vector3 Cylinder::get_normal(const Point3 &p) const {
    if ((p - haut).norm < radius) {
        return  dir;
    }
    if ((p - bas).norm < radius) {
        return -dir;
    }
    auto t = dotProd((p - bas), dir);
    auto tmp = bas + dir * t;
    return (p - tmp).get_normalized();


    /*
    //Check if the point is on the upper plane
    double d1 = -(dotProd(dir, haut));
    if(dotProd(dir, p) + d1 <= radius * radius)
        return (dir);
    //Check if the point is on the lower plane
    double d2 = -(dotProd(-dir, bas));
    if(dotProd(-dir, p) + d2 <= radius * radius)
        return (-dir);
    //Find the normal vector to the plane formed by a, b and p

    Vector3 perpendicular = crossProd((p - bas), dir);
//    The cylinder direction cross this vector will give me the normal
    return crossProd(dir, perpendicular);*/
}

std::optional<Vector3> Cylinder::intersect(const Vector3 &origin, const Vector3 &direction) const {


    //Check the intersection with the upper plane
    double dotP1 = dotProd(dir, direction);
    if(dotP1 < 0)
    {
        double d1 = -(dotProd(dir, haut));
        double t1 = -(d1 + dotProd(dir, origin))/dotP1;
        Vector3 p1 = origin + (direction * t1);

        if((p1 - haut).magnitudeSquared() <= (radius * radius) * 0.999)
            return origin + (direction * t1);
    }
    //Check the intersection with the lower plane
    double dotP2 = dotProd(-dir, direction);
    if(dotP2 < 0)
    {
        double d2 = -(dotProd((-dir),bas));
        double t2 = -(d2 + dotProd(-dir, origin) ) / dotP2;
        Vector3 p2 = origin + (direction * t2);

        if((p2 - bas).magnitudeSquared() <= (radius * radius) * 0.999)
            return origin + (direction * t2);
    }


    //Check the intersection with the torso
    Vector3 AB = (bas - haut);
    Vector3 AO = (origin - haut);
    Vector3 AOxAB = crossProd(AO, AB);
    Vector3 VxAB = crossProd(direction, AB);
    double ab2 = dotProd(AB, AB);
    double A = dotProd(VxAB, VxAB);
    double B = 2 * dotProd(VxAB, AOxAB);
    double C = dotProd(AOxAB, AOxAB) - (radius * radius * ab2);

    double discr = B * B - 4 * A * C;

    if(discr<0) {
        return std::nullopt;
    }

    if (discr >= -0.000001 and discr <= 0.000001) {
        double t = (-B) / (2.0f * A);
        return origin + (direction * t);
    }

//    double t1 = (-B + sqrt(discr))/(2*A);
//    double t2 = (-B - sqrt(discr))/(2*A);

    double t2 = (-B - sqrt(discr)) / (2.0f * A);
    double t1 = (-B + sqrt(discr)) / (2.0f * A);


    if (t2 < 0 && t1 < 0) {
        return std::nullopt;
    }
    float t = t2;
    if (t1 < t2) {
        t = t1;
    }
    /*double t = (t1 < t2)?t1:t2;
    if(t < 0)
        t = (t1 > t2)?t1:t2;*/

    auto res = origin + (direction * t);
    auto hautRes = haut - res;
    auto basRes = bas - res;
    auto dotHautRes = dotProd(dir, hautRes);
    auto dotBasRes = dotProd(dir, basRes);
    if (dotHautRes >= -0.00001 and dotBasRes <= 0.00001) {
        return res;
    }

    return std::nullopt;


    //Return the smallest t greater than 0, because it was the first intersection
//    return origin + (direction * t);


    /*float a = (direction.x * direction.x) + (direction.z * direction.z);
    float b = 2 * (direction.x * (origin.x - center.x) + direction.z * (origin.z - center.z));
    float c = (origin.x - center.x) * (origin.x - center.x) + (origin.z - center.z) * (origin.z - center.z) -
              (radius * radius);

    float delta = b * b - 4 * (a * c);
    if (delta < -0.001) {
        return std::nullopt;
    }
    if (delta < 0.001) {
        float t = (-b / (2 * a));
        return origin + direction * t;
        return intersectDisk(center.get_normalized(), haut, radius, origin, direction);
    }

    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);
    std::optional<Vector3> res = std::nullopt;
    if (t2 > 0 && (t1 < 0 || t2 < t1))
        res = origin + (direction * t2);
    else if (t1 > 0)
        res = origin + (direction * t1);

    if (res != std::nullopt) {
        if (res->y >= bas.y and res->y < haut.y) {
            return res;
        }
    }*/


    /*float tmp;
    float t;

    if (t1 > t2) {
        t = t2;
        tmp = t1;
    } else {
        t = t1;
        tmp = t2;
    }

    auto res = origin + direction * t;
    if (res.y >= bas.y and res.y < haut.y) {
        return res;
    }

    res = origin + direction * tmp;
    if (res.y >= bas.y and res.y <= haut.y) {
        return res;
    }*/

    /*float r = origin.y + t * direction.y;

    if ((r >= center.y) and (r <= center.y + height)) {
        return origin + direction * t;
    }*/
    return std::nullopt;
}
