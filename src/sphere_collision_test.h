#ifndef FOUGCOLDET_SPHERE_COLLISION_TEST_H
#define FOUGCOLDET_SPHERE_COLLISION_TEST_H

#include "base_collision_test.h"

/*! \brief Collision test with a sphere
 */
class FOUGCOLDET_LIB_EXPORT SphereCollisionTest : public BaseCollisionTest
{
public:
  SphereCollisionTest();

  const float* sphereCenter() const;
  void setSphereCenter(float x, float y, float z);

  float sphereRadius() const;
  void setSphereRadius(float radius);

private:
  float m_sphereCenter[3];
  float m_sphereRadius;
};

#endif // FOUGCOLDET_SPHERE_COLLISION_TEST_H
