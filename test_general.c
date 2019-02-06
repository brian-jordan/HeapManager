#include <stdlib.h>
#include <stdio.h>
#include "dmm.h"


int main(int argc, char *argv[])
{
    // Summary of Calls
    // A. ar0 = dmalloc(5)
    // B. ar1 = dmalloc(200)
    // C. ar2 = dmalloc(900) **Supposed to fail**

    char *ar0, *ar1, *ar2, *ar3, *ar4, *ar5;
    int i;

    // dmalloc Ar0
    printf("ar 0: calling dmalloc(5)\n");
    ar0 = dmalloc(5);
    if (ar0 == NULL) {
        fprintf(stderr, "ar0 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar0[i] = 'B';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar0[i]);
    }
    printf("\n");


    // dmalloc Ar1
    printf("ar 1: calling dmalloc(5)\n");
    ar1 = dmalloc(5);
    if (ar1 == NULL) {
        fprintf(stderr, "ar1 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar1[i] = 'C';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar1[i]);
    }
    printf("\n");

    // dmalloc Ar2
    printf("ar 2: calling dmalloc(5)\n");
    ar2 = dmalloc(5);
    if (ar2 == NULL) {
        fprintf(stderr, "ar2 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar2[i] = 'D';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar2[i]);
    }
    printf("\n");

    // dmalloc Ar3
    printf("ar 3: calling dmalloc(5)\n");
    ar3 = dmalloc(5);
    if (ar3 == NULL) {
        fprintf(stderr, "ar3 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar3[i] = 'E';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar3[i]);
    }
    printf("\n");

    // dmalloc Ar4
    printf("ar 4: calling dmalloc(5)\n");
    ar4 = dmalloc(5);
    if (ar4 == NULL) {
        fprintf(stderr, "ar4 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 5; ++i) {
        ar4[i] = 'F';
    }

    for (i = 0; i < 5; ++i) {
        printf("%c", ar4[i]);
    }
    printf("\n");

    printf("calling dfree(ar1)\n");
    dfree(ar1);
    printf("calling dfree(ar4)\n");
    dfree(ar4);
    printf("calling dfree(ar0)\n");
    dfree(ar0);
    printf("calling dfree(ar2)\n");
    dfree(ar2);

    // dmalloc Ar5
    printf("ar 5: calling dmalloc(12)\n");
    ar5 = dmalloc(12);
    if (ar5 == NULL) {
        fprintf(stderr, "ar5 dmalloc has failed");
        exit(1);
    } 
    
    for (i = 0; i < 12; ++i) {
        ar5[i] = 'G';
    }

    for (i = 0; i < 12; ++i) {
        printf("%c", ar5[i]);
    }
    printf("\n");

    printf("calling dfree(ar3)\n");
    dfree(ar3);


    printf("ALL GENERAL TESTS PASSED\n");
}

