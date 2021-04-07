#include "translator.h"
#include <time.h>
#include <immintrin.h>

const int system_buffer_size = 32;

int main(const int argc, const char* argv[])
{
    clock_t start = clock();
    if (argc - 1 == 0)
    {
        printf("Error: no input file\n");
        return 0;
    }

    FILE* input = fopen(argv[1], "r");

    if (input == nullptr)
    {
        printf("Can't open %s file\n", argv[1]);
        return 0;
    }

    Translate(input);

    fclose(input);

    printf("%ld\n", clock() - start);
    return 0;

    char system_str[system_buffer_size] = "";
    sprintf(system_str, "chromium %s", html_file); 
    system(system_str);

    return 0;
}
