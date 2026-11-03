#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Polinom {
    int koef;
    int exp;
    struct Polinom* next;
};

void ispis(struct Polinom* P) {
    struct Polinom* tek = P;

    while (tek != NULL) {
        printf("%dx^%d", tek->koef, tek->exp);

        if (tek->next != NULL) {
            printf(" + ");
        }

        tek = tek->next;
    }

    printf("\n");
}

int main() {
    FILE* dat;
    dat = fopen("polinomi.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!");
        return 1;
    }

    struct Polinom* P = NULL;
    struct Polinom* Q = NULL;

    struct Polinom* novi;
    struct Polinom* krajP = NULL;
    struct Polinom* krajQ = NULL;

    int koef, exp;
    int br = 0;
    char red[100];

    while (fgets(red, 100, dat) != NULL) {

        if (sscanf(red, "%d %d", &koef, &exp) == 2) {

            novi = (struct Polinom*)malloc(sizeof(struct Polinom));

            novi->koef = koef;
            novi->exp = exp;
            novi->next = NULL;

            if (br == 0) {
                if (P == NULL) {
                    P = novi;
                }
                else {
                    krajP->next = novi;
                }

                krajP = novi;
            }
            else {
                if (Q == NULL) {
                    Q = novi;
                }
                else {
                    krajQ->next = novi;
                }

                krajQ = novi;
            }
        }
        else {
            br++;
        }
    }

    fclose(dat);

    printf("Prvi polinom:\n");
    ispis(P);

    printf("Drugi polinom:\n");
    ispis(Q);

    return 0;
}

