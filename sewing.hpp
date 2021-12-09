#include <simlib.h>
#include <random>

int idx_quilting = 0;
//int ispanel = 0; //1 - panel, 0 - border
const double wait2[3] = {1.36, 1.46, 1.00};

Store PanelMachines(5);
Facility BorderMachine("BorderMachine");

int panelCounter = 0;
int borderCounter = 0;
int fabricCounter = 0;

double _Weibull(double a, double b){
   std::random_device rd;
   std::mt19937 generator(rd());
   std::weibull_distribution<double> distribution(a,b);

   double retVal = distribution(generator);
   return retVal;
}

enum quilting{
    idx_panel,
    idx_border 
};

class Sewing: public Process{  
    public:
        int idx_quilting;
        //constructor
        Sewing(int idx){
            this->idx_quilting = idx;
        }

        void Behavior(){
            if(idx_quilting == 0)
            {
                PanelProcess();
            }
            else
            {
                BorderProcess();
            }
        }

        void PanelProcess(){
            Enter(PanelMachines, 1);
            Wait(1+_Weibull(4.37, 0.564));
            Leave(PanelMachines, 1);
            panelCounter++;
            return;
        }

        void BorderProcess(){
            Seize(BorderMachine);
            Wait(_Weibull(6.13, 0.324));
            Release(BorderMachine);
            borderCounter++;
        }

};

class Fabric : public Process{
    void Behavior(){
        fabricCounter++;
        double r = Random();
        if (r <= 0.4){
            (new Sewing(idx_border)) -> Activate();
        }else{
            (new Sewing(idx_panel)) -> Activate();
        }
    }
};

class Quilt1Gen : public Event{
    void Behavior(){
        (new Fabric) -> Activate();     
        Activate(Time + wait2[0]);
    }
};
class Quilt2Gen : public Event{
    void Behavior(){
        (new Fabric) -> Activate();     
        Activate(Time + wait2[1]);
    }
};
class Quilt3Gen : public Event{
    void Behavior(){
        (new Fabric) -> Activate();     
        Activate(Time + wait2[2]);
    }
};