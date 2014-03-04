#include "hash.h"

hash_t hash(hash_t h_val, char c) {
    return (((h_val << 5) + h_val) + c); // hash * 33 + c
}

hash_t str_hash(const char* s) {
    hash_t h = HASH_START;

    while(*s)
        h = hash(h, *(s++));

    return h;
}
