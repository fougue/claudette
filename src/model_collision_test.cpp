#include "model_collision_test.h"

#include "mytritri.h"

#include <algorithm>

ModelCollisionTest::ModelCollisionTest()
  : m_otherModel(NULL),
    m_otherModelTransform(NULL),
    m_accuracyDepth(-1),
    m_iOtherColTri(-1),
    m_colPointIsDirty(false),
    m_maxProcessingTimedOut(false)
{
  std::fill(m_otherColTri, m_otherColTri + 9, float(0));
}

ModelCollisionTest::~ModelCollisionTest()
{
}

const CollisionModel3D *ModelCollisionTest::otherModel() const
{
  return m_otherModel;
}

void ModelCollisionTest::setOtherModel(const CollisionModel3D *other)
{
  m_otherModel = other;
}

const float *ModelCollisionTest::otherModelTransform() const
{
  return m_otherModelTransform;
}

void ModelCollisionTest::setOtherModelTransform(const float trsf[])
{
  m_otherModelTransform = trsf;
}

int ModelCollisionTest::accuracyDepth() const
{
  return m_accuracyDepth;
}

void ModelCollisionTest::setAccuracyDepth(int depth)
{
  m_accuracyDepth = depth;
}

bool ModelCollisionTest::collides() const
{
  return BaseCollisionTest::collides() && m_iOtherColTri != -1;
}

bool ModelCollisionTest::maxProcessingTimedOut() const
{
  return m_maxProcessingTimedOut;
}

const float *ModelCollisionTest::otherModelTriangle() const
{
  return m_otherColTri;
}

int ModelCollisionTest::otherTriangleId() const
{
  return m_iOtherColTri;
}

const float *ModelCollisionTest::point() const
{
  if (this->collides()) {
    if (m_colPointIsDirty) {
      ModelCollisionTest* mutableThis = const_cast<ModelCollisionTest*>(this);
      mutableThis->computeCollisionPoint();
    }
  }
  return BaseCollisionTest::point();
}

void ModelCollisionTest::computeCollisionPoint()
{
  const float* colTriPtr = this->modelTriangle();
  const Triangle colTri(Vector3D::asConstRef(colTriPtr),
                        Vector3D::asConstRef(colTriPtr + 3),
                        Vector3D::asConstRef(colTriPtr + 6));
  const Triangle otherTri(Vector3D::asConstRef(m_otherColTri),
                          Vector3D::asConstRef(m_otherColTri + 3),
                          Vector3D::asConstRef(m_otherColTri + 6));
  Vector3D::asRef(this->mutablePoint()) = my_tri_tri_intersect(colTri, otherTri);
  m_colPointIsDirty = false;
}
