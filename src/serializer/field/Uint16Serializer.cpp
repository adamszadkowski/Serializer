#include "serializer/field/Uint16Serializer.h"

namespace serializer {
namespace field {

const uint8_t Uint16Serializer::SIZE = sizeof(uint16_t);

Uint16Serializer::Uint16Serializer(uint16_t* value) : value(value) {
}

void Uint16Serializer::serialize(uint8_t* output) {
  memcpy(output, value, SIZE);
}

void Uint16Serializer::deserialize(uint8_t* input) {
  memcpy(value, input, SIZE);
}

uint32_t Uint16Serializer::size() {
  return SIZE;
}

}  // namespace field
}  // namespace serializer
