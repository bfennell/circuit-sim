//
//  SimpleSimulation.h
//  CircuitSim
//
//  Created by Brendan Fennell on 11.11.19.
//  Copyright © 2019 Brendan Fennell. All rights reserved.
//

#ifndef SimpleSimulation_h
#define SimpleSimulation_h

#include "CircuitSimulation.h"

class SimpleSimulation : public CircuitSimulation {
public:
    using Wire = CircuitSimulation::Wire;
    
    void execute() {
        Wire& in1 = make_wire();
        Wire& in2 = make_wire();
        Wire& sum = make_wire();
        Wire& carry = make_wire();
        
        probe("sum", sum);
        probe("carry", carry);
        
        half_adder(in1, in2, sum, carry);
        
        for(int i = 0; i < 1; ++i) {
        in1.set_signal(true);
        run();
        
        in2.set_signal(true);
        run();
        }
    }
};

#endif /* SimpleSimulation_h */
