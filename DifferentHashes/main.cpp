#include <string.h>
#include <ctype.h>

#include "../HashTable/hashtable.h"
#include "../HashTable/dictionary.cpp"

const size_t hashtable_size  = 4079;
const char*  dictionary_file = "../dictionary.txt";

const size_t f_mask = 0xFFFFFFFFFFFFFFFF;
const size_t crc64_const = 0xC96C5795D7870F42;
const int byte_size = 8;

#define ROR(a) ((a >> 1 ) | (a << (sizeof(a) * byte_size - 1)))
#define ROL(a) ((a << 1 ) | (a >> (sizeof(a) * byte_size - 1)))

size_t Hash1(char* const* elem)
{
    assert(elem);
    return 1;
}

size_t Hash2(char* const* elem)
{
    assert(elem);
    return strlen(*elem);
}

size_t Hash3(char* const* elem)
{
    assert(elem);
    return (*elem)[0];
}

size_t Hash4(char* const* elem)
{
    assert(elem);

    int i = 0;
    size_t hash = 0;
    while ((*elem)[i] != '\0')
    {
        hash += (*elem)[i++];
    }

    return hash;
}

size_t Hash5(char* const* elem)
{
    assert(elem);

    size_t hash = 0;
    int i = 0;

    while ((*elem)[i] != '\0')
    {
        hash = ROL(hash) xor (*elem)[i++];
    }

    return hash;
}

size_t Hash6(char* const* elem)
{
    assert(elem);

    size_t hash = f_mask;
    int i = 0;

    while ((*elem)[i] != '\0')
    {
        char symbol = (*elem)[i];
        for (int j = 0; j < byte_size; ++j)
        {
            size_t bit = (symbol xor hash) & 1;
            hash   >>= 1;
            symbol >>= 1;

            if (bit)
            {
                hash = hash xor crc64_const;
            }
        }

        i++;
    }

    return ~hash;
}

int Cmp(char* const* elem1, char* const* elem2)
{
    return strcasecmp(*elem1, *elem2);
}

void TestDifferentHashes()
{
    Dictionary dict = {};
    GetDictionary(&dict, dictionary_file);

    // HashTable table1 = {};
    // HashTable table2 = {};
    // HashTable table3 = {};
    // HashTable table4 = {};
    // HashTable table5 = {};
    HashTable table6 = {};

    // Construct(&table1, hashtable_size, Hash1, Cmp);
    // Construct(&table2, hashtable_size, Hash2, Cmp);
    // Construct(&table3, hashtable_size, Hash3, Cmp);
    // Construct(&table4, hashtable_size, Hash4, Cmp);
    // Construct(&table5, hashtable_size, Hash5, Cmp);
    Construct(&table6, hashtable_size, Hash6, Cmp);

    for (size_t i = 0; i < GetSize(&dict); ++i)
    {
        // Insert(&table1, dict.english[i], dict.russian[i]);
        // Insert(&table2, dict.english[i], dict.russian[i]);
        // Insert(&table3, dict.english[i], dict.russian[i]);
        // Insert(&table4, dict.english[i], dict.russian[i]);
        // Insert(&table5, dict.english[i], dict.russian[i]);
        Insert(&table6, dict.english[i], dict.russian[i]);
    }

    FILE* file = fopen("sizes.csv", "w");

    // PrintBucketSizes(&table1, file);
    // PrintBucketSizes(&table2, file);
    // PrintBucketSizes(&table3, file);
    // PrintBucketSizes(&table4, file);
    // PrintBucketSizes(&table5, file);
    PrintBucketSizes(&table6, file);

    fclose(file);
}

int main()
{
    TestDifferentHashes();
    return 0;
}
