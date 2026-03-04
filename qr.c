#include "TinyPngOut.h"
#include "qrcodegen.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
  uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
  bool ok = qrcodegen_encodeText(
      "Hello, world!", tempBuffer, qr0, qrcodegen_Ecc_MEDIUM,
      qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
  if (!ok)
    return 0;

  FILE *file = fopen("out.png", "w");
  if (file == NULL) {
    printf("couldnt open file\n");
    exit(-1);
  }
  int size = qrcodegen_getSize(qr0);
  printf("size%d\n", size);
  struct TinyPngOut writer;
  enum TinyPngOut_Status init_status =
      TinyPngOut_init(&writer, size, size, file);
  if (init_status != TINYPNGOUT_OK) {
    printf("couldnt initialize tinyOut write%d\n", init_status);
    exit(-1);
  }
  uint8_t rgb_black[] = {0, 0, 0};
  uint8_t rgb_white[] = {255, 255, 255};

  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      bool color = qrcodegen_getModule(qr0, x, y);
      TinyPngOut_write(&writer, color ? rgb_white : rgb_black, 1);
    }
  }

  return 0;
}
