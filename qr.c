#include "qrcodegen.h"
#include <stdbool.h>
#include <stdint.h>

int main() {
  uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
  uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
  bool ok = qrcodegen_encodeText(
      "Hello, world!", tempBuffer, qr0, qrcodegen_Ecc_MEDIUM,
      qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
  if (!ok)
    return 0;

  int size = qrcodegen_getSize(qr0);
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      //(... paint qrcodegen_getModule(qr0, x, y)...)
    }
  }

  // Binary data
  uint8_t dataAndTemp[qrcodegen_BUFFER_LEN_FOR_VERSION(7)] = {0xE3, 0x81, 0x82};
  uint8_t qr1[qrcodegen_BUFFER_LEN_FOR_VERSION(7)];
  ok = qrcodegen_encodeBinary(dataAndTemp, 3, qr1, qrcodegen_Ecc_HIGH, 2, 7,
                              qrcodegen_Mask_4, false);
  return 0;
}
