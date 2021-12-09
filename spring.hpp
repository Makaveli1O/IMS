#include <simlib.h>
#include <math.h>
const double wait[4] = {0.016, 0.017, 0.015, 0.017};

Store AssemblyMachines(4);  
Store ClinchingTables(5);

//infinite production of coils from raw metal
int actualCoils = 0;            //coils in one specific moment
int producedCoils = 0;          //total created during simulation

//chassis from assemblying coils
int chassisCounter = 0;

//frames to clinching table
int producedFrames = 0;
int actualFrames = 0;

//finished product of this district
int semiFinishedBonnels = 0;   


class Chassis: public Process{
    //production of 100x200cm chassis
    int coilsForChassis = 25;
    public:
        void Behavior(){
            AssemblyProcess();
            

            //take two frames
            while (actualFrames < 2)
            {
               1;
            }
            
            //use 1 frame for chassis
            actualFrames = actualFrames - 2;
            
            ClinchingProcess();
            //Add to semi-finished bonnels store
            semiFinishedBonnels++;
        }

        void AssemblyProcess(){
            Enter(AssemblyMachines, 1);
            Wait(Triag(3,4.35,5.13));
            Leave(AssemblyMachines, 1);
            chassisCounter++;
            actualCoils = actualCoils - coilsForChassis;
            return;
        }

        void ClinchingProcess(){
            Enter(ClinchingTables,1);
            Beta(1.32, 8.4, 3.0, 9.07);
            Leave(ClinchingTables, 1);
        }

};

class Coil : public Process{
    void Behavior(){
        actualCoils++;
        producedCoils++;
        if (actualCoils >= 25)
        {
            (new Chassis) -> Activate(Time);
        }
        
    }
};

class Coil1Gen : public Event{
    void Behavior(){
        (new Coil) -> Activate();   
        Activate(Time + wait[0]);
    }
};
class Coil2Gen : public Event{
    void Behavior(){
        (new Coil) -> Activate();     
        Activate(Time + wait[1]);
    }
};
class Coil3Gen : public Event{
    void Behavior(){
        (new Coil) -> Activate();     
        Activate(Time + wait[2]);
    }
};
class Coil4Gen : public Event{
    void Behavior(){
        (new Coil) -> Activate();     
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
