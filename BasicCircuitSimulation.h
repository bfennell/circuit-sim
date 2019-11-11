//
//  BasicCircuitSimulation.h
//  CircuitSim
//
//  Created by Brendan Fennell on 11.11.19.
//  Copyright © 2019 Brendan Fennell. All rights reserved.
//

#ifndef BasicCircuitSimulation_h
#define BasicCircuitSimulation_h

#include <cstdio>
#include <string>
#include <vector>

#include "Simulation.h"

class BasicCircuitSimulation : public Simulation {
public:
    virtual int inverter_delay() = 0;
    virtual int and_gate_delay() = 0;
    virtual int or_gate_delay() = 0;
    
    virtual ~BasicCircuitSimulation() {
    }
    
    class Wire {
    public:
        using Action = Simulation::Action;
        using ActionQueue = std::vector<Action>;
        
        bool get_signal() const {
            return sig_val;
        }
        
        void set_signal(const bool val) {
            if (sig_val != val) {
                sig_val = val;
                for (auto& action: actions) {
                    action();
                }
            }
        }
        
        void add_action(Action& action) {
            actions.insert(std::begin(actions),action);
            action();
        }

    private:
        bool sig_val{};
        ActionQueue actions{};
    };
    
    void inverter(Wire& input, Wire& out) {
        Action a([&]() {
            auto in_s = input.get_signal();
            after_delay(inverter_delay(), [in_s,&out]() {
                out.set_signal(!in_s);
            });
        });
        input.add_action(a);
    }

    void and_gate(Wire& in1, Wire& in2, Wire& out) {
        Action a([&]() {
            bool in1_s = in1.get_signal();
            bool in2_s = in2.get_signal();
            after_delay(and_gate_delay(), [in1_s,in2_s,&out]() {
                out.set_signal(in1_s && in2_s);
            });
        });
        in1.add_action(a);
        in2.add_action(a);
    }

    void or_gate(Wire& in1, Wire& in2, Wire& out) {
        Action a([&]() {
            bool in1_s = in1.get_signal();
            bool in2_s = in2.get_signal();
            after_delay(or_gate_delay(), [in1_s,in2_s,&out]() {
                out.set_signal(in1_s || in2_s);
            });
        });
        in1.add_action(a);
        in2.add_action(a);
    }

    void probe(const char* const name, Wire& wire) {
        Action a([&,name]() {
            printf("%s %d new-value = %d\n", name, getCurrentTime(), wire.get_signal());
        });
        wire.add_action(a);
    }
};

#endif /* BasicCircuitSimulation_h */
