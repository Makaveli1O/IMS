#include <iostream>
#include "mattressBuildUp.hpp"

void printSpringStats(){
    std::cout<<"-----------------------------------------------\n Spring department \n-----------------------------------------------"<<std::endl;
    std::cout<<"Total produced coils : " << producedCoils<<std::endl;
    std::cout<<"Total produced chassis : " << totalChassis <<std::endl;
    std::cout<<"Total produced chassis frames : " << producedFrames<<std::endl;
    std::cout<<"Total produced semi-finished bonnels : " << totalSemiFinishedBonnels<<std::endl;
    

    std::cout<<"\nActual numbers(not yet produced by the end of simulation): "<<std::endl;
    std::cout<<"Actual coils : " << actualCoils<<std::endl;
    std::cout<<"Actual chassis frames : " << actualFrames<<std::endl;
    std::cout<<"Actual semi-finished bonnels : " << actualSemiFinishedBonnels<<std::endl;
    
    std::cout<<"\nAssembly machines work rate : "<<std::endl;
    AssemblyMachines.Output();
    std::cout<<"Clinching tables work : "<<std::endl;
    ClinchingTables.Output();
}

void printSewingStats(){
    std::cout<<"-----------------------------------------------\n Quilting and tailoring department \n-----------------------------------------------"<<std::endl;
    std::cout<<"Total fabric produced : " << fabricCounter<<std::endl;
    std::cout<<"Total produced borders : " << totalProducedBorders<<std::endl;
    std::cout<<"Total produced Panels : " << totalProducedPanels<<std::endl;

    std::cout<<"\nActual numbers(not yet produced by the end of simulation): "<<std::endl;
    std::cout<<"Actual borders : " << borderCounter<<std::endl;
    std::cout<<"Actual panels : " << panelCounter<<std::endl;

    std::cout<<"\nSewing panels work rate : "<<std::endl;
    PanelMachines.Output();
    std::cout<<"Sewing borders work rate : "<<std::endl;
    BorderMachine.Output();
}

void printMattressBuildupStats(){
    std::cout<<"-----------------------------------------------\n Matress Build-up department \n-----------------------------------------------"<<std::endl;
    std::cout<<"Padding tables work rate: "<<std::endl;
    PaddingTables.Output();
    std::cout<<"Tape machines work rate: "<<std::endl;
    TapingMachines.Output();
    std::cout<<"Packing machines work rate: "<<std::endl;
    PackingMachines.Output();
}

int main(int argc, const char** argv) {
    int month = 60 * 550; //550 hours each month
    int year = 60 * 550 * 12; 

    RandomSeed(time(NULL)); //nastaveni seed pre random
    
    Init(0,month);
    //spring district
    (new Coil1Gen) -> Activate();
    (new Coil2Gen) -> Activate();
    (new Coil3Gen) -> Activate();
    (new Coil4Gen) -> Activate();
    (new FrameBendingMachine) -> Activate();

    (new Quilt1Gen) -> Activate();
    (new Quilt2Gen) -> Activate();
    (new Quilt3Gen) -> Activate();

    (new MatressBuildUp) -> Activate();

    Run();
    printSpringStats();
    printSewingStats();
    printMattressBuildupStats();
    std::cout<<"\nTotal produced matress: "<<mattress<<std::endl;
    return 0;
}