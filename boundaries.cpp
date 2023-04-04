#include "SIMPLE.h"

void SIMPLE::setVelocityBoundaryConditions(Eigen::MatrixXd& uIn, Eigen::MatrixXd& vIn) {

    for (int j = 0; j < N; j++) {
        uIn(0, j) = 0;
        vIn(0, j) = 0;
        vIn(M - 1, j) = 0;
    }

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                uIn(i, j) = 0;
                vIn(i, j) = 0;
            }
        }
    }

    for (int j = 0; j < N; j++) {
        uIn(0, j) = 0;
        uIn(M, j) = 1;
    }

    for (int i = 0; i < M; i++) {
        uIn(i, 0) = 1;
        uIn(i, N - 1) = uIn(i, N - 2);

        vIn(i, 0) = 0;
        vIn(i, N) = 0;
    }
}

void SIMPLE::setPressureBoundaryConditions(Eigen::MatrixXd& pIn) {

    for (int j = 1; j < N + 1; j++) {
        pIn(0, j) = pIn(1, j);
        pIn(M, j) = pIn(M - 1, j);
    }

    for (int i = 1; i < M + 1; i++) {
        pIn(i, 0) = pIn(i, 1);
        pIn(i, N) = pIn(i, N - 1);
    }
}

double SIMPLE::checkBoundaries(int i, int j) {

    double boundaryCondition = 0;

    if (j >= 30 && j <= 40 && i <= 20) {
        boundaryCondition = 1;
    }

    return boundaryCondition;
}