#include "translator.h"
#include "../HashTable/dictionary.cpp"

size_t Hash(char* const* elem)
{
    assert(elem);

    size_t hash = f_mask;
    int i = 0;

    while ((*elem)[i] != '\0')
    {
        char symbol = tolower((*elem)[i]);
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
    assert(elem1);
    assert(elem2);

    return strcasecmp(*elem1, *elem2);
}

char* GetEndOfWord(char* buffer)
{
    assert(buffer);

    size_t index = 0;

    while (buffer[index] != '\0')
    {
        if (!(isalpha(buffer[index])))
        {
            break;
        }

        index++;
    }

    return buffer + index;
}

void WriteToHTMLFile(char* buffer, FILE* output, HashTable* table)
{
    assert(buffer);
    assert(output);

    while (*buffer != '\0')
    {
        if (!isalpha(*buffer))
        {
            fputc(*buffer, output);
            buffer++;
            continue;
        }

        char* end_of_word = GetEndOfWord(buffer);
        char symbol       = *end_of_word;
        *end_of_word      = '\0';

        char* translated_word = Find(table, buffer);

        if (translated_word == nullptr)
        {
            char* old_end_of_word = end_of_word;
            char  old_symbol      = symbol;

            *end_of_word    = symbol;
            end_of_word     = GetEndOfWord(end_of_word + 1);
            symbol          = *end_of_word;
            *end_of_word    = '\0';
            translated_word = Find(table, buffer);

            if (translated_word == nullptr)
            {
                *end_of_word = symbol;
                symbol       = old_symbol;
                end_of_word  = old_end_of_word;
                *end_of_word = '\0';
            }
        }

        if (translated_word != nullptr)
        {
            fprintf(output, "<span title=\"%s\">%s</span>", translated_word, buffer);
        }
        else
        {
            fprintf(output, "%s", buffer);
        }

        *end_of_word = symbol;
        buffer       = end_of_word;
    }
}

void TranslateToHTML(FILE* input, FILE* output, HashTable* table)
{
    assert(input);
    assert(output);
    assert(table);

    size_t file_size = GetFileSize(input);

    char* buffer = (char*)calloc(file_size, sizeof(char));

    fread(buffer, sizeof(char), file_size, input);

    fprintf(output, "<html>\n<body>\n<pre>\n");

    WriteToHTMLFile(buffer, output, table);

    fprintf(output, "\n</pre>\n</body>\n</html>\n");
}

void Translate(FILE* input)
{
    assert(input);

    Dictionary dict = {};
    GetDictionary(&dict, dictionary_file);
    HashTable table = {};
    Construct(&table, hashtable_size, Hash, Cmp);

    for (size_t i = 0; i < dict.num_words; ++i)
    {
        Insert(&table, dict.english[i], dict.russian[i]);
    }

    FILE* output = fopen(html_file, "w");

    TranslateToHTML(input, output, &table);

    fclose(output);
    DestructDictionary(&dict);
    Destruct(&table);
}