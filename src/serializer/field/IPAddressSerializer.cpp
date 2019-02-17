#include "serializer/field/IPAddressSerializer.h"

namespace serializer {
namespace field {

const uint8_t IPAddressSerializer::SIZE = sizeof(uint32_t);

IPAddressSerializer::IPAddressSerializer(IPAddress* ipAddress) : ipAddress(ipAddress) {
}

void IPAddressSerializer::serialize(uint8_t* output) {
  uint32_t address = *ipAddress;
  memcpy(output, &address, SIZE);
}

void IPAddressSerializer::deserialize(uint8_t* input) {
  uint32_t address;
  memcpy(&address, input, SIZE);
  *ipAddress = address;
}

uint32_t IPAddressSerializer::size() {
  return SIZE;
}

}  // namespace field
}  // namespace serializer
