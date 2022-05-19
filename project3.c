#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535
#define max(x, y) (((x) > (y)) ? (x) : (y))

// 分配矩阵
double** NewMat(int row, int col) {
	double **mat = (double**)malloc(row * sizeof(double*));
	int i, j;
	if (row) {
		mat[0] = (double*)malloc(row * col * sizeof(double));
		for (i = 1; i < row; i++) {
			mat[i] = mat[0] + i * col;
		}
	}
	for (i = 0; i < row; i++)
		for (j = 0; j < col; ++j)
			mat[i][j] = 0;
	return mat;
}

// 删除矩阵
void deleteMat(double **mat, int row, int col) {
	if (row)
		free(mat[0]);
	free(mat);
}

// 矩阵相乘
double** multipleMat(double** mat1, double** mat2, int row1, int col1, int col2) {
	int i, j, k;

	// 初始化乘积矩阵
	double** resultMat = NewMat(row1, col2);
	for (i = 0; i < row1; i++)
		for (j = 0; j < col2; j++)
			resultMat[i][j] = 0;	
	
	// 矩阵相乘
	for (i = 0; i < row1; i++)
		for (j = 0; j < col2; j++) 
			for (k = 0; k < col1; k++)
				resultMat[i][j] += mat1[i][k] * mat2[k][j];

	return resultMat;
}

// 作矩阵的转置
double** transpMat(double** mat, int row, int col) {
	int i, j;
	double** resultMat = NewMat(col, row);
	for (i = 0; i < col; i++)
		for (j = 0; j < row; j++)
			resultMat[i][j] = mat[j][i];
	
	return resultMat;
}

// 计算行列式
double calcuDet(double** mat, int n) {
	if (n == 1)
		return mat[0][0];
	else {
		int i, j, k;
		double result = 0;
		for (i = 0; i < n; i++) {
			double** cplMat = NewMat(n - 1, n - 1);
			for (j = 0; j < n - 1; j++) 
				for (k = 0; k < n; k++)
					if (k < i) 
						cplMat[j][k] = mat[j + 1][k];
					else if (k > i)
						cplMat[j][k - 1] = mat[j + 1][k];
			result += mat[0][i] * pow(-1, 1 + i + 1) * calcuDet(cplMat, n - 1);
			deleteMat(cplMat, n - 1, n - 1);
		}
		return result;
	}	
}

// 计算逆矩阵
double** calcuInverseMat(double** mat, int n) {
	double det = calcuDet(mat, n);
	if (det == 0) return NULL;
	else {
		int i, j, k, l;
		double** acpyMat = NewMat(n, n);
		for (i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				double** cplMat = NewMat(n - 1, n - 1);
				for (k = 0; k < n; k++)
					for (l = 0; l < n; l++)
						if (k < j){
							if (l < i)
								cplMat[k][l] = mat[k][l];
							else if (l > i)
								cplMat[k][l - 1] = mat[k][l];
						}
						else if (k > j) {
							if (l < i)
								cplMat[k - 1][l] = mat[k][l];
							else if (l > i)
								cplMat[k - 1][l - 1] = mat[k][l];
						}
				acpyMat[i][j] = pow(-1, i + j + 2) * calcuDet(cplMat, n - 1) / det;
				deleteMat(cplMat, n - 1, n - 1);
			}	
		return acpyMat;
	}
}

// 计算旋转矩阵
double** calcuRMat(double phi, double omega, double kappa) {
	int i;
	double **R = NewMat(3, 3);
	R[0][0] = cos(phi) * cos(kappa) - sin(phi) * sin(omega) * sin(kappa);
	R[0][1] = -cos(phi) * sin(kappa) - sin(phi) * sin(omega) * cos(kappa);
	R[0][2] = -sin(phi) * cos(omega);
	R[1][0] = cos(omega) * sin(kappa);
	R[1][1] = cos(omega) * cos(kappa);
	R[1][2] = -sin(omega);
	R[2][0] = sin(phi) * cos(kappa) + cos(phi) * sin(omega) * sin(kappa);
	R[2][1] = -sin(phi) * sin(kappa) + cos(phi) * sin(omega) * cos(kappa);
	R[2][2] = cos(phi) * cos(omega);
	return R;
}

// 打印矩阵
void printMat(char *name, double **mat, int row, int col) {
	int i, j;
	printf("%s:\n", name);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) 
			printf("    %8.4lf", mat[i][j]);
		putchar('\n');
	}
}

