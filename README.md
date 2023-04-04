# SIMPLE implementation in C++ 

## Overview 

Semi-Implicit Method for Pressure Linked Equations (SIMPLE) is an iterative solver for the Navier-Stokes equations. This implementation uses finite volume discretization, is steady-state and only supports laminar incompressible flow. I got started on implementing transient behavior and a K-epsilon turbulence model, together with other scalar transport functions almost two years ago, but had no time due to work, so I decided to upload it to GitHub. 

## Description 

The code creates a domain based on a set of boundaries specified in `boundaries.cpp`. It then iterates until convergence with `iterations.cpp`, alternating between estimation of velocities and pressures. 

## Results 

Geometries are expressed in simple, structured Cartesian grids. To make reasonable details, quite a few cells are needed, but the results can be pretty. 

<img src="https://raw.githubusercontent.com/NielsBongers/SIMPLE-CFD/main/Figures/Inverted%20C.png" width="400">

## Requirements 

The code requires [Eigen](https://eigen.tuxfamily.org/) for its matrices. All other requirements are standard. 

## Sources 

For implementation details, I recommend Versteeg's _An Introduction to Computational Fluid Dynamics_, Patankar's _Numerical Heat Transfer and Fluid Flow_, and Ferziger's _Computational Method for Fluid Dynamics_. 