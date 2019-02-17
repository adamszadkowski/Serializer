#include "serializer/FieldsSerializer.h"

#include <CRC32.h>
#include "serializer/field/IPAddressSerializer.h"
#include "serializer/field/StringSerializer.h"
#include "serializer/field/Uint32Serializer.h"

namespace serializer {

class Node {
 public:
  Node(Node* next, Serializer* serializer) : next(next), serializer(serializer) {
  }
  ~Node() {
    delete serializer;
    if (next != nullptr) delete next;
  }
  Node* next;
  Serializer* serializer;
};

const uint32_t FieldsSerializer::OVERHEAD_SIZE = sizeof(uint32_t) + sizeof(uint32_t);

FieldsSerializer::FieldsSerializer(uint32_t maxSize) : maxSize(maxSize), elements(nullptr) {
  Serial.printf("Constructor has been executed with maxSize: %d, elements pointer: %08x\n", FieldsSerializer::maxSize,
                reinterpret_cast<uint32_t>(elements));
}

FieldsSerializer::~FieldsSerializer() {
  if (elements != nullptr) delete elements;
}

void FieldsSerializer::serialize(uint8_t* output) {
  uint8_t* const crcPointer = output;
  uint8_t* const sizePointer = output + sizeof(uint32_t);
  uint8_t* const payloadPointer = sizePointer + sizeof(uint32_t);

  uint32_t size = payloadSize();
  memcpy(sizePointer, &size, sizeof(size));

  uint8_t* writePointer = payloadPointer;
  for (Node* n = elements; n != nullptr; n = n->next) {
    Serializer* serializer = n->serializer;
    serializer->serialize(writePointer);
    writePointer += serializer->size();
  }

  uint32_t crc = CRC32::calculate(sizePointer, size + sizeof(size));
  memcpy(crcPointer, &crc, sizeof(crc));
}

void FieldsSerializer::deserialize(uint8_t* input) {
  uint8_t* const crcPointer = input;
  uint8_t* const sizePointer = input + sizeof(uint32_t);
  uint8_t* const payloadPointer = sizePointer + sizeof(uint32_t);

  uint32_t crc;
  memcpy(&crc, crcPointer, sizeof(crc));

  uint32_t size;
  memcpy(&size, sizePointer, sizeof(size));

  if (size <= maxSize - OVERHEAD_SIZE) {
    if (isCRC32Valid(crc, size + sizeof(size), sizePointer)) {
      uint8_t* readPointer = payloadPointer;
      for (Node* n = elements; n != nullptr; n = n->next) {
        Serializer* serializer = n->serializer;
        serializer->deserialize(readPointer);
        readPointer += serializer->size();
      }
    }
  }
}

uint32_t FieldsSerializer::size() {
  return OVERHEAD_SIZE + payloadSize();
}

FieldsSerializer& FieldsSerializer::operator<<(uint32_t* value) {
  registerFieldSerializer(new serializer::field::Uint32Serializer(value));
  return *this;
}

FieldsSerializer& FieldsSerializer::operator<<(String* string) {
  registerFieldSerializer(new serializer::field::StringSerializer(string));
  return *this;
}

FieldsSerializer& FieldsSerializer::operator<<(IPAddress* ipAddress) {
  registerFieldSerializer(new serializer::field::IPAddressSerializer(ipAddress));
  return *this;
}

void FieldsSerializer::registerFieldSerializer(Serializer* serializer) {
  elements = new Node(elements, serializer);
}

uint32_t FieldsSerializer::payloadSize() {
  uint32_t size = 0;
  for (Node* n = elements; n != nullptr; n = n->next) {
    size += n->serializer->size();
  }
  return size;
}

bool FieldsSerializer::isCRC32Valid(uint32_t crc, uint32_t size, uint8_t* input) {
  return CRC32::calculate(input, size) == crc;
}

}  // namespace serializer
