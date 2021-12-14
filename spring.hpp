#include <simlib.h>
#include <math.h>
const double wait[4] = {0.16, 0.17, 0.15, 0.17};

Store AssemblyMachines(4); //4->5  
Store ClinchingTables(5);

//infinite production of coils from raw metal
int actualCoils = 0;            //coils in one specific moment
int producedCoils = 0;          //total created during simulation

//chassis from assemblying coils
int totalChassis = 0;

//frames to clinching table
int producedFrames = 0;
int actualFrames = 0;

//finished product of this district
int actualSemiFinishedBonnels = 0;   
int totalSemiFinishedBonnels = 0;


class Chassis: public Process{
    //production of 100x200cm chassis
    public:
        void Behavior(){
            AssemblyProcess();
            
            //take two frames and a chassis for semi finished bonnel
            while (actualFrames < 2)
            {
               1;
            }
            actualFrames = actualFrames - 2;
            ClinchingProcess();
        
            //Add to semi-finished bonnels store
            actualSemiFinishedBonnels++;
            totalSemiFinishedBonnels++;
        }

        void AssemblyProcess(){
            Enter(AssemblyMachines, 1);
            Wait(Triag(3,4.35,5.13));
            Leave(AssemblyMachines, 1);
            totalChassis++;
            
            return;
        }

        void ClinchingProcess(){
            Enter(ClinchingTables,1);
            Wait(Beta(1.32, 8.4, 3.0, 9.07));
            Leave(ClinchingTables, 1);
        }

};

class CoilWire : public Process{
    void Behavior(){
        double t = Time;
        actualCoils++;
        producedCoils++;
        if (actualCoils >= 25)
        {
            actualCoils = actualCoils - 25;
            (new Chassis) -> Activate(Time);
        }
        
    }
};

class Coil1Gen : public Event{
    void Behavior(){
        (new CoilWire) -> Activate();   
        Activate(Time + wait[0]);
    }
};
class Coil2Gen : public Event{
    void Behavior(){
        (new CoilWire) -> Activate();     
        Activate(Time + wait[1]);
    }
};
class Coil3Gen : public Event{
    void Behavior(){
        (new CoilWire) -> Activate();     
        Activate(Time + wait[2]);
    }
};
class Coil4Gen : public Event{
    void Behavior(){
        (new CoilWire) -> Activate();     
        Activate(Time + wait[3]);
    }
};

class Frame: public Process{
    void Behavior(){
        producedFrames++;
        actualFrames++;
    }
};

class FrameBendingMachine: public Event{
    void Behavior(){
        (new Frame)->Activate();
        Activate(Time+std::abs(Normal(0.452,0.11)));
    }
};

