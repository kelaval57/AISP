#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct Student student;
typedef struct Student* pozicija;
typedef struct Datum datum;
int unos_na_pocetak(pozicija);
void ispis(pozicija);
int dodaj_na_kraj(pozicija);
pozicija pronadji(pozicija, char[]);
void brisi(pozicija, char);
int dodaj_iza(pozicija, char[]);
int dodaj_ispred(pozicija, char[]);
void sortiraj_po_prezimenu(pozicija);
int upisi_u_datoteku(pozicija);
int citaj_iz_datoteke(pozicija);

struct Datum {
	int dan;
	int mjesec;
	int godina;


};

struct Student {

	char ime[20];
	char prezime[20];
	datum datum_rodjenja;
	pozicija next;


};

int unos_na_pocetak(pozicija head) {
	pozicija novi = (pozicija)malloc(sizeof(student));

	printf("\nunesite ime:\n");
	scanf(" %s", novi->ime);
	printf("\nunesite prezime:\n");
	scanf(" %s", novi->prezime);
	printf("\nunesite datum rodjenja:\n");
	scanf(" %d.%d.%d", &novi->datum_rodjenja.dan, &novi->datum_rodjenja.mjesec, &novi->datum_rodjenja.godina);

	novi->next = head->next;
	head->next = novi;

	return 0;


}

void ispis(pozicija head) {

	while (head != NULL) {
		printf("\n%s %s %d.%d.%d", head->ime, head->prezime, head->datum_rodjenja.dan, head->datum_rodjenja.mjesec, head->datum_rodjenja.godina);
		head = head->next;
	}


}

int dodaj_na_kraj(pozicija head) {
	pozicija novi = (pozicija)malloc(sizeof(student));

	printf("\nunesite ime:\n");
	scanf(" %s", novi->ime);
	printf("\nunesite prezime:\n");
	scanf(" %s", novi->prezime);
	printf("\nunesite datum rodjenja:\n");
	scanf(" %d.%d.%d", &novi->datum_rodjenja.dan, &novi->datum_rodjenja.mjesec, &novi->datum_rodjenja.godina);

	while (head->next != NULL) {
		head = head->next;
	}

	novi->next = head->next;
	head->next = novi;

	return 0;
}

int dodaj_iza(pozicija head, char prezime[]) {
	pozicija trazeni = pronadji(head, prezime);
	if (trazeni == NULL) {
		return -1;
	}
	pozicija novi = (pozicija)malloc(sizeof(student));

	if (novi == NULL) {
		printf("\nGreska pri alokaciji memorije ");
		return -1;
	}
	
	printf("unesite ime: \n");
	scanf("%19s", novi->ime);
	printf("unesite prezime: \n");
	scanf("%19s", novi->prezime);
	printf("\nUnesite datum rodjenja (dan.mjesec.godina):\n");
	scanf("%d.%d.%d",
		&novi->datum_rodjenja.dan,
		&novi->datum_rodjenja.mjesec,
		&novi->datum_rodjenja.godina);

	novi->next = trazeni->next;
	trazeni->next = novi;

	return 0;
}

int dodaj_ispred(pozicija head, char prezime[]) {
	pozicija prethodni = head;
	while (prethodni->next != NULL &&
		strcmp(prethodni->next->prezime, prezime) != 0) {
		prethodni = prethodni->next;
	}
	if (prethodni->next == NULL) {
		printf("Greska student ne postoji ");
		return -1;
	}
	pozicija novi = (pozicija)malloc(sizeof(student));
	if (novi == NULL) {
		printf("Greska pri alokaciji memorije");
		return -1;
	}
	printf("\nUnesite ime:\n");
	scanf("%19s", novi->ime);

	printf("\nUnesite prezime:\n");
	scanf("%19s", novi->prezime);

	printf("\nUnesite datum rodjenja (dan.mjesec.godina):\n");
	scanf("%d.%d.%d",
		&novi->datum_rodjenja.dan,
		&novi->datum_rodjenja.mjesec,
		&novi->datum_rodjenja.godina);

	novi->next = prethodni->next;
	prethodni->next = novi;

	return 0;
}

pozicija pronadji(pozicija head, char prezime[]) {

	while (head != NULL && (strcmp(prezime, head->prezime) != 0)) {
		head = head->next;
	}

	if (head == NULL) {
		printf("\ngreska ne postoji");


		return NULL;
	}
	else
	{
		return head;
	}

}

