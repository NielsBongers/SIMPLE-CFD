#include "SIMPLE.h"

double SIMPLE::calculateStep() {
    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N - 1; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            double Fe = 0.5 * rho * (u(i, j) + u(i, j + 1)) * hx;
            double Fw = 0.5 * rho * (u(i, j) + u(i, j - 1)) * hx;
            double Fn = 0.5 * rho * (v(i - 1, j) + v(i - 1, j + 1)) * hy;
            double Fs = 0.5 * rho * (v(i, j) + v(i, j + 1)) * hy;

            double Pe = Fe / D;

            if (abs(Pe) > 1) {
                //std::cout << Pe << std::endl;
            }
            //double aE = -0.5 * Fe + D;
            //double aW = 0.5 * Fw + D;
            //double aN = -0.5 * Fn + D;
            //double aS = 0.5 * Fs + D;

            //double aE = D + takeMax(0, -Fe);
            //double aW = D + takeMax(0, Fw); 
            //double aN = D + takeMax(0, -Fn); 
            //double aS = D + takeMax(0, Fs); 

            double aE = takeMax(-Fe, D - 0.5 * Fe, 0);
            double aW = takeMax(Fw, D + 0.5 * Fw, 0);
            double aN = takeMax(-Fn, D - 0.5 * Fn, 0);
            double aS = takeMax(Fs, D + 0.5 * Fs, 0);

            double aP = (aW + aE + aN + aS + Fe - Fw + Fn - Fs);

            double Ae = -hx;

            dE(i, j) = Ae / aP;

            uStar(i, j) = (aE * u(i, j + 1) + aW * u(i, j - 1) + aN * u(i - 1, j) + aS * u(i + 1, j)) / aP + dE(i, j) * (p(i, j + 1) - p(i, j));

        }
    }

    for (int i = 1; i < M - 1; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            double Fe = 0.5 * rho * (u(i, j) + u(i + 1, j)) * hx;
            double Fw = 0.5 * rho * (u(i, j - 1) + u(i + 1, j - 1)) * hx;
            double Fn = 0.5 * rho * (v(i - 1, j) + v(i, j)) * hy;
            double Fs = 0.5 * rho * (v(i, j) + v(i + 1, j)) * hy;

            //double aE = -0.5 * Fe + D;
            //double aW = 0.5 * Fw + D;
            //double aN = -0.5 * Fn + D;
            //double aS = 0.5 * Fs + D;

            ////double aE = D + takeMax(0, -Fe);
            ////double aW = D + takeMax(0, Fw);
            ////double aN = D + takeMax(0, -Fn);
            ////double aS = D + takeMax(0, Fs);

            double aE = takeMax(-Fe, D - 0.5 * Fe, 0);
            double aW = takeMax(Fw, D + 0.5 * Fw, 0);
            double aN = takeMax(-Fn, D - 0.5 * Fn, 0);
            double aS = takeMax(Fs, D + 0.5 * Fs, 0);

            double aP = (aW + aE + aN + aS + Fe - Fw + Fn - Fs);

            double An = -hy;

            dN(i, j) = An / aP;

            vStar(i, j) = (aE * v(i, j + 1) + aW * v(i, j - 1) + aN * v(i - 1, j) + aS * v(i + 1, j)) / aP + dN(i, j) * (p(i, j) - p(i + 1, j));
        }
    }

    setVelocityBoundaryConditions(uStar, vStar);

    pStar = Eigen::MatrixXd::Zero(M + 1, N + 1);

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            double aE = -rho * dE(i, j) * hx;
            double aW = -rho * dE(i, j - 1) * hx;
            double aN = -rho * dN(i - 1, j) * hy;
            double aS = -rho * dN(i, j) * hy;

            double aP = aE + aW + aN + aS;

            b(i, j) = -rho * (uStar(i, j) - uStar(i, j - 1)) * hx + rho * (vStar(i, j) - vStar(i - 1, j)) * hy;


            pStar(i, j) = (aE * pStar(i, j + 1) + aW * pStar(i, j - 1) + aN * pStar(i - 1, j) + aS * pStar(i + 1, j) + b(i, j)) / aP;
        }
    }

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            p(i, j) = p(i, j) + pAlpha * pStar(i, j);
        }
    }

    setPressureBoundaryConditions(p);

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N - 1; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            u(i, j) = uStar(i, j) + uvAlpha * dE(i, j) * (pStar(i, j + 1) - pStar(i, j));
        }
    }

    for (int i = 1; i < M - 1; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            v(i, j) = vStar(i, j) + uvAlpha * dN(i, j) * (pStar(i, j) - pStar(i + 1, j));
        }
    }

    setVelocityBoundaryConditions(u, v);

    double error = 0;

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {

            if (checkBoundaries(i, j) == 1) {
                continue;
            }

            error += abs(b(i, j));
        }
    }

    return error;
}