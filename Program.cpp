#include "Program.h"
#include "Set_Instruction.h"
#include "Registers.h"
#include "Memory.h"
#include "ALU.h"
#include "CPU.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;
Program::Program() : Choices{'1', '2', '3', '4', '5', '6', '7', '8'} {
    //MainMenu();
}
void Program::MainMenu(){
    while(true){
    char Choice; 
    cout<<"Choose method"<<endl;
    cout<<"1-Import"<<endl;
    cout<<"2-Print"<<endl;
    cout<<"3-RunCode"<<endl;
    cout<<"4-Step"<<endl;
    cout<<"5-Clear"<<endl;
    cout<<"6-ClearMemory"<<endl;
    cout<<"7-ClearRegister"<<endl;
    cout<<"8-Exit"<<endl;
    while(true)
    {
         cin>>Choice;
         auto it = find(Choices.begin() , Choices.end() , Choice);
         if(it!=Choices.end()){
            break;
         }
         else cout<<"Please enter a valid choice"<<endl;
    }
    if(!ChooseMethod(Choice)){
        cout<<"Dont forget to try our GUI version (:"<<endl;
        cout << "\nEEEEE  X   X  III  TTTTT   TTTTT  III  N   N   GGG  "<<endl;
        cout << "E      X   X   I     T       T     I   NN  N  G     "<<endl;
        cout << "EEE     X X    I     T       T     I   N N N  G  GG "<<endl;
        cout << "E        X     I     T       T     I   N  NN  G   G "<<endl;
        cout << "EEEEE   X  X  III    T       T    III  N   N   GGG  "<<endl;
        return;
    };

    }


}