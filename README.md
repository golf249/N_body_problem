# N-Body Gravitational Simulation

This project simulates the gravitational interactions between multiple celestial bodies using Newton's law of gravitation, implemented in C++ with a 4th-order Runge-Kutta (RK4) integration method.

## Overview

The program numerically solves a system of ordinary differential equations (ODEs) that describe the motion of **N** celestial bodies. These equations are integrated using the 4th-order Runge-Kutta method. Input data is read from a file, and the simulation results are saved to an output file.

## Features

- **N-body gravitational simulation**: Computes mutual gravitational forces between all bodies and updates their positions and velocities.
- **4th-order Runge-Kutta integration**: Accurately solves the system of ODEs over time.
- **File-based input/output**: Reads initial parameters from `parameters.txt` and writes simulation results to `output.txt`.
- **No user interaction**: The simulation runs automatically once started.

## Project Structure

- `main.cpp`: Contains the main function that sets up and runs the simulation.
- `nbody.cpp`: Implements the core logic of the simulation, including gravitational force calculations and the Runge-Kutta method.
- `nbody.h`: Header file that defines the `nbody` class and its methods.

## Input Format

The input file `parameters.txt` must be formatted as follows:

1. The first line contains values for the gravitational constant (`G`), total simulation time (`T`), and time step (`∆t`).
2. Each subsequent line provides the initial conditions for each body:
   - Initial position (`xi(0)`, `yi(0)`).
   - Initial velocity (`ẋi(0)`, `ẏi(0)`).
   - Mass (`mi`).

### Example Input

```plaintext
1.0 10.0 0.01
0.0 0.0 1.0 1.0 1.0
1.0 0.0 0.0 25.0 1.0
```
## Output Format

The output file `output.txt` records the positions and velocities of the bodies at each time step. Each line in the output contains:

```plaintext
body_index timestep x y x_velocity y_velocity
```

## How It Works

1. **Class `nbody`**:  
   The `nbody` class is defined in `nbody.h` and implemented in `nbody.cpp`. It handles:
   - Reading input from `parameters.txt`.
   - Computing gravitational forces and updating positions/velocities using the 4th-order Runge-Kutta method.
   - Writing the simulation results to `output.txt`.

2. **Key Methods**:
   - `simulate()`: Iterates through time steps and computes the positions and velocities of all bodies using the Runge-Kutta 4th-order method.
   - `computeAccX()` and `computeAccY()`: Compute the gravitational acceleration in the x and y directions for each body.
   - `printFile()`: Outputs the computed positions and velocities to `output.txt`.

## Compilation and Usage

1. **Compile the code**:  
   Use a standard C++ compiler to compile the program:

   ```bash
   g++ main.cpp nbody.cpp -o nbody_simulation
   ```

2. **Run the program**:  
   Place the `parameters.txt` file in the same directory as the executable and run the program:

   ```bash
   ./nbody_simulation
   ```
   
3. **Check the output**:  
   The simulation results will be saved in `output.txt`, containing the positions and velocities of the bodies over time.

## Additional Notes

After you have obtained the `output.txt` file, you can plot the trajectory of the bodies using any programming language of your choice, such as Python or MATLAB. Popular libraries for plotting include:

- **Python**: Use `matplotlib` to create 2D plots of the trajectories.
- **MATLAB**: Utilize built-in plotting functions to visualize the motion of the bodies.

These plots can help you analyze the motion and interactions of the celestial bodies over time.

