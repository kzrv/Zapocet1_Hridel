#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000


typedef struct tyma {
	char id[10];
	char team[30];
	char group;
	int games;
	int wins;
	int wins_ot;
	int losses_ot;
	int losses;
	int gf;
	int ga;
	int pts;
}TYMA;

void odehrajZapas(TYMA t, TYMA t1);
void odehrajSkupinu(TYMA* t);


void odehrajZapas(TYMA* t, TYMA* t1) {
	int tym_gol = rand() % 10;
	int tym_gol1 = rand() % 10;
	if (tym_gol > tym_gol1) {
		t->pts += 3;
		t->wins += 1;
		t1->losses += 1;
		printf("Vyhrala hru tyma: %s\n Pocet: %d:%d\n", t->team, tym_gol, tym_gol1);
	}
	else if (tym_gol < tym_gol1) {
		t1->pts += 3;
		t1->wins += 1;
		t->losses += 1;
		printf("Vyhrala hru tyma: %s\n Pocet: %d:%d\n", t1->team, tym_gol, tym_gol1);
	}
	else if (tym_gol == tym_gol1) {
		while (tym_gol == tym_gol1) {
			tym_gol += rand() % 10;
			tym_gol1 += rand() % 10;
		}
		if (tym_gol > tym_gol1) {
			t->pts += 2;
			t1->pts += 1;
			t->wins_ot += 1;
			t1->losses_ot += 1;
			printf("Vyhrala hru tyma: %s\n Pocet: %d:%d\n", t->team, tym_gol, tym_gol1);
		}
		else {
			t->pts += 1;
			t1->pts += 2;
			t1->wins_ot += 1;
			t->losses_ot += 1;
			printf("Vyhrala hru tyma: %s\n Pocet: %d:%d\n", t1->team, tym_gol, tym_gol1);
		}
		t->gf += tym_gol;
		t1->gf += tym_gol1;
		t->ga += tym_gol1;
		t1->ga += tym_gol;
	}
	t->games++;
	t1->games++;
}
int compare(const void* a, const void* b) {
	TYMA* tym1 = (TYMA*)a;
	TYMA* tym2 = (TYMA*)b;
	if (tym1->pts != tym2->pts) {
		return tym2->pts - tym1->pts;
	}
	else if (tym1->gf - tym1->ga != tym2->gf - tym2->ga) {
		return (tym2->gf - tym2->ga) - (tym1->gf - tym1->ga);
	}
	else {
		return tym2->gf - tym1->gf;
	}
}

void odehrajSkupinu(TYMA* A,int pocet) {
	for (int i = 0; i < pocet;i++) {
		for (int j = i+1;j < pocet; j++) {
			odehrajZapas(&A[i], &A[j]);
		}
	}
	FILE* f = fopen("output.txt", "w");
	if (f == NULL) {
		printf("CHYBA CTENI");
		return 1;
	}
	qsort(A, pocet, sizeof(TYMA), compare);
	for (int i = 0; i < pocet;i++) {

		printf("%s,%s,%c,%d,%d,%d,%d,%d,%d,%d,%d\n",
			A[i].id, A[i].team, A[i].group, A[i].games, A[i].wins, A[i].wins_ot,
			A[i].losses_ot, A[i].losses, A[i].gf, A[i].ga, A[i].pts);
		printf("------------------------------------------\n");
		fprintf(f, "%s,%s,%c,%d,%d,%d,%d,%d,%d,%d,%d\n",
			A[i].id, A[i].team, A[i].group, A[i].games, A[i].wins, A[i].wins_ot,
			A[i].losses_ot, A[i].losses, A[i].gf, A[i].ga, A[i].pts);
	}
	
	
}

int main(void) {
	srand(time(NULL));
	FILE* f = fopen("input.csv", "r");
	if (f == NULL) {
		printf("CHYBA CTENI");
		return 1;
	}
	TYMA* A = malloc(sizeof(TYMA));
	TYMA* B = malloc(sizeof(TYMA));
	if (B == NULL || A == NULL) {
		printf("CHYBA ALLOKOVANI");
		return 1;
	}
	char buf[N];
	fgets(buf, N, f);
	int a = 0, b = 0;
	while (fgets(buf, N, f)) {
		char* str1 = strchr(buf, ',');
		char* str2 = strchr(str1+1, ',');
		char* str3 = str2 + 1;
		if (str3[0] == 'A') {
			sscanf(buf, "%[^,],%[^,],%c,%d,%d,%d,%d,%d,%d,%d,%d",
				A[a].id, A[a].team, &A[a].group, &A[a].games, &A[a].wins, &A[a].wins_ot,
				&A[a].losses_ot, &A[a].losses, &A[a].gf, &A[a].ga, &A[a].pts);
			a++;
			A = realloc(A, sizeof(TYMA) * (a + 1));
		}
		else {
			sscanf(buf, "%[^,],%[^,],%c,%d,%d,%d,%d,%d,%d,%d,%d",
				B[b].id, B[b].team, &B[b].group, &B[b].games, &B[b].wins, &B[b].wins_ot,
				&B[b].losses_ot, &B[b].losses, &B[b].gf, &B[b].ga, &B[b].pts);
			b++;
			B = realloc(B, sizeof(TYMA) * (b + 1));
		}
	}
	for (int i = 0; i < a;i++) {
		printf("%s,%s,%c,%d,%d,%d,%d,%d,%d,%d,%d\n",
			B[i].id, B[i].team, B[i].group, B[i].games, B[i].wins, B[i].wins_ot,
			B[i].losses_ot, B[i].losses, B[i].gf, B[i].ga, B[i].pts);
		printf("%s,%s,%c,%d,%d,%d,%d,%d,%d,%d,%d\n",
			A[i].id, A[i].team, A[i].group, A[i].games,A[i].wins, A[i].wins_ot,
			A[i].losses_ot, A[i].losses, A[i].gf, A[i].ga, A[i].pts);
		printf("------------------------------------------\n");
		

	}
	odehrajSkupinu(A,a);
	odehrajSkupinu(B,b);
	return 0;
}