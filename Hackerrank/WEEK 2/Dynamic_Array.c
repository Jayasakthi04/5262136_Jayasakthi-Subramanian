#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */
int* dynamicArray(int n, int queries_rows, int queries_columns, int** queries, int* result_count) 
{
    int *sizes = (int*)calloc(n, sizeof(int));
    int *caps = (int*)calloc(n, sizeof(int));
    int **arrs = (int**)calloc(n, sizeof(int*));
    
    int *results = NULL;
    int res_size = 0;
    int res_cap = 0;
    
    int lastAnswer = 0;
    
    for (int qi = 0; qi < queries_rows; ++qi) {
        int type = queries[qi][0];
        int x = queries[qi][1];
        int y = queries[qi][2];
        
        int idx = (x ^ lastAnswer) % n;
        
        if (type == 1) {
            if (caps[idx] == 0) {
                caps[idx] = 1;
                arrs[idx] = (int*)malloc(caps[idx] * sizeof(int));
            } else if (sizes[idx] == caps[idx]) {
                caps[idx] *= 2;
                arrs[idx] = (int*)realloc(arrs[idx], caps[idx] * sizeof(int));
            }
            arrs[idx][sizes[idx]++] = y;
        } else if (type == 2) {
            int pos = y % sizes[idx];
            lastAnswer = arrs[idx][pos];

            if (res_size == res_cap) {
                res_cap = res_cap ? res_cap * 2 : 4;
                results = (int*)realloc(results, res_cap * sizeof(int));
            }
            results[res_size++] = lastAnswer;
        }
    }

    for (int i = 0; i < n; ++i) free(arrs[i]);
    free(arrs);
    free(sizes);
    free(caps);

    *result_count = res_size;
    return results;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    int** queries = malloc(q * sizeof(int*));

    for (int i = 0; i < q; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));

        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            int queries_item = parse_int(*(queries_item_temp + j));
            *(*(queries + i) + j) = queries_item;
        }
    }

    int result_count;
    int* result = dynamicArray(n, q, 3, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));
        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");
    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;
        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) data = '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) data = '\0';
        else data[data_length] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}

