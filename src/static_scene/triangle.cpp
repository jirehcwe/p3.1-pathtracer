#include "triangle.h"

#include "CGL/CGL.h"
#include "GL/glew.h"

namespace CGL { namespace StaticScene {

Triangle::Triangle(const Mesh* mesh, size_t v1, size_t v2, size_t v3) :
    mesh(mesh), v1(v1), v2(v2), v3(v3) { }

BBox Triangle::get_bbox() const {

  Vector3D p1(mesh->positions[v1]), p2(mesh->positions[v2]), p3(mesh->positions[v3]);
  BBox bb(p1);
  bb.expand(p2); 
  bb.expand(p3);
  return bb;

}

bool Triangle::intersect(const Ray& r) const {

  // TODO (Part 1.3):
  // implement ray-triangle intersection

  Vector3D p0(mesh->positions[v1]), p1(mesh->positions[v2]), p2(mesh->positions[v3]);
  
  Vector3D e1 = p1 - p0;
  Vector3D e2 = p2 - p0;
  Vector3D s0 = r.o - p0;
  Vector3D s1 = cross(r.d, e2);
  Vector3D s2 = cross(s0, e1);

  Vector3D bary = Vector3D(dot(s2, e2), dot(s1, s0), dot(s2, r.d))/(dot(s1, e1));
  

  double b3 = 1 - bary.y - bary.z;

  if (bary.y > 1 || bary.y < 0 || bary.z > 1 || bary.z < 0 || b3 > 1 || b3 < 0){
    return false;
  }

  if (bary.x < 0){
    return false;
  }

  if (bary.x < r.min_t || bary.x > r.max_t){
    return false;
  }

  r.max_t = bary.x;

  return true;


}

bool Triangle::intersect(const Ray& r, Intersection *isect) const {
  
  // TODO (Part 1.3):
  // implement ray-triangle intersection. When an intersection takes
  // place, the Intersection data should be updated accordingly

  Vector3D p0(mesh->positions[v1]), p1(mesh->positions[v2]), p2(mesh->positions[v3]);
  Vector3D n1(mesh->normals[v1]), n2(mesh->normals[v2]), n3(mesh->normals[v3]);
  
  
    
  Vector3D e1 = p1 - p0;
  Vector3D e2 = p2 - p0;
  Vector3D s0 = r.o - p0;
  Vector3D s1 = cross(r.d, e2);
  Vector3D s2 = cross(s0, e1);

  Vector3D bary = (double)1/(dot(s1, e1))*(Vector3D(dot(s2, e2), dot(s1, s0), dot(s2, r.d)));
  
  double b2 = bary.y;
  double b3 = bary.z;
  double b1 = 1 - b2- b3;
  
  

  if (b1 < 0 || b1 > 1 || b2 < 0 || b2 > 1 || b3 > 1 || b3 < 0){
    return false;
  }

  if (bary.x < r.min_t || bary.x > r.max_t){
    return false;
  }

  r.max_t = bary.x;
  Vector3D normal = b1*n1+b2*n2+b3*n3;
  normal.normalize();

  isect->t = bary.x;
  isect->n = normal;
  isect->primitive = this;
  isect->bsdf = get_bsdf();
  
  return true;
}

void Triangle::draw(const Color& c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_TRIANGLES);
  glVertex3d(mesh->positions[v1].x,
             mesh->positions[v1].y,
             mesh->positions[v1].z);
  glVertex3d(mesh->positions[v2].x,
             mesh->positions[v2].y,
             mesh->positions[v2].z);
  glVertex3d(mesh->positions[v3].x,
             mesh->positions[v3].y,
             mesh->positions[v3].z);
  glEnd();
}

void Triangle::drawOutline(const Color& c, float alpha) const {
  glColor4f(c.r, c.g, c.b, alpha);
  glBegin(GL_LINE_LOOP);
  glVertex3d(mesh->positions[v1].x,
             mesh->positions[v1].y,
             mesh->positions[v1].z);
  glVertex3d(mesh->positions[v2].x,
             mesh->positions[v2].y,
             mesh->positions[v2].z);
  glVertex3d(mesh->positions[v3].x,
             mesh->positions[v3].y,
             mesh->positions[v3].z);
  glEnd();
}



} // namespace StaticScene
} // namespace CGL
