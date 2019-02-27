#include "serializer/field/Uint8Serializer.h"

namespace serializer {
namespace field {

const uint8_t Uint8Serializer::SIZE = sizeof(uint8_t);

Uint8Serializer::Uint8Serializer(uint8_t* value) : value(value) {
}

void Uint8Serializer::serialize(uint8_t* output) {
  memcpy(output, value, SIZE);
}

void Uint8Serializer::deserialize(uint8_t* input) {
  memcpy(value, input, SIZE);
}

uint32_t Uint8Serializer::size() {
  return SIZE;
}

}  // namespace field
}  // namespace serializer
