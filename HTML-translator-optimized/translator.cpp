#include "translator.h"
#include "src/dictionary.cpp"

size_t Hash(char* const* elem)
{
    __asm__
    (
            "pushq %r12\n"
            "movq $0x00, %rax\n"
            "movq (%rdi), %rdi\n"
            "xor %r12, %r12\n"
        "cycle:\n"
            "movb (%rdi), %r12b\n"
            "test %r12b, %r12b\n"
            "jz end_cycle\n"
            "crc32 %r12b, %rax\n"
            "inc %rdi\n"
            "jmp cycle\n"
        "end_cycle:\n"
            "popq %r12\n"
            "popq %rbp\n"
            "ret\n"
    );
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

    while (*buffer != '\0')
    {
        if (!(isalpha(*buffer)) && *buffer != '-')
        {
            break;
        }

        buffer++;
    }

    return buffer;
}

void PutHTMLChar(char symbol, FILE* output)
{
    assert(output);

    if (symbol == '\n')
    {
        fprintf(output, "</p>\n</p>");
    }
    else
    {
        fputc(symbol, output);
    }
}

void WriteToHTMLFile(char* buffer, FILE* output, HashTable* table)
{
    assert(buffer);
    assert(output);

    while (*buffer != '\0')
    {
        if (!isalpha(*buffer))
        {
            PutHTMLChar(*buffer, output);
            buffer++;
            continue;
        }

        char* end_of_word = GetEndOfWord(buffer);
        char symbol       = *end_of_word;
        *end_of_word      = '\0';


        char* translated_word = Find(table, buffer);
        for (int i = 0; i < 100; ++i)
        {
            Find(table, buffer);
        }

        if (translated_word != nullptr)
        {
            fprintf(output, "<span title=\"%s\">%s</span>\n", translated_word, buffer);
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

    fprintf(output, "<html>\n<body>\n<h1>Translator</h1>\n<p>");

    WriteToHTMLFile(buffer, output, table);

    fprintf(output, "\n</p>\n</body>\n</html>\n");
}

void Translate(FILE* input)
{
    assert(input);

    HashTable table = {};
    Construct(&table, hashtable_size, Hash, Cmp);

    FillHashTable(&table, dictionary_file);

    FILE* output = fopen(html_file, "w");

    TranslateToHTML(input, output, &table);

    fclose(output);
    DestructWithBuffer(&table);
}
