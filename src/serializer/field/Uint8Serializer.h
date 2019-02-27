#pragma once

#include "serializer/Serializer.h"

namespace serializer {
namespace field {

class Uint8Serializer : public Serializer {
 public:
  Uint8Serializer(uint8_t* value);

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

 private:
  const static uint8_t SIZE;
  uint8_t* value;
};
}  // namespace field
}  // namespace serializer
