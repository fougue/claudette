#ifndef FOUGCOLDET_RAY_COLLISION_TEST_P_H
#define FOUGCOLDET_RAY_COLLISION_TEST_P_H

#include "ray_collision_test.h"

#include "box.h"
#include "math3d.h"

class RayCollisionTest::Private
{
public:
  Private();

  // Input
  Vector3D m_rayOrigin;
  Vector3D m_rayDirection;
  float m_raySegMin;
  float m_raySegMax;
  RayCollisionTest::Search m_raySearch;

  // Output
  /** The triangle that last collided */
  Triangle m_colTri;
  /** The index of the triangle that last collided */
  int m_iColTri;
  /** The collision point of the last test */
  Vector3D m_colPoint;
};

#endif // FOUGCOLDET_RAY_COLLISION_TEST_P_H
