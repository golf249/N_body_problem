#ifndef NBODY_H
#define NBODY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
// Nbody class
class nbody
{
    private:
        double G;					// gravitational constant
        double T;					// time period
        double dt;					// time step
        int N = 0;					// number of bodies
        double Final_cycle;			// the total number cycle
        vector<double> m;			// vector storing all the mass of each bodies
        vector<vector<double>> xTotal, yTotal, dxTotal, dyTotal;	// vector of a vector to store all the positions and velocities as well as the timestep

		// functions to compute all the position and velocities
        double computeAccX(double x, double y, int i, int cycle);
        double computeAccY(double x, double y, int i, int cycle);
        void rungeKutta4(int i, int cycle);

    public:
        nbody(string& fileName);	// constructor
		
        void simulate();			// function to compute all the position and velocities for all timesteps
        void printFile();			// output the content computed using RK4 into a text file
};

#endif // NBODY_H