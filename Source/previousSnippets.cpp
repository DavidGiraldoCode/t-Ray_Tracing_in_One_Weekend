/*

color rayColor(const ray &r)
{
    point3 sphereCenter = point3(0, 0, -1);
    
    // if(hitSphere(point3(0,0,-1), 0.5, r) >= 0)
    // {
    //     double t = hitSphere(point3(0,0,-1), 0.5, r);
    //     point3 pointOnSphere = r.at(t);
    //     vec3 normal = vec3(0.5, 0.5, 0.5) / (pointOnSphere - point3(0,0,-1));
    //     color color = 0.5 * (normal.x() + 1.0)
    //     return
    //     //color(1.0, 0, 0);
    // }

    double t = hitSphere(sphereCenter, 0.5, r);
    if (t >= 0)
    {
        vec3 normal = unit_vector(r.at(t) - sphereCenter);
        auto rMap = 0.5 * (normal.x() + 1.0);
        auto gMap = 0.5 * (normal.y() + 1.0);
        auto bMap = 0.5 * (normal.z() + 1.0);
        // return color(rMap,gMap,bMap);

        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unitDirection = unit_vector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);

    // std::cout << double(unitDirection.y()) << " unitDirection.y()\n";
    // std::cout << double(a) << " a\n";
    color startColor = color(1.0, 1.0, 1.0);
    color endColor = color(0.5, 0.7, 1.0);

    color interpolatedColor = ((1.0 - a) * startColor) + (a * endColor);
    // std::cout << interpolatedColor << " interpolatedColor\n";

    return interpolatedColor; //(1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
}

color rayColor(const ray &r, const Sphere &sphere)
{
    hit_record hitRecord;
    bool hit = sphere.hit(r, 0.1, 5.0, hitRecord);

    if (hit)
    {
        vec3 normal = hitRecord.normal;
        auto rMap = 0.5 * (normal.x() + 1.0);
        auto gMap = 0.5 * (normal.y() + 1.0);
        auto bMap = 0.5 * (normal.z() + 1.0);
        // return color(rMap,gMap,bMap);

        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unitDirection = unit_vector(r.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);

    // std::cout << double(unitDirection.y()) << " unitDirection.y()\n";
    // std::cout << double(a) << " a\n";
    color startColor = color(1.0, 1.0, 1.0);
    color endColor = color(0.5, 0.7, 1.0);

    color interpolatedColor = ((1.0 - a) * startColor) + (a * endColor);
    // std::cout << interpolatedColor << " interpolatedColor\n";

    return interpolatedColor; //(1.0 - a) * color(1.0, 1.0, 1.0) + (a * color(0.5, 0.7, 1.0));
}


void setImageAndViewPort()
{
    auto aspectRatio = 9 / 16;

    unsigned imageWidth = 800;
    unsigned imageHeight = unsigned(imageWidth / aspectRatio);
    imageHeight = imageHeight < 1 ? 1 : imageHeight; // Make sure is at least 1

    // View port is the virtual square IN 3D SPACE (meaning is actully in the scene) containing the pixel grid that represent the image
    auto viewPortHeight = 2;
    auto viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);
}

//bool
double hitSphereDefault(const point3& center, double radius, const ray& r)
{
    vec3 CO = center - r.origin();
    // Compute all the term of the quadratic formula ax^2 + by + c
    double a = dot(r.direction(), r.direction());                       // Self-try dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), CO );                          // dot((-2 * r.direction()), (center - r.origin()) );
    double c = dot(CO, CO) - (radius * radius);                         //dot((center - r.origin()), (center - r.origin())) - (radius * radius);

    // Compute the quadratic formula
    double discriminant = (b*b) - (4*a*c);

    // discriminant == 0 -> one intersection
    // discriminant > 0 -> two intersections
    // discriminant < 0 -> zero intersections
    if(discriminant < 0) return -1.0; // Previously I was returning false, which will yield the purple sky

    //return discriminant >= 0 ;
    double t1 = (-b - std::sqrt(discriminant)) / (2 * a); // Missing the sqrt, the () are KEY to avoid unwanted behaviour
    //double t2 = -b - discriminant / 2*a;
    return t1;
}

double hitSphere(const point3& center, double radius, const ray& r)
{
    vec3 QC = (center - r.origin());

    double a = r.direction().length_squared();
    double c = QC.length_squared() - (radius * radius);
    double h = dot(r.direction(), QC);

    double discriminant = (h*h) - (a*c);

    if(discriminant < 0)
    {
        return -1;
    }
    else return (h - std::sqrt(discriminant)) / a;
    // We use (-) between h and the sqrt because a negative value int th descriminant will yield a positive result
}


*/