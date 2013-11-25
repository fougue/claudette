#ifndef FOUGCOLDET_BASE_COLLISION_TEST_H
#define FOUGCOLDET_BASE_COLLISION_TEST_H

#include "global.h"

class FOUGCOLDET_LIB_EXPORT BaseCollisionTest
{
public:
  BaseCollisionTest();
  virtual ~BaseCollisionTest();

  virtual bool collides() const;

  /*! \brief The triangle that collided (belongs to _this_ model)
   *
   *  The result is returned as a pointer being an array of 9 float values :
   *    \li x,y,z of 1st vertex : [0..2]
   *    \li          2nd vertex : [3..5]
   *    \li          3rd vertex : [6..8]
   */
  virtual const float* modelTriangle() const;

  //! The index of the triangle that collided (belongs to _this_ model)
  virtual int triangleId() const;

  //! The detected collision point (array of 3 items containing x,y,z coords)
  virtual const float* point() const;

protected:
  float* mutablePoint();

private:
  friend class CollisionModel3DImpl;
  int m_iColTri;
  float m_colTri[9];
  float m_colPnt[3];
};

#endif // FOUGCOLDET_BASE_COLLISION_TEST_H
