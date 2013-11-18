#ifndef FOUGCOLDET_SPHERE_COLLISION_TEST_H
#define FOUGCOLDET_SPHERE_COLLISION_TEST_H

#include "global.h"

class FOUGCOLDET_LIB_EXPORT SphereCollisionTest
{
public:
  SphereCollisionTest();
  ~SphereCollisionTest();

  const float* sphereCenter() const;
  void setSphereCenter(float x, float y, float z);

  float sphereRadius() const;
  void setSphereRadius(float radius);

  bool collides() const;

  //! The triangle that collided (belongs to _this_ model)
  void getModelTriangle(float tri[9]);
  //void getWorldTriangle(float tri[9]);

  //! The triangles index that collided (belongs to _this_ model)
  int triangleId() const;

  //! The detected collision point
  const float* point() const;

private:
  class Private;
  friend class CollisionModel3DImpl;
  Private* const d;
};

#endif // FOUGCOLDET_SPHERE_COLLISION_TEST_H
