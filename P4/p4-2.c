#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int resoltrisup(int, double **, double *, double);
int gauss(int, double **, double *, double);

int main() {
	int i, j, n, check;
	double **A,**auxA;
	double *b, *auxb, *r;
	double tol = 1.e-10;
	double sum;

	printf("Introduiu la dimensio: n = ");
	scanf("%d", &n);
	printf("\n");

	/*allocate A*/
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
	/*allocate auxA*/
	auxA = (double **)malloc(n * sizeof(double *));
	if (auxA == NULL) {
		printf("No mem\n");
		exit(1);
	}
	for (i = 0; i < n; i++) {
		auxA[i] = (double *)malloc(n * sizeof(double));
		if (auxA[i] == NULL) {
			printf("No mem\n");
			exit(2);
		}
	}

	/*allocate b*/
	b = (double *)malloc(n * sizeof(double));
	if (b == NULL) {
		printf("No mem\n");
		exit(1);
	}

	/*allocate auxb*/
	auxb = (double *)malloc(n * sizeof(double));
	if (auxb == NULL) {
		printf("No mem\n");
		exit(1);
	}

	/*/allocate r*/
	r = (double *)calloc(n,sizeof(double));
	if (r == NULL) {
		printf("No mem\n");
		exit(1);
	}

	/* fill A and auxA */
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			A[i][j] = (double)1 / (i + j + 1);
			auxA[i][j] = A[i][j];
		}

	for (sum = 0, i = 1; i <= n; i++)
		sum += 1. / i;

	/*fill b and auxb*/
	b[0] = sum;
	auxb[0] = b[0];

	for (i = 1; i < n; i++) {
		b[i] = b[i - 1] - 1. / (i)+1. / (i + 3);
		auxb[i] = b[i];
	}

/*FUNCTION CALLING*/

	check = gauss(n, auxA, auxb, tol);

	if (check) {
		printf("Algun pivot es zero al fer reduccio gaussiana\n");
		exit(1);
	}

	check = resoltrisup(n, auxA, auxb, tol);

	if (check) {
		printf("Algun element de la diagonal es zero\n");
		exit(2);
	}

/*OUTPUT*/

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			r[i] += -A[i][j] * auxb[i];

		r[i] += b[i];
	}

	printf("El vector residu es:\n");
	printf("(");

	for(i=0;i<n-1;i++)
		printf("%.2le,", r[i]);
	printf("%.2le)\n", r[n - 1]);

	free(b);
	free(r);
	free(auxb);

	for (i = 0; i < n; i++) {
		free(A[i]);
		free(auxA[i]);
	}
	free(auxA);
	free(A);

	system("pause");
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