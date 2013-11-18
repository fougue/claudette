#include "model_collision_test.h"

#include "model_collision_test_p.h"
#include "mytritri.h"

ModelCollisionTest::Private::Private()
  : m_otherModel(NULL),
    m_otherModelTransform(NULL),
    m_accuracyDepth(-1),
    m_colTri1(Vector3D::Zero, Vector3D::Zero, Vector3D::Zero),
    m_colTri2(Vector3D::Zero, Vector3D::Zero, Vector3D::Zero),
    m_iColTri1(-1),
    m_iColTri2(-1),
    m_colPointIsDirty(false)
{
}

ModelCollisionTest::ModelCollisionTest()
  : d(new Private)
{
}

ModelCollisionTest::~ModelCollisionTest()
{
  delete d;
}

const CollisionModel3D *ModelCollisionTest::otherModel() const
{
  return d->m_otherModel;
}

void ModelCollisionTest::setOtherModel(const CollisionModel3D *other)
{
  d->m_otherModel = other;
}

const float *ModelCollisionTest::otherModelTransform() const
{
  return d->m_otherModelTransform;
}

void ModelCollisionTest::setOtherModelTransform(const float trsf[])
{
  d->m_otherModelTransform = trsf;
}

int ModelCollisionTest::accuracyDepth() const
{
  return d->m_accuracyDepth;
}

void ModelCollisionTest::setAccuracyDepth(int depth)
{
  d->m_accuracyDepth = depth;
}

bool ModelCollisionTest::collides() const
{
  return d->m_iColTri1 == -1 || d->m_iColTri2 == -1;
}

void ModelCollisionTest::getModelTriangles(float t1[], float t2[])
{
  d->m_colTri1.copyCoords(t1);
  d->m_colTri2.copyCoords(t2);
}

std::pair<int, int> ModelCollisionTest::triangleIdPair() const
{
  return std::make_pair(d->m_iColTri1, d->m_iColTri2);
}

const float *ModelCollisionTest::point() const
{
  if (this->collides()) {
    if (d->m_colPointIsDirty) {
      d->m_colPoint = my_tri_tri_intersect(d->m_colTri1, d->m_colTri2);
      d->m_colPointIsDirty = false;
    }
    return d->m_colPoint.constData();
  }
  return NULL;
}
