#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI acos(-1)

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
			for (k = 0; k < col1; k++)
				resultMat[i][j] += mat1[i][k] * mat2[k][j];

	return resultMat;
}

// 计算旋转矩阵
double** calcuRotateMat(double phi, double omega, double kappa) {
	int i, j;
	// 初始化三个方向的旋转矩阵
	double **phiMat, **omegaMat, **kappaMat;
	phiMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++) phiMat[i] = (double*)malloc(3 * sizeof(double));
	omegaMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++) omegaMat[i] = (double*)malloc(3 * sizeof(double));
	kappaMat = (double**)malloc(3 * sizeof(double*));
	for (i = 0; i < 3; i++) kappaMat[i] = (double*)malloc(3 * sizeof(double));
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			phiMat[i][j] = 0;
			omegaMat[i][j] = 0;
			kappaMat[i][j] = 0;
		}

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
	double** R = multipleMat(tmpMat, kappaMat, 3, 3, 3);

	// 释放临时矩阵内存
	for (i = 0; i < 3; i++) {
		free(tmpMat[i]);
		free(phiMat[i]);
		free(omegaMat[i]);
		free(kappaMat[i]);
	}
	free(tmpMat);
	free(phiMat);
	free(omegaMat);
	free(kappaMat);

	return R;
}

// 作矩阵的转置
double** transpMat(double** mat, int row, int col) {
	int i, j;
	double** resultMat = (double**)malloc(col * sizeof(double*));
	for (i = 0; i < col; i++) resultMat[i] = (double*)malloc(row * sizeof(double));
	for (i = 0; i < col; i++)
		for (j = 0; j < row; j++)
			resultMat[i][j] = mat[j][i];
	
	return resultMat;
}

// 用共线方程计算各个像点的像平面坐标近似值
double** calcuColineation(double x_0, double y_0, double f, double** R, double** groundCoor, int n, double X_S, double Y_S, double Z_S) {
	double *xCon, *yCon, *zCon;
	int i, j;
	xCon = (double*)malloc(n * sizeof(double*));
	yCon = (double*)malloc(n * sizeof(double*));
	zCon = (double*)malloc(n * sizeof(double*));
	double** calculatedCoor = (double**)malloc(n * sizeof(double*));
	for (i = 0; i < n; i++) calculatedCoor[i] = (double*)malloc(2 * sizeof(double));
	for (i = 0; i < n; i++)
		for (j = 0; j < 2; j++)
			calculatedCoor[i][j] = 0;	
	for (i = 0; i < n; i++) {
		xCon[i] += R[0][0] * (groundCoor[i][0] - X_S) + R[1][0] * (groundCoor[i][1] - Y_S) + R[2][0] * (groundCoor[i][2] - Z_S);
		yCon[i] += R[0][1] * (groundCoor[i][0] - X_S) + R[1][1] * (groundCoor[i][1] - Y_S) + R[2][1] * (groundCoor[i][2] - Z_S);
		zCon[i] += R[0][2] * (groundCoor[i][0] - X_S) + R[1][2] * (groundCoor[i][1] - Y_S) + R[2][2] * (groundCoor[i][2] - Z_S);
	}
	// 计算像点像平面坐标
	for (i = 0; i < n; i++) {
		calculatedCoor[i][0] = x_0 - f * xCon[i] / zCon[i];
		calculatedCoor[i][1] = y_0 - f * yCon[i] / zCon[i];
	}

	free(xCon);
	free(yCon);
	free(zCon);
	return calculatedCoor;
}

