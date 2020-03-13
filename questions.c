#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gmodule.h>

//Strictily higher
int static inline max_int(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

/*
Find the most common integer in an array
The time complexity has to be linear, because it is mandatory
to check for every number. Space complexity is linear in this case, too.
I used a hash table which has to hold in memory the frecuency for each
integer.
*/
int find_most_common_integer(int* arr, unsigned n)
{
    if (!n)
    {
        fprintf(stderr, "Array cannot be empty!\n");
        return -1;
    }
    int max_val = 1;
    int* max_key = arr;
    GHashTable* hash_table = g_hash_table_new(g_int_hash, g_int_equal);
    for (unsigned i = 0; i < n; i++)
    {
        int* value = g_hash_table_lookup(hash_table, &arr[i]);
        if (value == NULL)
        {
            value = malloc(sizeof(int));
            *value = 1;
            g_hash_table_insert(hash_table, &arr[i], value);
        }
        else
        {
            int val = *value;
            val++;
            *value = val;
            if (val > max_val)
            {
                max_val = val;
                max_key = &arr[i];
            }
        }
    }
    g_hash_table_destroy(hash_table);
    return *max_key;
}



int main()
{
    srand(time(NULL));
    unsigned n = 100000;
    int* arr = malloc(sizeof(int) * n);
    for (unsigned i = 0; i < n; i++)
        arr[i] = (rand() % 100) - 10;
    // unsigned n = sizeof(arr) / sizeof(arr[0]);
    // printf("Array : [");
    // for (unsigned i = 0; i < n; i++)
    //     printf("%d, ", arr[i]);
    // printf("\b\b]\n");
    printf("Most common integer : %d\n", find_most_common_integer(arr, n));
    free(arr);
    return 0;
}