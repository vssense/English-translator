#pragma once

#include <string.h>
#include <ctype.h>

#include "../HashTable/hashtable.h"

static const size_t hashtable_size  = 4079;
static const char*  dictionary_file = "../dictionary.txt";
static const char*  html_file       = "/tmp/translated.html";

static const size_t f_mask      = 0xFFFFFFFFFFFFFFFF;
static const size_t crc32_const = 0xC96C5795D7870F42;
static const int    byte_size   = 8;

void Translate(FILE* input);
