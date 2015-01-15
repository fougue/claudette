#include "sphere_collision_test.h"

#include "math3d.h"

SphereCollisionTest::SphereCollisionTest()
    : m_sphereRadius(0)
{
    Vector3D::fillFloatVec(m_sphereCenter, 0);
}

const float *SphereCollisionTest::sphereCenter() const
{
    return m_sphereCenter;
}

void SphereCollisionTest::setSphereCenter(float x, float y, float z)
{
    Vector3D::setFloatVec(m_sphereCenter, x, y, z);
}

float SphereCollisionTest::sphereRadius() const
{
    return m_sphereRadius;
}

void SphereCollisionTest::setSphereRadius(float radius)
{
    m_sphereRadius = radius;
}
