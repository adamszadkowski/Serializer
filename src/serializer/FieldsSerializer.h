#pragma once

#include "Arduino.h"
#include "IPAddress.h"
#include "serializer/Serializer.h"

namespace serializer {

class Node;

class FieldsSerializer : public Serializer {
 public:
  FieldsSerializer(uint32_t version, uint32_t maxSize);
  FieldsSerializer(const FieldsSerializer&) = delete;
  ~FieldsSerializer() override;

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

  FieldsSerializer& operator<<(uint8_t* value);
  FieldsSerializer& operator<<(uint16_t* value);
  FieldsSerializer& operator<<(uint32_t* value);
  FieldsSerializer& operator<<(String* string);
  FieldsSerializer& operator<<(IPAddress* ipAddress);

  void registerFieldSerializer(Serializer* serializer);

 private:
  uint32_t payloadSize();
  bool isCRC32Valid(uint32_t crc, uint32_t size, uint8_t* input);

 private:
  const static uint32_t OVERHEAD_SIZE;
  uint32_t version;
  uint32_t maxSize;
  Node* elements;
};

}  // namespace serializer
