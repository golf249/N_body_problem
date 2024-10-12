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

