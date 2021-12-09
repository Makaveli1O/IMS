#include "spring.hpp"
#include "sewing.hpp"

int mattress = 0;
Store PaddingTables(7);
Store TapingMachines(9);
Store PackingMachines(2);
class Padding : public Process{
    public:
        void Behavior(){
            if (panelCounter > 0 && borderCounter > 0 && semiFinishedBonnels > 0){
                panelCounter--;
                borderCounter--;
                semiFinishedBonnels--;
                PaddingProcess();
                TapingProcess();
                PackingProcess();
                mattress++;
            }
        }

        void PaddingProcess(){
            Enter(PaddingTables, 1);
            Wait(Beta(1.8, 1.38, 12, 15));
            Leave(PaddingTables, 1);
            return;
        }

        void TapingProcess(){
            Enter(TapingMachines, 1);
            Wait(4+_Weibull(2.0, 3.46));
            Leave(TapingMachines, 1);
            return;
        }

        void PackingProcess(){
            Enter(PackingMachines, 1);
            Wait(_Weibull(11.7, 0.338));
            Leave(PackingMachines, 1);
        }

};

class MatressBuildUp : public Event{
    void Behavior(){
        (new Padding) -> Activate();
        Activate(Time + 1);
    }
};
