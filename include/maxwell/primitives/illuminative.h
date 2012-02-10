#ifndef ILLUMINATIVE_H_
#define ILLUMINATIVE_H_

#include "primitive.h"
#include "../common.h"

//Represents a illuminative scene element
class Illuminative
{
public:
  //Get random point from the surface of the element.
  virtual Vector3 GetRandomPoint() const = 0;

  //Get a value of area of the surface of the element
  //'area = 1' means point element
  virtual int GetArea() const = 0;

  virtual ~Illuminative()
  {}
};

#endif /*ILLUMINATIVE_H_*/
