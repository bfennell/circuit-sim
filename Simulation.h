//
//  Simulation.h
//  CircuitSim
//
//  Created by Brendan Fennell on 11.11.19.
//  Copyright © 2019 Brendan Fennell. All rights reserved.
//

#ifndef Simulation_h
#define Simulation_h

#include <cstdio>
#include <functional>
#include <vector>

class Simulation {
public:
    using Action = std::function<void(void)>;
    
    struct Event {int time{}; Action action{}; };
    
    using EventQueue = std::vector<Event>;
    
    int getCurrentTime() const {
        return currentTime;
    }
    
    void after_delay(const int delay, Action action) {
        insert({currentTime + delay, action});
    }
    
    void run() {
        after_delay(0, [&](){
            printf("*** simulation started, time = %d\n", currentTime);
        });
        
        while(!evtq.empty()) {
            next();
        }
    }
private:
    int currentTime{};
    EventQueue evtq{};
    
    void next() {
        if (evtq.size() > 0) {
            Event e {evtq.front()};
            evtq.erase(std::begin(evtq));
            currentTime = e.time;
            e.action();
        }
    }
    
    void insert(const Event& e) {
        const int time = e.time;
        auto it = std::find_if(std::begin(evtq), std::end(evtq), [time](const Event& e) {
            return time < e.time;
        });
    
        evtq.insert(it, e);
    }
};

#endif /* Simulation_h */
