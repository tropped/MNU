#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int resoltrisup(int, double **, double *, double);
int gauss(int, double **, double *, double);

int main() {
	int i, j, n, check;
/*	char nom[90]; */
	double **A;
	double *b;
	double tol = 1.e-10;

/*INPUT*/

/*	FILE *p;  
                                                    Això és per si he de llegir d'un arxiu
	printf("Nom de l'arxiu de lectura: ");
	scanf(" %s", nom);
	p = fopen(nom, "r");

	if (p == NULL) {
		printf("No s'ha pogut obrir l'arxiu de lectura.\n");
		exit(-1);
	}

	fscanf(p, "%d", &n);
*/
	printf("Introduiu la dimensio: n = ");
	scanf("%d", &n);
	printf("\n");

	A = (double **)malloc(n * sizeof(double *));
	if (A == NULL) {
		printf("No mem\n");
		exit(1);
	}
	for (i = 0; i < n; i++) {
		A[i] = (double *)malloc(n * sizeof(double));
		if (A[i] == NULL) {
			printf("No mem\n");
			exit(2);
		}
	}
	
	b = (double *)malloc(n * sizeof(double));
	if (b == NULL) {
		printf("No mem\n");
		exit(1);
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%le", &A[i][j]); /* fscanf(p, "%le", &A[i][j]); */

	for (i = 0; i < n; i++)
		scanf("%le", &b[i]); /* fscanf(p, "%le", &b[i]); */


/*FUNCTION CALLING*/

	check = gauss(n, A, b, tol);

	if (check) {
		printf("Algun pivot es zero al fer reduccio gaussiana\n");
		exit(1);
	}

	check = resoltrisup(n, A, b, tol);

	if (check) {
		printf("Algun element de la diagonal es zero\n");
		exit(2);
	}

/*OUTPUT*/

	printf("El vector solucio es:\n");
	printf("(");

	for(i=0;i<n-1;i++)
		printf("%.2le,", b[i]);
	printf("%.2le)\n", b[n - 1]);

	free(b);
	for (i = 0; i < n; i++)
		free(A[i]);
	free(A);
	/*fclose(p)*/
	return 0;

	}

int resoltrisup(int n, double **A, double *b, double tol) {

	int i, j;
	double suma;

	for (i = 0; i<n; i++)
		if (fabs(A[i][i])<tol)
			return -1;

	b[n - 1] /= A[n - 1][n - 1];

	for (i = n - 2; i >= 0; i--) {

		for (suma = 0, j = i + 1; j<n; j++)
			suma += A[i][j] * b[j];


		b[i] = (b[i] - suma) / A[i][i];

	}

	return 0;

}


int gauss(int n, double **A, double *b, double tol) {

	int i, j, k;
	double m;

	for (i = 0; i < n; i++)
		if (fabs(A[i][i]) < tol)
			return -1;

	for (k = 0; k < n - 1; k++) {
		for (i = k + 1; i < n; i++) {
			m = A[i][k] / A[k][k];
			A[i][k] = m;
			for (j = k + 1; j < n; j++)
				A[i][j] = A[i][j] - m*A[k][j];

			b[i] = b[i] - m*b[k];

		}
	}

	return 0;
}