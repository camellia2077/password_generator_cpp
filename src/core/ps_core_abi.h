#ifndef PS_CORE_ABI_H
#define PS_CORE_ABI_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int ps_generate_password(int length, char* out_buffer, size_t out_buffer_len);

#ifdef __cplusplus
}
#endif

#endif // PS_CORE_ABI_H
