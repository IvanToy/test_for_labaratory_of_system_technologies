#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define MAX_ARRAY_SIZE 1000
#define BUFFER_SIZE 10000

typedef struct
{
    int number;
    int count;
} number_count_t;

bool is_unique(int num, int *unique_nums, int length);
number_count_t *number_count(int *nums_array, int length, int *unique_count);
char *serialize(number_count_t *nums_count, int count);
int *deserialize(char *serialized);
void run_tests();

int main()
{
    run_tests();
    return 0;
}

bool is_unique(int num, int *unique_nums, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (unique_nums[i] == num)
        {
            return false;
        }
    }
    return true;
}

number_count_t *number_count(int *nums_array, int length, int *unique_count)
{
    int count = 0;
    int unique_nums[length];

    for (int i = 0; i < length; i++)
    {
        if (is_unique(nums_array[i], unique_nums, count))
        {
            unique_nums[count++] = nums_array[i];
        }
    }

    number_count_t *nums_count = (number_count_t *)malloc(sizeof(number_count_t) * count);
    if (nums_count == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    for (int i = 0; i < count; i++)
    {
        nums_count[i].number = unique_nums[i];
        nums_count[i].count = 0;
    }

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (nums_count[j].number == nums_array[i])
            {
                nums_count[j].count++;
                break;
            }
        }
    }

    *unique_count = count;
    return nums_count;
}

char *serialize(number_count_t *nums_count, int count)
{
    char *serialized = (char *)malloc(BUFFER_SIZE);
    if (serialized == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }
    serialized[0] = '\0';

    for (int i = 0; i < count; i++)
    {
        char temp[20];
        if (nums_count[i].count <= 26)
        {
            snprintf(temp, sizeof(temp), "%d%c", nums_count[i].number, (char)(64 + nums_count[i].count));
        }
        else
        {
            snprintf(temp, sizeof(temp), "%d%d", nums_count[i].number, nums_count[i].count);
        }
        strcat(serialized, temp);
    }

    return serialized;
}

int *deserialize(char *serialized)
{
    int *deserialized = malloc(sizeof(int) * MAX_ARRAY_SIZE);
    if (deserialized == NULL)
    {
        printf("Failed to allocate memory\n");
        return NULL;
    }

    int index = 0;
    int num = 0;
    int i = 0;
    while (i < strlen(serialized))
    {
        if (isdigit(serialized[i]))
        {

            num = 0;
            while (i < strlen(serialized) && isdigit(serialized[i]))
            {
                num = num * 10 + (serialized[i] - '0');
                i++;
            }

            if (isalpha(serialized[i]))
            {
                int count = serialized[i] - 'A' + 1;
                for (int j = 0; j < count; j++)
                {
                    deserialized[index++] = num;
                }
                i++;
            }
            else
            {

                int count = 0;
                while (i < strlen(serialized) && isdigit(serialized[i]))
                {
                    count = count * 10 + (serialized[i] - '0');
                    i++;
                }
                for (int j = 0; j < count; j++)
                {
                    deserialized[index++] = num;
                }
            }
        }
    }

    return deserialized;
}

void run_test_case(int *array, int length)
{
    int unique_count;
    number_count_t *nums_count = number_count(array, length, &unique_count);
    if (nums_count == NULL)
    {
        return;
    }
    char *serialized = serialize(nums_count, unique_count);
    if (serialized != NULL)
    {
        printf("Serialized: %s\n", serialized);
    }
    int *deserialized = deserialize(serialized);

    if (deserialized != NULL)
    {
        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        {
            if (deserialized[i] != 0)
            {
                printf("%d\n", deserialized[i]);
            }
            else
            {
                break;
            }
        }
    }
    free(nums_count);
    free(serialized);
    free(deserialized);
}

void run_tests()
{
    srand(time(NULL));

    // Simple short examples
    printf("Simple short examples\n");
    int array1[] = {1, 1, 1, 2, 2, 3, 3, 3, 1};
    run_test_case(array1, sizeof(array1) / sizeof(array1[0]));

    // Random examples with 50, 100, 500, and 1000 numbers
    printf("Random examples with 50 numbers\n");
    int array2[50];
    for (int i = 0; i < 50; i++)
        array2[i] = rand() % 100;
    run_test_case(array2, 50);

    printf("Random examples with 100 numbers\n");
    int array3[100];
    for (int i = 0; i < 100; i++)
        array3[i] = rand() % 100;
    run_test_case(array3, 100);

    printf("Random examples with 500 numbers\n");
    int array4[500];
    for (int i = 0; i < 500; i++)
        array4[i] = rand() % 100;
    run_test_case(array4, 500);

    printf("Random examples with 1000 numbers\n");
    int array5[1000];
    for (int i = 0; i < 1000; i++)
        array5[i] = rand() % 100;
    run_test_case(array5, 1000);

    // Edge cases
    printf("Edge case: All numbers being single digits\n");
    int array6[100];
    for (int i = 0; i < 100; i++)
        array6[i] = rand() % 10;
    run_test_case(array6, 100);

    printf("Edge case: All numbers being two digits\n");
    int array7[100];
    for (int i = 0; i < 100; i++)
        array7[i] = 10 + rand() % 90;
    run_test_case(array7, 100);

    printf("Edge case: All numbers being three digits\n");
    int array8[100];
    for (int i = 0; i < 100; i++)
        array8[i] = 100 + rand() % 900;
    run_test_case(array8, 100);

    printf("Edge case: Each number appearing three times, totaling 900 numbers\n");
    int array9[900];
    for (int i = 0; i < 300; i++)
    {
        array9[i * 3] = i;
        array9[i * 3 + 1] = i;
        array9[i * 3 + 2] = i;
    }
    run_test_case(array9, 900);
}
