#include "sphere_collision_test.h"

#include "sphere_collision_test_p.h"

SphereCollisionTest::Private::Private()
  : m_sphereCenter(0, 0, 0),
    m_sphereRadius(0),
    m_colTri(Vector3D::Zero, Vector3D::Zero, Vector3D::Zero),
    m_iColTri(-1)
{
}

SphereCollisionTest::SphereCollisionTest()
  : d(new Private)
{
}

SphereCollisionTest::~SphereCollisionTest()
{
  delete d;
}

const float *SphereCollisionTest::sphereCenter() const
{
  return d->m_sphereCenter.constData();
}

void SphereCollisionTest::setSphereCenter(float x, float y, float z)
{
  d->m_sphereCenter.x = x;
  d->m_sphereCenter.y = y;
  d->m_sphereCenter.z = z;
}

float SphereCollisionTest::sphereRadius() const
{
  return d->m_sphereRadius;
}

void SphereCollisionTest::setSphereRadius(float radius)
{
  d->m_sphereRadius = radius;
}

bool SphereCollisionTest::collides() const
{
  return d->m_iColTri != -1;
}

void SphereCollisionTest::getModelTriangle(float tri[])
{
  d->m_colTri.copyCoords(tri);
}

int SphereCollisionTest::triangleId() const
{
  return d->m_iColTri;
}

const float *SphereCollisionTest::point() const
{
  return d->m_colPoint.constData();
}
