struct Dictionary
{
    char*  buffer  = nullptr;
    char** english = nullptr;
    char** russian = nullptr;

    size_t length = 0;
    size_t num_words = 0;
};

size_t GetFileSize(FILE* file)
{
    assert(file);

    fseek(file, 0, SEEK_END);
    size_t pos = ftell(file);
    fseek(file, 0, SEEK_SET);

    return pos;
}

size_t GetSize(Dictionary* dict)
{
    assert(dict);

    return dict->num_words;
}

size_t CalculateNumWords(Dictionary* dict)
{
    assert(dict);

    size_t num_words = 0;
    size_t offset = 0;

    for (size_t i = 0; i < dict->length; ++i)
    {
        if (dict->buffer[i] != '\r')
        {
            dict->buffer[offset++] = dict->buffer[i];
        }

        if (dict->buffer[i] == '\n')
        {
            num_words++;
        }
    }

    dict->buffer[offset] = '\0';
    dict->length = offset;

    return num_words;
}

void ReadWords(Dictionary* dict)
{
    assert(dict);

    char* cur_symbol = dict->buffer;
    
    for (size_t i = 0; i < dict->num_words && *cur_symbol != '\0'; ++i)
    {
        dict->english[i] = cur_symbol;
        cur_symbol  = strchr(cur_symbol, ':');
        *cur_symbol = '\0';
        cur_symbol++;

        dict->russian[i] = cur_symbol;
        cur_symbol = strchr(cur_symbol, '\n');

        *cur_symbol = '\0';
        cur_symbol++;
    }
}

void GetBuffer(Dictionary* dict, FILE* file)
{
    assert(dict);
    assert(file);

    dict->length = GetFileSize(file);

    dict->buffer = (char*)calloc(dict->length, sizeof(char));
    fread(dict->buffer, sizeof(char), dict->length, file);

    dict->num_words = CalculateNumWords(dict);

    dict->russian = (char**)calloc(dict->num_words, sizeof(char*));
    dict->english = (char**)calloc(dict->num_words, sizeof(char*));

    ReadWords(dict);
}

void GetDictionary(Dictionary* dict, const char* file)
{
    assert(dict);
    assert(file);

    FILE* input = fopen(file, "r");
    if (input == nullptr)
    {
        printf("Can't open file %s\n", file);
        return;
    }

    GetBuffer(dict, input);
}

void DestructDictionary(Dictionary* dict)
{
    assert(dict);
    assert(dict->buffer);
    assert(dict->english);
    assert(dict->russian);

    free(dict->buffer);
    free(dict->english);
    free(dict->russian);
}