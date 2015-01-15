#include "base_collision_test.h"

#include "math3d.h"

#include <algorithm>

BaseCollisionTest::BaseCollisionTest()
    : m_collides(false),
      m_iColTri(-1)
{
    Vector3D::fillFloatVec(m_colPnt, 0);
    std::fill(m_colTri, m_colTri + 9, float(0));
}

BaseCollisionTest::~BaseCollisionTest()
{
}

bool BaseCollisionTest::collides() const
{
    return m_collides;
}

const float *BaseCollisionTest::modelTriangle() const
{
    return m_colTri;
}

// BaseCollisionTest::void getWorldTriangle(float tri[9]);

int BaseCollisionTest::triangleId() const
{
    return m_iColTri;
}

const float *BaseCollisionTest::point() const
{
    return m_colPnt;
}

float *BaseCollisionTest::mutablePoint()
{
    return m_colPnt;
}
