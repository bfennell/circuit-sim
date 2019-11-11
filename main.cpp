//
//  main.cpp
//  CircuitSim
//
//  Created by Brendan Fennell on 11.11.19.
//  Copyright © 2019 Brendan Fennell. All rights reserved.
//

#include <iostream>
#include <stdexcept>

#include "SimpleSimulation.h"

int main(int, const char**) {
    try {
        SimpleSimulation sim;
        
        sim.execute();
        
        return 0;
    } catch (std::exception& e) {
        printf("exception: %s\n", e.what());
        return -1;
    }
    
    return 0;
}
