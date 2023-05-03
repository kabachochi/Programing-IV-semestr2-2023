#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

uint32_t generate_number();

size_t encode_varint(uint32_t value, uint8_t *buf);

uint32_t decode_varint(const uint8_t** bufp);

