#include "serializer/field/Uint32Serializer.h"

namespace serializer {
namespace field {

const uint8_t Uint32Serializer::SIZE = sizeof(uint32_t);

Uint32Serializer::Uint32Serializer(uint32_t* value) : value(value) {
}

void Uint32Serializer::serialize(uint8_t* output) {
  memcpy(output, value, SIZE);
}

void Uint32Serializer::deserialize(uint8_t* input) {
  memcpy(value, input, SIZE);
}

uint32_t Uint32Serializer::size() {
  return SIZE;
}

}  // namespace field
}  // namespace serializer
