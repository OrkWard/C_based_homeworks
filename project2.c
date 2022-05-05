#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926535

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

// 复制矩阵
double** copyMat(double** mat, int row, int col) {
    int i, j;
    double **newMat = (double**)malloc(row * sizeof(double*));
    for (i = 0; i < row; i++) newMat[i] = (double*)malloc(col * sizeof(double));
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            newMat[i][j] = mat[i][j];
    return newMat;
}

// 计算旋转矩阵
double** calcuRMat(double phi, double omega, double kappa) {
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
    double phi = 0, omega = 0, kappa = 0, mu = 0, nu = 0;   // 5个相对定向元素
    int i, j;                                               // 计数器
    double minLimit = 0.000001, minChange;                  // 限差

    FILE* fp;                                               // 文件句柄
    int N;                                                  // 同名像点数
    double **left, **right;                                 // 左片和右片影像坐标矩阵
    fp = fopen("./data2.txt", "r");
    fscanf(fp, "%d", &N);
    left = (double**)malloc(N * sizeof(double*));
    right = (double**)malloc(N * sizeof(double*));
    for(i = 0; i < N; i++) {
        left[i] = (double*)malloc(3 * sizeof(double));
        fscanf(fp, "%lf%lf", left[i], left[i] + 1);
        left[i][2] = -24;
        right[i] = (double*)malloc(3 * sizeof(double));
        fscanf(fp, "%lf%lf", right[i], right[i] + 1);
        right[i][2] = -24;
    }
    fclose(fp);

    do {
        double **R, **R1, **R2;
        double **AMat, **LMat;                              // 各矩阵
        AMat = (double**)malloc(N * sizeof(double*));
        LMat = (double**)malloc(N * sizeof(double*));
        for (i = 0; i < N; i++) {
            AMat[i] = (double*)malloc(5 * sizeof(double));
            LMat[i] = (double*)malloc(sizeof(double));
        }                                                   // 初始化法方程矩阵

        /* 计算系数矩阵和常数矩阵 */
        R = calcuRMat(phi, omega, kappa);                   // 计算旋转矩阵
        for (i = 0; i < N; i++) {
            R1 = transpMat(left + i, 1, 3);                   // 计算X1，Y1，Z1
            double **transRight = transpMat(right + i, 1, 3);
            R2 = multipleMat(R, transRight, 3, 3, 1);        // 计算X2，Y2，Z2
            double N, NPrime, Q, *B;
            B = (double*)malloc(3 * sizeof(double));
            B[0] = 5.185;
            B[1] = B[0] * mu;
            B[2] = B[0] * nu;
            N = (B[0]*R2[2][0] - B[2]*R2[0][0]) / (R1[0][0]*R2[2][0] - R1[2][0]*R2[0][0]);
            NPrime = (B[0]*R1[2][0] - B[2]*R1[0][0]) / (R1[0][0]*R2[2][2] - R1[2][0]*R2[0][0]);
            Q = N*R1[1][0] - NPrime*R2[1][0] - B[1];

            AMat[i][0] = -R2[0][0] * R2[1][0] * NPrime / R2[2][0];
            AMat[i][1] = -(R2[2][0] + R2[1][0]*R2[1][0]/R2[2][0]);
            AMat[i][2] = R2[0][0] * NPrime;
            AMat[i][3] = B[0];
            AMat[i][4] = -R2[1][0] * R2[2][0] / B[0];
            LMat[i][0] = Q;

            free(B);
            for (j = 0; j < 3; i++) {
                free(R1[j]);
                free(R2[j]);
                free(transRight[j]);
            }
            free(R1); free(R2); free(transRight);
        }

        double **ATMat = transpMat(AMat, N, 5);             // 系数矩阵转置
        double **ATAMat = multipleMat(ATMat, AMat, 5, N, 5);
        double **inverATAMat = calcuInverseMat(ATAMat, 5);
        double **constMat = multipleMat(ATMat, LMat, 5, N, 1);       
        double **delta = multipleMat(inverATAMat, constMat, 5, 5, 1);// 改正数矩阵

        minChange = fabs(delta[0][0]);
        phi += delta[0][0];
        minChange = minChange > fabs(delta[1][0]) ? fabs(delta[1][0]) : minChange;
        omega += delta[1][0];
        minChange = minChange > fabs(delta[2][0]) ? fabs(delta[2][0]) : minChange;
        kappa += delta[2][0];
        minChange = minChange > fabs(delta[3][0]) ? fabs(delta[3][0]) : minChange;
        mu += delta[3][0];
        minChange = minChange > fabs(delta[4][0]) ? fabs(delta[4][0]) : minChange;
        nu += delta[4][0];

        for (i = 0; i < 3; i++) free(R[i]); free(R);
        for (i = 0; i < N; i++) {
            free(AMat[i]);
            free(LMat[i]);
        }
        free(AMat); free(LMat);
        for (i = 0; i < 5; i++) {
            free(ATMat[i]);
            free(ATAMat[i]);
            free(inverATAMat[i]);
            free(constMat[i]);
            free(delta[i]);
        }
        free(ATMat); free(ATAMat); free(inverATAMat); free(constMat); free(delta);
    } while(minChange > minLimit);

    for (i = 0; i < N; i++) {
        free(left[i]);
        free(right[i]);
    }
    free(left); free(right);
    
    printf("%.6lf %.6lf %.6lf %.6lf %.6lf\n", phi, omega, kappa, mu, nu);
    return 0;
}