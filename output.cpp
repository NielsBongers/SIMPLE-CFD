#include "SIMPLE.h"

void SIMPLE::paintBoundaries() {

    Eigen::MatrixXd BCs = Eigen::MatrixXd::Zero(M, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            BCs(i, j) = checkBoundaries(i, j);
        }
    }

    saveMatrix(BCs, "BC");
}

void SIMPLE::saveMatrix(Eigen::MatrixXd inputMatrix, std::string fileName) {

    std::ofstream file;

    file.open(fileName + ".txt");

    //for (int i = 0; i < M; i++) {
    //    for (int j = 0; j < N; j++) {

    //        u(i, j) = 0.5 * (u(i, j) + u(i + 1, j));
    //        v(i, j) = 0.5 * (v(i, j) + v(i, j + 1));
    //    }
    //}

    //for (int i = 0; i < M; i++) {
    //    for (int j = 0; j < N; j++) {
    //        uvAbs(i, j) = sqrt(u(i, j) * u(i, j) + v(i, j) * v(i, j));
    //    }
    //}

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            file << "\t" << inputMatrix(i, j);
        }
        file << std::endl;
    }
}

void SIMPLE::saveAll() {

    Eigen::MatrixXd uOut = u; 
    Eigen::MatrixXd vOut = v;
    Eigen::MatrixXd pOut = p;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            uOut(i, j) = 0.5 * (u(i, j) + u(i + 1, j));
            vOut(i, j) = 0.5 * (v(i, j) + v(i, j + 1));
            pOut(i, j) = 0.25 * (p(i, j) + p(i, j + 1), p(i + 1, j) + p(i + 1, j + 1)); 
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            pOut(i, j) = 0.25 * (p(i, j) + p(i, j + 1), p(i + 1, j) + p(i + 1, j + 1));
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            uvAbs(i, j) = sqrt(u(i, j) * u(i, j) + v(i, j) * v(i, j));
        }
    }

    saveMatrix(uOut, "u");
    saveMatrix(vOut, "v");
    saveMatrix(pOut, "p");
    saveMatrix(uvAbs, "speed");

}