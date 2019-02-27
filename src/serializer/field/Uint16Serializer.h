#pragma once

#include "serializer/Serializer.h"

namespace serializer {
namespace field {

class Uint16Serializer : public Serializer {
 public:
  Uint16Serializer(uint16_t* value);

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

 private:
  const static uint8_t SIZE;
  uint16_t* value;
};
}  // namespace field
}  // namespace serializer
