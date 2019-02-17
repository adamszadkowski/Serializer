#include "serializer/field/StringSerializer.h"

namespace serializer {
namespace field {

const uint8_t StringSerializer::SIZE_UNIT_BYTES = sizeof(SizeUnit);

StringSerializer::StringSerializer(String* string) : string(string) {
}

void StringSerializer::serialize(uint8_t* output) {
  SizeUnit size = string->length();

  memcpy(output, &size, SIZE_UNIT_BYTES);
  output += SIZE_UNIT_BYTES;

  for (SizeUnit i = 0; i < size; i++) {
    output[i] = (*string)[i];
  }
}

void StringSerializer::deserialize(uint8_t* input) {
  SizeUnit size;

  memcpy(&size, input, SIZE_UNIT_BYTES);
  input += SIZE_UNIT_BYTES;

  *string = "";
  for (SizeUnit i = 0; i < size; i++) {
    *string += static_cast<char>(input[i]);
  }
}

uint32_t StringSerializer::size() {
  return SIZE_UNIT_BYTES + string->length();
}

}  // namespace field
}  // namespace serializer
