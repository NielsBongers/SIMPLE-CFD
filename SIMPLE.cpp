#include "SIMPLE.h"

SIMPLE::SIMPLE() {

    uStar = Eigen::MatrixXd::Zero(M + 1, N);
    vStar = Eigen::MatrixXd::Zero(M, N + 1);
    pStar = Eigen::MatrixXd::Zero(M + 1, N + 1);

    u = Eigen::MatrixXd::Zero(M + 1, N);
    v = Eigen::MatrixXd::Zero(M, N + 1);
    p = Eigen::MatrixXd::Zero(M + 1, N + 1);

    b = Eigen::MatrixXd::Zero(M + 1, N + 1);
    dE = Eigen::MatrixXd::Zero(M + 1, N);
    dN = Eigen::MatrixXd::Zero(M, N + 1);

    uvAbs = Eigen::MatrixXd::Zero(M + 1, N + 1);
    
    u(1, 1) = 1; 
    p(M, N) = 1;

}

void SIMPLE::runIterations() {
    int numberIterations = 0;
    double error = 1;

    std::ofstream diagnosticsFile; 
    diagnosticsFile.open("Convergence.txt"); 

    while (error > epsilon && numberIterations < maxIterations) {
        error = calculateStep();

        if (numberIterations % 1000 == 0) {
            std::cout << "Iteration " << numberIterations << "\t Error = " << error << std::endl;
            diagnosticsFile << numberIterations << "\t" << error << std::endl; 
        }

        if (numberIterations % 5000 == 0) {
            saveAll(); 
        }

        numberIterations += 1;
    }
    saveAll(); 
}


int main()
{

    SIMPLE CFD;
    CFD.runIterations();

}
