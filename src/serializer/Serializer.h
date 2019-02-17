#pragma once

#include "Arduino.h"

namespace serializer {

class Serializer {
 public:
  virtual ~Serializer() {
  }

  virtual void serialize(uint8_t* output) = 0;
  virtual void deserialize(uint8_t* input) = 0;
  virtual uint32_t size() = 0;
};

}  // namespace serializer
