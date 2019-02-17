#pragma once

#include "serializer/Serializer.h"

namespace serializer {
namespace field {

class Uint32Serializer : public Serializer {
 public:
  Uint32Serializer(uint32_t* value);

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

 private:
  const static uint8_t SIZE;
  uint32_t* value;
};
}  // namespace field
}  // namespace serializer
