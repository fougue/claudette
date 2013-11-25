#ifndef FOUGCOLDET_MODEL_COLLISION_TEST_H
#define FOUGCOLDET_MODEL_COLLISION_TEST_H

#include "base_collision_test.h"

class CollisionModel3D;

/*! \brief Collision test between two meshes
 */
class FOUGCOLDET_LIB_EXPORT ModelCollisionTest : public BaseCollisionTest
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

  //! The triangle that collided (in other model)
  const float* otherModelTriangle() const;

  //! The index of the triangle that collided (belongs to other model)
  int otherTriangleId() const;

  const float* point() const;

private:
  void computeCollisionPoint();

  friend class CollisionModel3DImpl;

  const CollisionModel3D* m_otherModel;
  const float* m_otherModelTransform;
  int m_accuracyDepth;

  float m_otherColTri[9];
  int m_iOtherColTri;

  //! Does the collision point need to be recomputed ?
  bool m_colPointIsDirty;
};

#endif // FOUGCOLDET_MODEL_COLLISION_TEST_H
