#include "spring.hpp"
#include "sewing.hpp"

Store PaddingTables(7); // 7 - > 10
Store TapingMachines(9); // 9 -> 6
Store PackingMachines(2); //2 -> 1

int mattress = 0;

class Packing : public Process{
    void Behavior(){
        Enter(PackingMachines, 1);
        Wait(_Weibull(11.7, 0.338));
        Leave(PackingMachines, 1);
        //finished and packed mattress
        mattress++;
    }
};

class Taping : public Process{
    void Behavior(){
        Enter(TapingMachines, 1);
        Wait(4+_Weibull(2.0, 3.46));
        Leave(TapingMachines, 1);
        (new Packing) -> Activate();
    }
};

class Padding : public Process{
    void Behavior(){
        Enter(PaddingTables, 1);
        Wait(Beta(1.8, 1.38, 12, 15));
        Leave(PaddingTables, 1);
        //after padding subtract actual number since they no longer exist indepentendly
        //rather are padded mattress
        panelCounter--;
        borderCounter--;
        actualSemiFinishedBonnels--;
        (new Taping) -> Activate();
    }
};

class BuildUp : public Process{
    public:
        void Behavior(){
            if (panelCounter > 0 && borderCounter > 0 && actualSemiFinishedBonnels > 0){
                (new Padding) -> Activate();
            }
        }
};

class MatressBuildUp : public Event{
    void Behavior(){
        (new BuildUp) -> Activate();
        Activate(Time + 1);
    }
};
