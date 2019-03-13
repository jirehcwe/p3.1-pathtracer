#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

  // TODO (Part 2.2):
  // Implement ray - bounding box intersection test
  // If the ray intersected the bouding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.
  double tXmin = (min.x - r.o.x)/r.d.x;
  double tYmin = (min.y - r.o.y)/r.d.y;
  double tZmin = (min.z - r.o.z)/r.d.z;
  double tXmax = (max.x - r.o.x)/r.d.x;
  double tYmax = (max.y - r.o.y)/r.d.y;
  double tZmax = (max.z - r.o.z)/r.d.z;

  if (tXmin > tXmax){
    double temp = tXmax;
    tXmax = tXmin;
    tXmin = temp; 
  }
  if (tYmin > tYmax){
    double temp = tYmax;
    tYmax = tYmin;
    tYmin = temp;
  }
  if (tZmin > tZmax){
    double temp = tZmax;
    tZmax = tZmin;
    tZmin = temp;
  }


  double test0, test1;

  //Finding maximum of mins and mins of maxes
  test0 = std::max (std::max(tXmin, tYmin), tZmin);
  test1 = std::min (std::min(tXmax, tYmax), tZmax);

  if (test0 > test1){
    return false;
  }

  // if (test0 < t0 || test1 > t1 || test0 < r.min_t || test1 > r.max_t){
  //   return false;
  // }

  return true;
}

void BBox::draw(Color c, float alpha) const {

  glColor4f(c.r, c.g, c.b, alpha);

  // top
  glBegin(GL_LINE_STRIP);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
  glEnd();

  // bottom
  glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glEnd();

  // side
  glBegin(GL_LINES);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
  glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
