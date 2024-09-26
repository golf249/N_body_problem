#include "nbody.h"

// class constructor
// all the data like the initial conditions are initialised in the constructor
nbody::nbody(string& fileName)
{
    //read data from paramater.txt text file
    ifstream file(fileName);
    //check if file opened correctly
    if (file.good()) {
        file >> G >> T >> dt;					// store data from file into variables
        Final_cycle = T/dt;						// calculate the number of cycle in the system
        double vTemp1, vTemp2, vTemp3, vTemp4, vTemp5;				// creating a temporary variables to store content of the file
        while (true) {
            file >> vTemp1 >> vTemp2 >> vTemp3 >> vTemp4 >> vTemp5;		// store data from file into variables
			// append all the temporary variables into a vector that stores all the data
            xTotal.push_back(vector<double> {vTemp1});
            yTotal.push_back(vector<double> {vTemp2});
            dxTotal.push_back(vector<double> {vTemp3});
            dyTotal.push_back(vector<double> {vTemp4});
            m.push_back(vTemp5);
            ++N;				// counts the number of bodies in the system
            if (file.eof()){
                break;			// if the end of file is reached end the loop
            }
        } 
        
    } else {
        cout << "Failed to open file" << endl;			// when file fails to open, output an error message
    }
    file.close();
}

// this function calculates all the values for positions and velocities into a vector for all timestep
void nbody::simulate()
{
    for (int time = 0; time <= Final_cycle; ++time) {		// iterate through the time period T with timestep dt
        for (int i = 0; i < N; ++i) {						// iterate through the number of bodies
            rungeKutta4(i, time);          					// compute values using RK4
        }
    }
}

// this function outputs all the values into the textfile called 'output.txt'
// the format of each line is: i | timestep | x | y | dx | dy
void nbody::printFile()
{
    simulate();							// runs the RK4 function for every time step and bodies
    ofstream outputFile("output.txt", ios::out | ios::trunc);		//create an output file which stores all the required values
    for (int i = 0; i < N; i++) {
        double timestep = 0.0;
        for (int time = 0; time <= Final_cycle; ++time) {
            outputFile << i + 1 << " " << timestep << " " << xTotal[i][time] << " " << yTotal[i][time] << " " << dxTotal[i][time] << " " << dyTotal[i][time] << endl;
            timestep += dt;
        }
    }
    outputFile.close();
}

// this function calculates the acceleration in the x direction given the argument
double nbody::computeAccX(double x, double y, int i, int cycle)
{
	// initialise the distance between bodies and the acceleration
    double d_ij = 0.0;
    double totalx = 0.0;
	// iterates through the number of bodies except for its own
    for (int j = 0; j < N; ++j) {
        if (i != j) {
			// acceleration calulated using equation 1
            d_ij = sqrt(pow(x - xTotal[j][cycle], 2.0) + pow(y - yTotal[j][cycle], 2.0));
            totalx += G * (m[j]/pow(d_ij,3.0)) * (xTotal[j][cycle] - x);
        }
    }
    return (totalx);			// returns the acceleration caused by all the bodies
}

// this function calculates the acceleration in the y direction given the argument
double nbody::computeAccY(double x, double y, int i, int cycle)
{
	// initialise the distance between bodies and the acceleration	
    double d_ij = 0.0;
    double totaly = 0.0;
	// iterates through the number of bodies except for its own
    for (int j = 0; j < N; ++j) {
        if (i != j) {
			// acceleration calulated using equation 1			
            d_ij = sqrt(pow(x - xTotal[j][cycle], 2.0) + pow(y - yTotal[j][cycle], 2.0));
            totaly += G * (m[j]/pow(d_ij,3.0)) * (yTotal[j][cycle] - y);
        }
    }
    return (totaly);			// returns the acceleration caused by all the bodies
}

// this function performs the 4th order Runge-Kutta
void nbody::rungeKutta4(int i, int cycle) 
{
	// k1 k2 k3 k4 values are calculated using the 4th order Runge-Kutta equation but are seperated into its x y dx dy components
    double k1x = dxTotal[i][cycle]; 
    double k1y = dyTotal[i][cycle];
    double k1dx = computeAccX(xTotal[i][cycle], yTotal[i][cycle], i, cycle);
    double k1dy = computeAccY(xTotal[i][cycle], yTotal[i][cycle], i, cycle);

    double k2x = (dxTotal[i][cycle] + (dt * k1dx/2.0)); 
    double k2y = (dyTotal[i][cycle] + (dt * k1dy/2.0));
    double k2dx = (computeAccX(xTotal[i][cycle] + (dt * k1x/2.0), yTotal[i][cycle] + (dt * k1y/2.0), i, cycle));
    double k2dy = (computeAccY(xTotal[i][cycle] + (dt * k1x/2.0), yTotal[i][cycle] + (dt * k1y/2.0), i, cycle));

    double k3x = (dxTotal[i][cycle] + (dt * k2dx/2.0)); 
    double k3y = (dyTotal[i][cycle] + (dt * k2dy/2.0));
    double k3dx = (computeAccX(xTotal[i][cycle] + (dt * k2x/2.0), yTotal[i][cycle] + (dt * k2y/2.0), i, cycle));
    double k3dy = (computeAccY(xTotal[i][cycle] + (dt * k2x/2.0), yTotal[i][cycle] + (dt * k2y/2.0), i, cycle));

    double k4x = (dxTotal[i][cycle] + dt * k3dx); 
    double k4y = (dyTotal[i][cycle] + dt * k3dy);
    double k4dx = (computeAccX(xTotal[i][cycle] + dt * k3x, yTotal[i][cycle] + dt * k3y, i, cycle));
    double k4dy = (computeAccY(xTotal[i][cycle] + dt * k3x, yTotal[i][cycle] + dt * k3y, i, cycle));    

	// store the new values of x y dx and dy values into a new variable
    double NewX = xTotal[i][cycle] + dt * (k1x + (k2x + k3x) * 2.0 + k4x)/6.0;
    double NewY = yTotal[i][cycle] + dt * (k1y + (k2y + k3y) * 2.0 + k4y)/6.0;
    double NewDx = dxTotal[i][cycle] + dt * (k1dx + (k2dx + k3dx) * 2.0 + k4dx)/6.0;
    double NewDy = dyTotal[i][cycle] + dt * (k1dy + (k2dy + k3dy) * 2.0 + k4dy)/6.0;
	
	// append all these new variable into a vector of a vector for that body
    xTotal[i].push_back(NewX);
    yTotal[i].push_back(NewY);
    dxTotal[i].push_back(NewDx);
    dyTotal[i].push_back(NewDy);
}