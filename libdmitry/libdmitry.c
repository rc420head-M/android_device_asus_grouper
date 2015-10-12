#define LOG_TAG "libdmitry"
#include <stdio.h>
#include <stdlib.h>
#include <utils/Log.h>

// this used to exist in OpenSLL, but does not in BoringSSL - for some reason GPS library uses it anyways
void *CRYPTO_malloc(uint32_t sz, const char *file, uint32_t line);

/*
 * FUNCTION: CRYPTO_malloc(uint32_t sz, const char *file, uint32_t line)
 * USE:      INTERPOSE: Allocate memory
 * NOTES:    In OpenSSL, this just allocates memory and optionally tracks it.
 *           Why grouper/manta's GPS library chose to use it is a mystery, but to make
 *           it happy we must provide it, so we do, backing the allocation with
 *           a calloc()-ed memory chunk.
 */
void *CRYPTO_malloc(uint32_t sz, const char *file, uint32_t line)
{
    (void)file;
    (void)line;
    return calloc(sz, 1);
}
