all: circuit-sim

circuit-sim: BasicCircuitSimulation.h
circuit-sim: CircuitSimulation.h
circuit-sim: SimpleSimulation.h
circuit-sim: Simulation.h
circuit-sim: main.cpp
	g++ -Wall -Wextra -Weffc++ -std=c++2a -o $@ main.cpp

clean:
	rm -f circuit-sim

