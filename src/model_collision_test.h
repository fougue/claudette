#ifndef FOUGCOLDET_MODEL_COLLISION_TEST_H
#define FOUGCOLDET_MODEL_COLLISION_TEST_H

#include "global.h"

#include <utility>

class CollisionModel3D;

class FOUGCOLDET_LIB_EXPORT ModelCollisionTest
{
public:
  ModelCollisionTest();
  ~ModelCollisionTest();

  const CollisionModel3D* otherModel() const;
  void setOtherModel(const CollisionModel3D* other);

  /*! \brief Allows overriding the other model's transform, by supplying an alternative one.
   *
   *  This can be useful when testing a model against itself with different orientations.
   */
  const float* otherModelTransform() const;
  void setOtherModelTransform(const float trsf[16]);

  int accuracyDepth() const;
  void setAccuracyDepth(int depth);

  bool collides() const;

  /*! The pair of triangles that collided (t1 is this model's triangle and t2 is the other one)
   */
  void getModelTriangles(float t1[9], float t2[9]);

  /*! \brief The pair of triangles indices that collided
   *
   * First index belongs to the model where CollisionModel3D::modelCollision() was called.
   * Second index belongs to otherModel()
   */
  std::pair<int, int> triangleIdPair() const;

  /*! The detected collision point
   */
  const float* point() const;

private:
  class Private;
  friend class CollisionModel3DImpl;
  Private* const d;
};

#endif // FOUGCOLDET_MODEL_COLLISION_TEST_H
