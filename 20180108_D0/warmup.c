#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

size_t searchPos(int array[], size_t size, int n)
{
  for (size_t i = 0; i < size; i++)
  {
    if (array[i] == n)
    {
      return i;
    }
  }
  return -1;
}

size_t* twoSum(int *nums, size_t size, int target)
{
  size_t* res = malloc(sizeof(size_t) * 2);
  if (size >= 2)
  {
    for (size_t i = 0; i < size; i++)
    {
      if (nums[i] < target)
      {
        res[0] = i;
        size_t pos = searchPos(nums, size, target - nums[i]);
        if (pos != (size_t)-1)
        {
          res[1] = pos;
          return res;
        }
      }
    }
  }
  res[0] = 0;
  res[1] = 0; 
  return res;
}

int* generateSortedArray(size_t size)
{
    int* res = malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (int)i;
    }
    return res;
}

int* generateRandomArray(size_t size, int max)
{
    int* res = malloc(sizeof(int) * size);
   srand(time(NULL));
    for (size_t i = 0; i < size; i++)
    {
        res[i] = (rand() % max);
    }
    return res;
}

void printIntArray(int* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (i == size-1) {
            printf(" %d \n ", array[i]);
        }
        else {
            printf(" %d |", array[i]);
        }
    }
}

void printSizeTArray(size_t* array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (i == size-1) {
            printf(" %zu \n ", array[i]);
        }
        else {
            printf(" %zu |", array[i]);
        }
    }
}

int isInString(char* string, size_t begin, size_t end, char c)
{
    int res = 0;
    for (size_t i = begin; i < end; i++)
    {
        if (string[i] == c) 
        {
            res = 1;
        }
    }
    return res;
}

char* longestSubstring(char* string, size_t size)
{
    size_t* res = malloc(sizeof(size_t) * 2);
    size_t* curr = malloc(sizeof(size_t) * 2);
    for (size_t i = 0; i < 2; i++)
    {
        res[i] = 0;
        curr[i] = 0;
    }
    for (size_t i = 0; i < size; i++)
    {
        if (isInString(string, curr[0], curr[1], string[i]) == 0)
        {
            curr[1] = curr[1] + 1;
        }
        else 
        {
            if (curr[1] - curr[0] > res[1] - res[0])
            {
                res[0] = curr[0];
                res[1] = curr[1];
                curr[0] = curr[1] + 1;
                curr[1] = curr[1] + 1;
            }
        }
    }
    printf("%zu | %zu\n", res[0], res[1]);  
    char *substring = malloc(sizeof(char) * (res[1] - res[0] + 1));
    memcpy(substring, &string[res[0]], res[1] - res[0]);
    substring[res[1] - res[0]] = *"\0";
    return substring;
}   

char* reverse(char* string, size_t size) 
{
    char* res = malloc(sizeof(char) * size);
    for (size_t i = 0; i < size; i++)
    {
        res[size - 1 - i] = string[i];
    }
    return res;
}

char* shiftString(char* string, size_t size)
{
    char* res = malloc(sizeof(char) * size);
    char c = string[size-1];
    for (size_t i = 1; i < size; i++)
    {
        res[i] = string[i - 1];
    }
    res[0] = c;
    return res;
}

void allPermutations(char* string, size_t size)
{
    printf("   %s\n", string);
    char* loc = malloc(sizeof(char) * size);
    memcpy(loc, string, size);
    for (size_t i = 0; i < size; i++)
    {
        char* shift = shiftString(loc, size);
        printf("   %s\n", shift);
        memcpy(loc, shift, size);
        free(shift);
    }
    char* reversew = reverse(string, size);
    printf("   %s\n", reversew);
    memcpy(loc, reversew, size);
    for (size_t i = 0; i < size; i++)
    {
        char* shift = shiftString(loc, size);
        printf("   %s\n", shift);
        memcpy(loc, shift, size);
        free(shift);
    }
    free(reversew);
    free(loc);
}


int main() {

    printf("Two Sums\n\n");
    int *sortarr = generateSortedArray(8);
    int *randarr = generateRandomArray(8, 100);
    
    printIntArray(sortarr, 8);
    printIntArray(randarr, 8);

    printSizeTArray(twoSum(sortarr, 8, 3), 2);
    printSizeTArray(twoSum(sortarr, 8, 6), 2);
    printSizeTArray(twoSum(randarr, 8, 48), 2);

    free(sortarr);
    free(randarr);
    
    printf("--------------------\n\n");

    printf("Longest Substring\n\n");

    char *string = "pwwkew";
    printf("%s\n", string);
    printf("%s\n", longestSubstring(string, 10));

    printf("--------------------\n\n");

    printf("All permutations\n\n");

    printf("Testing on : ");
    char* string2 = "abc";
    printf("'%s'.\n", string2);
    allPermutations(string2, 3);
}
