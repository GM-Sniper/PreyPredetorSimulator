# Predator-Prey Simulation

## Overview

The goal of this Programming Project is to create a simple two-dimensional predator-prey simulation. In this simulation, the prey are ants and the predators are doodlebugs. These critters live in a world composed of a 20 × 20 grid of cells. Only one critter may occupy a cell at a time. The grid is enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. Each critter performs some action every time step.

## Ant Behavior

- **Move:** Every time step, ants randomly try to move up, down, left, or right. If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.

- **Breed:** If an ant survives for three time steps, it will breed, creating a new ant in an adjacent empty cell. If no empty cells are available, no breeding occurs. An ant cannot produce an offspring until three more time steps have elapsed.

## Doodlebug Behavior

- **Move:** Every time step, doodlebugs move to an adjacent cell with an adjacent ant (up, down, left, or right) to eat the ant. If no adjacent ants are present, doodlebugs move according to the same rules as ants. Doodlebugs cannot eat other doodlebugs.

- **Breed:** If a doodlebug survives for eight time steps, it will spawn a new doodlebug in the same manner as the ant.

- **Starve:** If a doodlebug has not eaten an ant within the last three time steps, it will starve and die, and be removed from the grid of cells.

## Implementation

Write a program to implement this simulation and draw the world using ASCII characters: "o" for an ant and "X" for a doodlebug. Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. This class should have a pure virtual function named `move` that is defined in the derived classes of Ant and Doodlebug. You may need additional data structures to keep track of which critters have moved.

## Initial Population

Initialize the world with 5 doodlebugs and 100 ants.

## Usage

After each time step, prompt the user to press Enter to move to the next time step. You should see a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