int main() {
	double **elements = NewMat(7, 1);  // 七个绝对定向元素
    int i, j;
    double minLimit = 0.00001, minChange;
    int maxTry = 200, tryTime = 0;

    FILE *fp;
    int N;
    double **imgCoors, **grdCoors;
    fp = fopen("./data3.txt", "r");
    fscanf(fp, "%d", &N);
	imgCoors = NewMat(N, 3);
	grdCoors = NewMat(N, 3);
    for (i = 0; i < N; i++) {
        fscanf(fp, "%lf%lf%lf", imgCoors[i], imgCoors[i] + 1, imgCoors[i] + 2);
        fscanf(fp, "%lf%lf%lf", grdCoors[i], grdCoors[i] + 1, grdCoors[i] + 2);
    }
    fclose(fp);

    do {
		double **R = calcuRMat(elements[4][0], elements[5][0], elements[6][0]);
		double **A = NewMat(3 * N, 7);
		double **L = NewMat(3 * N, 1);
		for (i = 0; i < N; i++) {
			double **XYZ = transpMat(imgCoors + i, 1, 3);
			double **XYZPrime = multipleMat(R, XYZ, 3, 3, 1);
			for (j = 0; j < 3; j++)
				L[i * 3 + j][0] = grdCoors[i][j] - elements[j][0] - elements[3][0]*XYZPrime[j][0];
			
			A[i * 3 + 0][0] = 1; 				A[i * 3 + 1][0] = 0; 				A[i * 3 + 2][0] = 0;
			A[i * 3 + 0][1] = 0; 				A[i * 3 + 1][1] = 1; 				A[i * 3 + 2][1] = 0;
			A[i * 3 + 0][2] = 0; 				A[i * 3 + 1][2] = 0; 				A[i * 3 + 2][2] = 1;
			A[i * 3 + 0][3] = XYZPrime[0][0]; 	A[i * 3 + 1][3] = XYZPrime[1][0]; 	A[i * 3 + 2][3] = XYZPrime[2][0];
			A[i * 3 + 0][4] = -XYZPrime[2][0]; 	A[i * 3 + 1][4] = 0; 				A[i * 3 + 2][4] = XYZPrime[0][0];
			A[i * 3 + 0][5] = 0; 				A[i * 3 + 1][5] = -XYZPrime[2][0]; 	A[i * 3 + 2][5] = XYZPrime[1][0];
			A[i * 3 + 0][6] = -XYZPrime[1][0]; 	A[i * 3 + 1][6] = XYZPrime[0][0]; 	A[i * 3 + 2][6] = 0;

			deleteMat(XYZ, 3, 1);
			deleteMat(XYZPrime, 3, 1);
		}

		double **AT = transpMat(A, 3 * N, 7);
		double **ATA = multipleMat(AT, A, 7, 3 * N, 7);
		double **inverATA = calcuInverseMat(ATA, 7);
		double **ATL = multipleMat(AT, L, 7, 3 * N, 1);
		double **X = multipleMat(inverATA, ATL, 7, 7, 1);

		minLimit = X[0][0]; elements[0][0] += X[0][0];
		minLimit = max(minLimit, X[1][0]); elements[1][0] += X[1][0];
		minLimit = max(minLimit, X[2][0]); elements[2][0] += X[2][0];
		minLimit = max(minLimit, X[3][0]); elements[3][0] += X[3][0];
		minLimit = max(minLimit, X[4][0]); elements[4][0] += X[4][0];
		minLimit = max(minLimit, X[5][0]); elements[5][0] += X[5][0];
		minLimit = max(minLimit, X[6][0]); elements[6][0] += X[6][0];

		deleteMat(R, 3, 3); deleteMat(A, 3 * N, 7); deleteMat(L, 3 * N, 1);
		deleteMat(AT, 7, 3 * N); deleteMat(ATA, 7, 7); deleteMat(inverATA, 7, 7);
		deleteMat(ATL, 7, 1); deleteMat(X, 7, 1);
        tryTime++;
    } while(minChange < minLimit && tryTime <= maxTry);

	printf("%.3lf %.3lf %.3lf %.6lf %.6lf %.6lf %.6lf\n", 
		elements[0][0], elements[1][0], elements[2][0], 
		elements[3][0], elements[4][0], elements[5][0], elements[6][0]);

	return 0;
}