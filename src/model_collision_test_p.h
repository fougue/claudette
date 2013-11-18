#ifndef FOUGCOLDET_MODEL_COLLISION_TEST_P_H
#define FOUGCOLDET_MODEL_COLLISION_TEST_P_H

#include "model_collision_test.h"

#include "box.h"
#include "math3d.h"

class ModelCollisionTest::Private
{
public:
  Private();

  const CollisionModel3D* m_otherModel;
  const float* m_otherModelTransform;
  int m_accuracyDepth;

  /** The triangles that last collided */
  Triangle m_colTri1;
  Triangle m_colTri2;
  /** The indices of the triangles that last collided */
  int m_iColTri1;
  int m_iColTri2;
  /** The collision point of the last test */
  Vector3D m_colPoint;
  bool m_colPointIsDirty;
};

#endif // FOUGCOLDET_MODEL_COLLISION_TEST_P_H
