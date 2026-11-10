#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Cvor cvor;
typedef struct Cvor* pozicija;
int unos(pozicija, int);
int ispis(pozicija);
pozicija presjek_dvije_liste(pozicija, pozicija);
pozicija unija_dvije_liste(pozicija, pozicija);





struct Cvor {
	int el;
	pozicija next;

};

int unos(pozicija head, int x) {
	pozicija novi = (pozicija)malloc(sizeof(cvor));
	novi->el = x;

	novi->next = head->next;
	head->next = novi;

	return 0;
}


pozicija unija_dvije_liste(pozicija head1, pozicija head2) {
	pozicija head = NULL;
	pozicija novi = NULL;
	pozicija zadnji = NULL;

	while (head1 != NULL && head2 != NULL) {
		novi = (pozicija)malloc(sizeof(cvor));

		if (head1->el < head2->el) {
			novi->el = head1->el;
			head1 = head1->next;
		}
		else if (head1->el > head2->el) {
			novi->el = head2->el;
			head2 = head2->next;
		}
		else {
			novi->el = head1->el;
			head1 = head1->next;
			head2 = head2->next;
		}

		novi->next = NULL;

		if (head == NULL)
			head = novi;
		else
			zadnji->next = novi;

		zadnji = novi;
	}

	while (head1 != NULL) {
		novi = (pozicija)malloc(sizeof(cvor));
		novi->el = head1->el;
		novi->next = NULL;

		if (head == NULL)
			head = novi;
		else
			zadnji->next = novi;

		zadnji = novi;
		head1 = head1->next;
	}

	while (head2 != NULL) {
		novi = (pozicija)malloc(sizeof(cvor));
		novi->el = head2->el;
		novi->next = NULL;

		if (head == NULL)
			head = novi;
		else
			zadnji->next = novi;

		zadnji = novi;
		head2 = head2->next;
	}

	return head;
}


pozicija presjek_dvije_liste(pozicija head1, pozicija head2) {
	pozicija head = NULL;
	pozicija novi = NULL;
	pozicija zadnji = NULL;

	while (head1 != NULL && head2 != NULL) {

		if (head1->el < head2->el)
			head1 = head1->next;

		else if (head1->el > head2->el)
			head2 = head2->next;

		else {
			novi = (pozicija)malloc(sizeof(cvor));
			novi->el = head1->el;
			novi->next = NULL;

			if (head == NULL)
				head = novi;
			else
				zadnji->next = novi;

			zadnji = novi;

			head1 = head1->next;
			head2 = head2->next;
		}
	}

	return head;
}

int ispis(pozicija head) {
	printf("\n");

	while (head != NULL) {
		printf(" %d", head->el);
		head = head->next;
	}
	return 0;
}



int main() {
	cvor head1 = { 0 };
	cvor head2 = { 0 };


	unos(&head1, 23);
	unos(&head1, 15);
	unos(&head1, 12);
	unos(&head1, 7);
	unos(&head1, 5);
	unos(&head1, 2);

	unos(&head2, 70);
	unos(&head2, 50);
	unos(&head2, 8);
	unos(&head2, 5);
	unos(&head2, 2);
	unos(&head2, 1);


	pozicija presjek = presjek_dvije_liste(head1.next, head2.next);
	pozicija unija = unija_dvije_liste(head1.next, head2.next);

	printf("presjek: ");
	ispis(presjek);
	printf("\nunija: ");
	ispis(unija);


	return 0;
}