// 计算误差系数矩阵
double** calcuCoefficient(double x_0, double y_0, double f, double** R, double** imgCoor, double** groundCoor, int n, double omega, double kappa, double X_S, double Y_S, double Z_S) {
	double* zCon = (double*)malloc(n * sizeof(double));
	int i, j;
	for (i = 0; i < n; i++) zCon[i] = 0;
	for (i = 0; i < n; i++) 
		zCon[i] += R[0][2] * (groundCoor[i][0] - X_S) + R[1][2] * (groundCoor[i][1] - Y_S) + R[2][2] * (groundCoor[i][2] - Z_S);

	double** coefficientMat = (double**)malloc(2 * n * sizeof(double*));
	for (i = 0; i < 2 * n; i++) coefficientMat[i] = (double*)malloc(6 * sizeof(double));
	for (i = 0; i < 2 * n; i++)
		for (j = 0; j < 6; j++)
			coefficientMat[i][j] = 0;
	for (i = 0; i < n; i++) {
		coefficientMat[2*i][0] = 1.0 / zCon[i] * (R[0][0] * f + R[0][2] * (imgCoor[i][0] - x_0));
		coefficientMat[2*i][1] = 1.0 / zCon[i] * (R[1][0] * f + R[1][2] * (imgCoor[i][0] - x_0));
		coefficientMat[2*i][2] = 1.0 / zCon[i] * (R[2][0] * f + R[2][2] * (imgCoor[i][0] - x_0));
		coefficientMat[2*i + 1][0] = 1.0 / zCon[i] * (R[0][1] * f + R[0][2] * (imgCoor[i][1] - y_0));
		coefficientMat[2*i + 1][1] = 1.0 / zCon[i] * (R[1][1] * f + R[1][2] * (imgCoor[i][1] - y_0));
		coefficientMat[2*i + 1][2] = 1.0 / zCon[i] * (R[2][1] * f + R[2][2] * (imgCoor[i][1] - y_0));
		coefficientMat[2*i][3] = (imgCoor[i][1] - y_0) * sin(omega) - ((imgCoor[i][0] - x_0) / f * ((imgCoor[i][0] - x_0) * cos(kappa) - \
								- (imgCoor[i][1] - y_0) * sin(kappa)) + f * cos(kappa)) * cos(omega);
		coefficientMat[2*i][4] = -f * sin(kappa) - (imgCoor[i][0] - x_0) / f * ((imgCoor[i][0] - x_0) * sin(kappa) + (imgCoor[i][1] - y_0) * \
								cos(kappa));
		coefficientMat[2*i][5] = imgCoor[i][1] - y_0;
		coefficientMat[2*i + 1][3] = (imgCoor[i][0] - x_0) * sin(omega) - ((imgCoor[i][1] - y_0) / f * ((imgCoor[i][0] - x_0) * cos(kappa) - \
								- (imgCoor[i][1] - y_0) * sin(kappa)) + f * sin(kappa)) * cos(omega);
		coefficientMat[2*i + 1][4] = -f * cos(kappa) - (imgCoor[i][1] - y_0) / f * ((imgCoor[i][0] - x_0) * sin(kappa) + (imgCoor[i][1] - y_0) * \
								cos(kappa));
		coefficientMat[2*i + 1][5] = imgCoor[i][0] - x_0;
	}

	free(zCon);

	return coefficientMat;
}

/* 求解法方程
double* solEqual(double** coefficientMat, int row, int col, double* constMat) {
	int i, j, k;
	
	// 增广矩阵
	double** augmentMat = (double**)malloc(row * sizeof(double*));
	for (i = 0; i < row; i++) augmentMat[i] = (double*)malloc((col + 1) * sizeof(double));
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			augmentMat[i][j] = coefficientMat[i][j];
	for (i = 0; i < row; i++)
		augmentMat[i][col] = constMat[i];

	for (i = 0; i < col; i++) {
		// 将非零行移至最上方
		double maxValue = fabs(augmentMat[i][i]);
		int maxLine = i;
		for (j = i + 1; j < row; j++)
			if (fabs(augmentMat[j][i]) > maxValue) {
				maxValue = fabs(augmentMat[j][i]);
				maxLine = j;
			}
		
		if (maxLine > i)
			for (j = 0; j < col + 1; j++) {
				double tmp = augmentMat[i][j];
				augmentMat[i][j] = augmentMat[maxLine][j];
				augmentMat[maxLine][j] = tmp;
			}

		// 消去其余行首项
		for (j = i; j < col + 1; j++) augmentMat[i][j] /= augmentMat[i][i];
		for (j = i + 1; j < row; j++)
			for (k = i; k < col + 1; k++) 
				augmentMat[j][k] -= augmentMat[i][k] * augmentMat[j][i];
	}

	double* result = (double*)malloc(row * sizeof(double));
	for (i = 0; i < col; i++) result[i] = augmentMat[i][col];

	for (i = 0; i < row; i++) free(augmentMat[i]);
	free(augmentMat);

	return result;
}
*/

