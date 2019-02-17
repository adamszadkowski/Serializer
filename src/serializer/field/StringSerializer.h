#pragma once

#include "serializer/Serializer.h"

namespace serializer {
namespace field {

class StringSerializer : public Serializer {
 public:
  typedef uint8_t SizeUnit;
  StringSerializer(String* string);

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

 private:
  const static uint8_t SIZE_UNIT_BYTES;
  String* string;
};

}  // namespace field
}  // namespace serializer
