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


  double test0, test1;

  if (tXmin > tYmin){
    if (tXmin > tZmin){
      test0 = tXmin;
    } else {
      test0 = tZmin;
    }
  } else {
    if (tYmin > tZmin){
      test0 = tYmin;
    } else {
      test0 = tZmin;
    }
  }

  if (tXmax > tYmax){
    if (tXmax > tZmax){
      test1 = tXmax;
    } else {
      test1 = tZmax;
    }
  } else {
    if (tYmax > tZmax){
      test1 = tYmax;
    } else {
      test1 = tZmax;
    }
  }

  // double test0 = (tXmin > tYmin ? tXmin : tYmin) > (tYmin > tZmin ? tYmin : tZmin) ? (tXmin > tYmin ? tXmin : tYmin) : (tYmin > tZmin ? tYmin : tZmin);
  // double test1 = (tXmax < tYmax ? tXmax : tYmax) < (tYmax < tZmax ? tYmax : tZmax) ? (tXmax < tYmax ? tXmax : tYmax) : (tYmax < tZmax ? tYmax : tZmax);
  
  

  // if (test0 < test1){
  //   return false;
  // } else 
  if (test0 < 0 && test1 < 0){
    return false;
  } else {
    t0 = test0;
    t1 = test1;
    return true;
  }

  
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
