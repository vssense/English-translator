#include <string.h>
#include "hashtable.h"

const size_t hashtable_size = 1077;
const char* dictionary_file = "../dictionary.txt";

#include "dictionary.cpp"

size_t Hash(char* const* elem)
{
    return (*elem)[0]; 
}

int Cmp(char* const* elem1, char* const* elem2)
{
    return strcmpi(*elem1, *elem2);
}

int main()
{
    HashTable table = {};
    Construct(&table, 10, Hash, Cmp);

    Dictionary dict = {};
    GetDictionary(&dict, dictionary_file);

    for (size_t i = 0; i < dict.num_words; ++i)
    {
        printf("%p[%p]\n", dict.english[i], dict.russian[i]);
        printf("%s[%s]\n", dict.english[i], dict.russian[i]);
        Insert(&table, dict.english[i], dict.russian[i]);
    }

    char input[20] = "";

    while (true)
    {
        scanf("%s", input);
        printf("%s\n", Find(&table, input));
    }


    Destruct(&table);
    DestructDictionary(&dict);
    return 0;
}
