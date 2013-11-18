#include "ray_collision_test.h"

#include "ray_collision_test_p.h"

RayCollisionTest::Private::Private()
  : m_rayOrigin(0, 0, 0),
    m_rayDirection(0, 0, 1), // Z
    m_raySegMin(0),
    m_raySegMax(3.4e+38f),
    m_raySearch(RayCollisionTest::SearchFirstTriangle),
    m_colTri(Vector3D::Zero, Vector3D::Zero, Vector3D::Zero),
    m_iColTri(-1)
{
}

RayCollisionTest::RayCollisionTest()
  : d(new Private)
{
}

RayCollisionTest::~RayCollisionTest()
{
  delete d;
}

const float *RayCollisionTest::rayOrigin() const
{
  return d->m_rayOrigin.constData();
}

void RayCollisionTest::setRayOrigin(float x, float y, float z)
{
  d->m_rayOrigin.x = x;
  d->m_rayOrigin.y = y;
  d->m_rayOrigin.z = z;
}

const float *RayCollisionTest::rayDirection() const
{
  return d->m_rayDirection.constData();
}

void RayCollisionTest::setRayDirection(float x, float y, float z)
{
  d->m_rayDirection.x = x;
  d->m_rayDirection.y = y;
  d->m_rayDirection.z = z;
}

float RayCollisionTest::raySegmentMin() const
{
  return d->m_raySegMin;
}

float RayCollisionTest::raySegmentMax() const
{
  return d->m_raySegMax;
}

void RayCollisionTest::setRaySegmentBounds(float min, float max)
{
  d->m_raySegMin = min;
  d->m_raySegMax = max;
}

RayCollisionTest::Search RayCollisionTest::raySearch() const
{
  return d->m_raySearch;
}

void RayCollisionTest::setRaySearch(RayCollisionTest::Search srh)
{
  d->m_raySearch = srh;
}

bool RayCollisionTest::collides() const
{
  return d->m_iColTri != -1;
}

void RayCollisionTest::getModelTriangle(float tri[])
{
  d->m_colTri.copyCoords(tri);
}

int RayCollisionTest::triangleId() const
{
  return d->m_iColTri;
}

const float *RayCollisionTest::point() const
{
  return d->m_colPoint.constData();
}
