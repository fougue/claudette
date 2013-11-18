#ifndef FOUGCOLDET_RAY_COLLISION_TEST_H
#define FOUGCOLDET_RAY_COLLISION_TEST_H

#include "global.h"

class FOUGCOLDET_LIB_EXPORT RayCollisionTest
{
public:
  /** Search option of rayCollision() for the colliding triangle */
  enum Search
  {
    SearchClosestTriangle, /**< Search closest triangle on the ray (will slow
                                the test considerably) */
    SearchFirstTriangle    /**< Search stop on the first triangle that collides with the ray */
  };

  RayCollisionTest();
  ~RayCollisionTest();

  const float* rayOrigin() const;
  void setRayOrigin(float x, float y, float z);

  const float* rayDirection() const;
  void setRayDirection(float x, float y, float z);

  float raySegmentMin() const;
  float raySegmentMax() const;
  /*! The default ray is a standard infinite ray.  However, using segmin and segmax a line segment
   *  along the ray can be defined
   */
  void setRaySegmentBounds(float min = 0.f, float max = 3.4e+38f);

  Search raySearch() const;
  void setRaySearch(Search srh);

  bool collides() const;

  //! The triangle that collided (belongs to _this_ model)
  void getModelTriangle(float tri[9]);
  //void getWorldTriangle(float tri[9]);

  //! The triangles index that collided (belongs to _this_ model)
  int triangleId() const;

  //! The detected collision point
  const float* point() const;

private:
  class Private;
  friend class CollisionModel3DImpl;
  Private* const d;
};

#endif // FOUGCOLDET_RAY_COLLISION_TEST_H
