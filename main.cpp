#include <iostream>
#include "padding.hpp"

void printSpringStats(){
    std::cout<<"Actual coils : " << actualCoils<<std::endl;
    std::cout<<"Total produced coils : " << producedCoils<<std::endl;
    std::cout<<"Total produced chassis : " << chassisCounter<<std::endl;
    std::cout<<"Actual chassis frames : " << actualFrames<<std::endl;
    std::cout<<"Total produced chassis frames : " << producedFrames<<std::endl;
    std::cout<<"Semi-finished bonnels : " << semiFinishedBonnels<<std::endl;
}

void printSewingStats(){
    std::cout<<"Total fabric produced : " << fabricCounter<<std::endl;
    std::cout<<"Total produced borders : " << borderCounter<<std::endl;
    std::cout<<"Total produced Panels : " << panelCounter<<std::endl;
}

int main(int argc, const char** argv) {
    RandomSeed(time(NULL)); //nastaveni seed pre random
    Init(0,60 * 550);
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

    std::cout<<"Total produced matress: "<<mattress<<std::endl;
    return 0;
}