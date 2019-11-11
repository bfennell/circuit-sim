//
//  CircuitSimulation.h
//  CircuitSim
//
//  Created by Brendan Fennell on 11.11.19.
//  Copyright © 2019 Brendan Fennell. All rights reserved.
//

#ifndef CircuitSimulation_h
#define CircuitSimulation_h

#include <memory>
#include <vector>

#include "BasicCircuitSimulation.h"

class CircuitSimulation : public BasicCircuitSimulation {
public:
    using Wire = BasicCircuitSimulation::Wire;

    virtual int inverter_delay() override { return 1; };
    virtual int and_gate_delay() override { return 3; };
    virtual int or_gate_delay() override { return 5; };

    Wire& make_wire() {
        auto w_ = std::make_unique<Wire>();
        Wire* w = w_.get();
        wires.push_back(std::move(w_));
        return *w;
    }

    void half_adder(Wire& a, Wire& b, Wire& s, Wire& c) {
        Wire& d = make_wire();
        Wire& e = make_wire();
        
        or_gate(a, b, d);
        and_gate(a, b, c);
        inverter(c, e);
        and_gate(d, e, s);
    }

    void full_adder(Wire& a, Wire& b, Wire& cin, Wire& sum, Wire& cout) {
        Wire& s = make_wire();
        Wire& c1 = make_wire();
        Wire& c2 = make_wire();

        half_adder(a, cin, s, c1);
        half_adder(b, s, sum, c2);
        or_gate(c1, c2, cout);
    }

private:
    std::vector<std::unique_ptr<Wire>> wires{};
};

#endif /* CircuitSimulation_h */
