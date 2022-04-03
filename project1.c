#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 矩阵相乘
double** multipleMat(double** mat1, double** mat2, int row1, int col1, int col2) {
	int i, j, k;

	// 初始化乘积矩阵
	double** resultMat = (double**)malloc(row1 * sizeof(double*));
	for (i = 0; i < row1; i++) resultMat[i] = (double*)malloc(col2 * sizeof(double));
	for (i = 0; i < row1; i++)
		for (j = 0; j < col2; j++)
			resultMat[i][j] = 0;
	
	// 矩阵相乘
	for (i = 0; i < row1; i++)
		for (j = 0; j < col2; j++) 
			for (k = 0; k < col1; k++) {
				resultMat[i][j] += mat1[i][k] * mat2[k][j];
			}

	return resultMat;
}

// 计算旋转矩阵
double** calcuRotateMat(double phi, double omega, double kappa) {
	int i, j;
	// 初始化三个方向的旋转矩阵
	double **phiMat, **omegaMat, **kappaMat;
	phiMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++) phiMat[i] = (double*)malloc(3 * sizeof(double));
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) phiMat[i][j] = 0;
	omegaMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) omegaMat[i][j] = 0;
	for (i = 0; i < 3; i++) omegaMat[i] = (double*)malloc(3 * sizeof(double));
	kappaMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++) kappaMat[i] = (double*)malloc(3 * sizeof(double));
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) kappaMat[i][j] = 0;

	phiMat[0][0] = cos(phi); phiMat[0][2] = -sin(phi);
	phiMat[1][1] = 1;
	phiMat[2][0] = sin(phi); phiMat[2][2] = cos(phi);
	omegaMat[0][0] = 1;
	omegaMat[1][1] = cos(omega); omegaMat[1][2] = -sin(omega);
	omegaMat[2][1] = sin(omega); omegaMat[2][2] = cos(omega);
	kappaMat[0][0] = cos(kappa); kappaMat[0][1] = -sin(kappa);
	kappaMat[1][0] = sin(kappa); kappaMat[1][1] = cos(kappa);
	kappaMat[2][2] = 1;

	// 计算三个矩阵相乘
	double** tmpMat = multipleMat(phiMat, omegaMat, 3, 3, 3);
	double** resultMat = multipleMat(tmpMat, kappaMat, 3, 3, 3);

	// 释放临时矩阵内存
	for (i = 0; i < 3; i++) free(tmpMat[i]);
	free(tmpMat);

	return resultMat;
}

int main() {
	int m; // 影像比例尺
	double x_0, y_0, f; // 内方位元素
	double** imgCor; // 影像坐标
	double** groundCor; // 地面坐标

	FILE* fp; // 文件句柄
	fp = fopen("data1.txt", "r");
	fscanf(fp, "%d%lf%lf%lf", &m, &x_0, &y_0, &f);
	int N, i; // 控制点数，计数器
	fscanf(fp, "%d", &N);

	// 分配所有坐标所需的空间
	imgCor = (double**)malloc(N * sizeof(double*));
	groundCor = (double**)malloc(N * sizeof(double*));
	for (i = 0; i < N; i++) {
		imgCor[i] = (double*)malloc(2 * sizeof(double));
		groundCor[i] = (double*)malloc(3 * sizeof(double));
	}

	// 读取坐标
	for (i = 0; i < N; i++) {
		fscanf(fp, "%ld%ld", imgCor[i], imgCor[i] + 1);
		fscanf(fp, "%ld%ld%ld", groundCor[i], groundCor[i] + 1, groundCor[i] + 2);
	}

	// 确定初始值
	double X_S, Y_S, Z_S; // 三个线外方位元素
	double phi = 0, omega = 0, kappa = 0; // 三个角外方位元素
	Z_S = m * f;
	for (i = 0; i < N; i++) X_S += groundCor[i][0];
	X_S /= N;
	for (i = 0; i < N; i++) Y_S += groundCor[i][1];
	Y_S /= N;

	double** R; //旋转矩阵
}