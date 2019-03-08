#include "sphere.h"

#include <cmath>

#include  "../bsdf.h"
#include "../misc/sphere_drawing.h"

namespace CGL { namespace StaticScene {

bool Sphere::test(const Ray& r, double& t1, double& t2) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection test.
  // Return true if there are intersections and writing the
  // smaller of the two intersection times in t1 and the larger in t2.
  double a = dot(r.d, r.d);
  double b = 2*dot((r.o-o), r.d);
  double c = dot((r.o-o), (r.o-o)) - r2;

  double determinant = b*b-4* a*c;

  if (determinant < 0){
    return false;
  }

  if (determinant == 0){
    double root = -b/(2*a);

    t1 = root;
    t2 = root;
    return true;
  }

  float firstRoot = (-b - sqrt(determinant))/(2*a);
  float secondRoot = (-b + sqrt(determinant))/(2*a);


  if (firstRoot > secondRoot){
    t2 = firstRoot;
    t1 = secondRoot;
  } else {
    t1 = firstRoot;
    t2 = secondRoot;
  }
  return true;


}

bool Sphere::intersect(const Ray& r) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note that you might want to use the the Sphere::test helper here.
  double t1;
  double t2;
  bool result = test(r, t1, t2);
  if (result){
    r.max_t = t1;
  }
  
  return result;
}

bool Sphere::intersect(const Ray& r, Intersection *i) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note again that you might want to use the the Sphere::test helper here.
  // When an intersection takes place, the Intersection data should be updated
  // correspondingly.
  double t1;
  double t2;
  bool result = test(r, t1, t2);
  if (result){
    r.max_t = t1;
    i->t = t1;
    i->n = (r.at_time(t1)-o);
    i->n.normalize();
    i->primitive = this;
    i->bsdf = get_bsdf();
  }
  
  return result;

  
}

void Sphere::draw(const Color& c, float alpha) const {
  Misc::draw_sphere_opengl(o, r, c);
}

void Sphere::drawOutline(const Color& c, float alpha) const {
    //Misc::draw_sphere_opengl(o, r, c);
}


} // namespace StaticScene
} // namespace CGL
