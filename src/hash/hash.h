#ifndef _H_HASH
#define _H_HASH

#include <stdlib.h>
#include <stdint.h>

// Type hashage
typedef uint64_t hash_t;
#define HASH_START 5381

hash_t hash(hash_t h_val, char c);
hash_t str_hash(const char* s);

#endif // _H_HASH
