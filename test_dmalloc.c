#include <stdlib.h>
#include <stdio.h>
#include "dmm.h"


int main(int argc, char *argv[])
{
    // Summary of Calls
    // A. ar0 = dmalloc(5)
    // B. ar1 = dmalloc(200)
    // C. ar2 = dmalloc(900) **Supposed to fail**

    char *ar0, *ar1, *ar2;
    int i;

    // dmalloc Ar0
    printf("ar 0: calling dmalloc(5)\n");
    ar0 = dmalloc(5);
    if (ar0 == NULL) {
        fprintf(stderr, "ar0 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar0[i] = 'A';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar0[i]);
    }
    printf("\n");

    // dmalloc Ar1
    printf("ar 1: calling dmalloc(200)\n");
    ar1 = dmalloc(200);
    if (ar1 == NULL) {
        fprintf(stderr, "ar1 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 200; ++i) {
        ar1[i] = 'B';
    }

    for (i = 0; i < 200; ++i) {
        printf("%c", ar1[i]);
    }
    printf("\n");
    
    // dmalloc ar2
    printf("ar 2: calling dmalloc(900)\n");

    ar2 = dmalloc(900);
    printf("%p\n", ar2);

    if (ar2 == NULL) {
        printf("ar2 dmalloc call succesfully failed\n");
    } else {
        printf("\ndmalloc(900) should return NULL\n");
        exit(1);
    }

    printf("\n\ndmalloc tests passed!\n");

    return 0;
}
