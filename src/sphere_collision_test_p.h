#ifndef FOUGCOLDET_SPHERE_COLLISION_TEST_P_H
#define FOUGCOLDET_SPHERE_COLLISION_TEST_P_H

#include "sphere_collision_test.h"

#include "box.h"
#include "math3d.h"

class SphereCollisionTest::Private
{
public:
  Private();

  // Input
  Vector3D m_sphereCenter;
  float m_sphereRadius;

  // Output
  /** The triangle that last collided */
  Triangle m_colTri;
  /** The index of the triangle that last collided */
  int m_iColTri;
  /** The collision point of the last test */
  Vector3D m_colPoint;
};

#endif // FOUGCOLDET_SPHERE_COLLISION_TEST_P_H
