#pragma once

#pragma once

#include <iostream>
#include <fstream>
#include <math.h>
#include "../Eigen/Eigen/Sparse"
#include "../Eigen/Eigen/Dense"
#include "../Eigen/Eigen/SparseCholesky"
#include "../Eigen/Eigen/IterativeLinearSolvers"

class SIMPLE {

public: 

	// Variables
	
	double epsilon = pow(10, -5); 
	int maxIterations = (int)pow(10, 9); 
	
	int M = 100;    // y
	int N = 300;    // x 

	double ySize = 1; 
	double xSize = 1; 
	
	double hy = ySize / (M-1);
	double hx = xSize / (N-1); 

	double eta = 1; 
	double rho = 1; 

	//double D = eta / (hx/2.) * hy;
	double D = 0.1; 

	double uvAlpha = 0.7; 
	double pAlpha = 0.7; 

	// Matrices
	Eigen::MatrixXd uStar; 
	Eigen::MatrixXd vStar;
	Eigen::MatrixXd pStar;
	Eigen::MatrixXd u;
	Eigen::MatrixXd v;
	Eigen::MatrixXd p;

	Eigen::MatrixXd b;

	Eigen::MatrixXd dE;
	Eigen::MatrixXd dN;

	Eigen::MatrixXd uvAbs; 

	// Functions
	SIMPLE(); 
	void runIterations(); 
	void setVelocityBoundaryConditions(Eigen::MatrixXd& u, Eigen::MatrixXd& v);
	void setPressureBoundaryConditions(Eigen::MatrixXd& p); 
	double takeMax(double A, double B); 
	double takeMax(double A, double B, double C);
	double checkBoundaries(int i, int j); 
	void paintBoundaries(); 
	void calculateShear(); 
	double calculateStep(); 
	void saveMatrix(Eigen::MatrixXd inputMatrix, std::string fileName);
	void saveAll(); 
};