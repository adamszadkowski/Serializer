#pragma once

#include "IPAddress.h"
#include "serializer/Serializer.h"

namespace serializer {
namespace field {

class IPAddressSerializer : public Serializer {
 public:
  IPAddressSerializer(IPAddress* ipAddress);

  void serialize(uint8_t* output) override;
  void deserialize(uint8_t* input) override;
  uint32_t size() override;

 private:
  const static uint8_t SIZE;
  IPAddress* ipAddress;
};

}  // namespace field
}  // namespace serializer