// 计算行列式
double calcuDet(double** mat, int n) {
	if (n == 1)
		return mat[0][0];
	else {
		int i, j, k;
		double result = 0;
		for (i = 0; i < n; i++) {
			double** cplMat = (double**)malloc((n - 1) * sizeof(double*));
			for (j = 0; j < n - 1; j++) cplMat[j] = (double*)malloc((n - 1) * sizeof(double));
			for (j = 0; j < n - 1; j++) 
				for (k = 0; k < n; k++)
					if (k < i) 
						cplMat[j][k] = mat[j + 1][k];
					else if (k > i)
						cplMat[j][k - 1] = mat[j + 1][k];
			result += mat[0][i] * pow(-1, 1 + i + 1) * calcuDet(cplMat, n - 1);
			for (j = 0; j < n - 1; j++) free(cplMat[j]);
			free(cplMat);
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
		double** acpyMat = (double**)malloc(n * sizeof(double*));
		for (i = 0; i < n; i++) acpyMat[i] = (double*)malloc(n * sizeof(double));
		for (i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				double** cplMat = (double**)malloc((n - 1) * sizeof(double*));
				for (k = 0; k < n - 1; k++) cplMat[k] = (double*)malloc((n - 1) * sizeof(double));
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
				for (k = 0; k < n - 1; k++) free(cplMat[k]);
				free(cplMat);
			}	
		return acpyMat;
	}
}

int main() {
	int m = 40000; // 影像比例尺
	double x_0 = 0, y_0 = 0, f = 153.24; // 内方位元素
	double** imgCoor; // 像点坐标
	double** groundCoor; // 地面坐标
	double minLimit = 0.000000001, minChange; // 限差
	int maxTryLimit = 400, tryTime = 0; // 迭代次数上限

	FILE* fp; // 文件句柄
	fp = fopen("data1.txt", "r");
	int N; // 控制点数
	int i, j; // 计数器
	fscanf(fp, "%d", &N);

	// 分配所有坐标所需的空间
	imgCoor = (double**)malloc(N * sizeof(double*));
	groundCoor = (double**)malloc(N * sizeof(double*));
	for (i = 0; i < N; i++) {
		imgCoor[i] = (double*)malloc(2 * sizeof(double));
		groundCoor[i] = (double*)malloc(3 * sizeof(double));
	}

	// 读取坐标
	for (i = 0; i < N; i++) {
		fscanf(fp, "%lf%lf", imgCoor[i], imgCoor[i] + 1);
		fscanf(fp, "%lf%lf%lf", groundCoor[i], groundCoor[i] + 1, groundCoor[i] + 2);
	}

	// 确定初始值
	double X_S, Y_S, Z_S; // 三个线外方位元素
	double phi = 0, omega = 0, kappa = 0; // 三个角外方位元素
	Z_S = m * f;
	for (i = 0; i < N; i++) X_S += groundCoor[i][0];
	X_S /= N;
	for (i = 0; i < N; i++) Y_S += groundCoor[i][1];
	Y_S /= N;

	// 迭代过程
	do {
		tryTime++;
		double** R = calcuRotateMat(phi, omega, kappa); //旋转矩阵
		double** calculatedCoor = calcuColineation(x_0, y_0, f, R, groundCoor, N, X_S, Y_S, Z_S); // 计算像点坐标近似值

		double** coefficientMat = calcuCoefficient(x_0, y_0, f, R, imgCoor, groundCoor, N, omega, kappa, X_S, Y_S, Z_S); // 计算系数矩阵
		double** transCoefficientMat = transpMat(coefficientMat, 2 * N, 6); // 系数矩阵转置
		double** constMat = (double**)malloc(2 * N * sizeof(double*)); // 计算常数矩阵
		for (i = 0; i < 2 * N; i++) constMat[i] = (double*)malloc(sizeof(double));
		for (i = 0; i < N; i++) {
			constMat[2 * i][0] = imgCoor[i][0] - calculatedCoor[i][0];
			constMat[2 * i + 1][0] = imgCoor[i][1] - calculatedCoor[i][1];
		}
		double** mulCoefficientMat = multipleMat(transCoefficientMat, coefficientMat, 6, 2 * N, 6);
		double** mulConstMat = multipleMat(transCoefficientMat, constMat, 6, 2 * N, 1);

		// 释放无用内存
		for (i = 0; i < 2 * N; i++) free(coefficientMat[i]);
		free(coefficientMat);
		for (i = 0; i < 6; i++) free(transCoefficientMat[i]);
		free(transCoefficientMat);
		for (i = 0; i < 3; i++) free(R[i]);
		free(R);
		for (i = 0; i < N; i++) free(calculatedCoor[i]);
		free(calculatedCoor);
		for (i = 0; i < N; i++) free(constMat[i]);
		free(constMat);

		// double* deltaMat = solEqual(mulCoefficientMat, 6, 6, mulConstMat); // 解方程
		double** inverseMat = calcuInverseMat(mulCoefficientMat, 6);
		double** deltaMat = multipleMat(inverseMat, mulConstMat, 6, 6, 1);
		X_S += deltaMat[0][0]; 
		Y_S += deltaMat[1][0]; 
		Z_S += deltaMat[2][0];
		phi += deltaMat[3][0];
		minChange = fabs(deltaMat[3][0]);
		omega += deltaMat[4][0];
		minChange = fabs(deltaMat[4][0]) > minChange ? minChange : fabs(deltaMat[4][0]);
		kappa += deltaMat[5][0];
		minChange = fabs(deltaMat[5][0]) > minChange ? minChange : fabs(deltaMat[5][0]);

		// 释放无用内存
		for (i = 0; i < 6; i++) free(mulCoefficientMat[i]);
		free(mulCoefficientMat);
		for (i = 0; i < 6; i++) free(mulConstMat[i]);
		free(mulConstMat);
		for (i = 0; i < 6; i++) free(inverseMat[i]);
		free(inverseMat);
		for (i = 0; i < 6; i++) free(deltaMat[i]);
		free(deltaMat);
	} while(minChange > minLimit && tryTime < maxTryLimit);

	printf("Xs: %.2lf, Ys: %.2lf, Zs: %.2lf\nphi: %.6lf, omega: %.6lf, kappa: %.6lf\n", X_S, Y_S, Z_S, phi, omega, kappa);
	for (i = 0; i < N; i++) {
		free(imgCoor[i]);
		free(groundCoor[i]);
	}
	free(imgCoor);
	free(groundCoor);
	return 0;
}