void brisi(pozicija head, char prezime[])
{

	pozicija temp;

	while (head->next != NULL && strcmp(prezime, head->next->prezime) != 0) {
		head = head->next;
	}

	if (head->next == NULL) {
		printf("\nGreska, ne postoji");
	}
	else {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}

void sortiraj_po_prezimenu(pozicija head) {
	pozicija prethodni, tekuci, sljedeci;

	if (head == NULL || head->next == NULL)
		return;

	prethodni = head;

	while (prethodni->next != NULL) {
		tekuci = prethodni->next;

		while (tekuci->next != NULL) {
			if (strcmp(tekuci->prezime, tekuci->next->prezime) > 0) {
				sljedeci = tekuci->next;

				tekuci->next = sljedeci->next;
				sljedeci->next = tekuci;
				prethodni->next = sljedeci;

				tekuci = sljedeci;
			}

			tekuci = tekuci->next;
		}

		prethodni = prethodni->next;
	}
}


int upisi_u_datoteku(pozicija head) {
	FILE* datoteka = fopen("C:\\Users\\Public\\studenti.txt", "w");

	if (datoteka == NULL) {
		printf("\nGreska pri otvaranju datoteke!\n");
		return -1;
	}

	pozicija tekuci = head->next;

	while (tekuci != NULL) {
		fprintf(datoteka, "%s %s %d.%d.%d\n",
			tekuci->ime,
			tekuci->prezime,
			tekuci->datum_rodjenja.dan,
			tekuci->datum_rodjenja.mjesec,
			tekuci->datum_rodjenja.godina);

		tekuci = tekuci->next;
	}

	fclose(datoteka);

	printf("\nLista je uspjesno zapisana u datoteku studenti.txt\n");

	return 0;
}


int citaj_iz_datoteke(pozicija head) {
	FILE* datoteka = fopen("studenti.txt", "r");

	if (datoteka == NULL) {
		printf("\nGreska pri otvaranju datoteke!\n");
		return -1;
	}

	pozicija novi;
	pozicija zadnji = head;

	while (zadnji->next != NULL) {
		zadnji = zadnji->next;
	}

	while (1) {
		novi = (pozicija)malloc(sizeof(student));

		if (novi == NULL) {
			printf("\nGreska pri alokaciji memorije!\n");
			fclose(datoteka);
			return -1;
		}

		if (fscanf(datoteka, "%19s %19s %d.%d.%d",
			novi->ime,
			novi->prezime,
			&novi->datum_rodjenja.dan,
			&novi->datum_rodjenja.mjesec,
			&novi->datum_rodjenja.godina) != 5) {
			break;
		}

		novi->next = NULL;
		zadnji->next = novi;
		zadnji = novi;
	}

	fclose(datoteka);

	printf("\nStudenti su ucitani iz datoteke!\n");

	return 0;
}



int main() {
	student head = { 0 };
	pozicija neki_student = NULL;
	char prezime[20];
	char prezime_iza[20];
	char prezime_ispred[20];

	citaj_iz_datoteke(&head);

	printf("\nUcitan popis studenata:\n");
	ispis(head.next);

	printf("\n\nUnesite prezime studenta kojeg trazite: ");
	scanf("%19s", prezime);

	neki_student = pronadji(head.next, prezime);

	if (neki_student != NULL) {
		printf("\nPronadjeni student:\n%s %s %d.%d.%d\n",
			neki_student->ime,
			neki_student->prezime,
			neki_student->datum_rodjenja.dan,
			neki_student->datum_rodjenja.mjesec,
			neki_student->datum_rodjenja.godina);
	}

	printf("\nUnesite prezime studenta kojeg zelite obrisati: ");
	scanf("%19s", prezime);
	brisi(&head, prezime);

	printf("\nLista nakon brisanja:\n");
	ispis(head.next);

	printf("\n\nIza kojeg studenta zelite dodati novog studenta? ");
	scanf("%19s", prezime_iza);

	dodaj_iza(&head, prezime_iza);

	printf("\nIspred kojeg studenta zelite dodati novog studenta? ");
	scanf("%19s", prezime_ispred);

	dodaj_ispred(&head, prezime_ispred);

	printf("\nLista nakon dodavanja:\n");
	ispis(head.next);

	sortiraj_po_prezimenu(&head);

	printf("\nSortirana lista po prezimenima:\n");
	ispis(head.next);

	upisi_u_datoteku(&head);

	return 0;
}
