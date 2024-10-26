#include <iostream>
#include <regex>
#include <fstream>
#include <vector>
using namespace std ;
bool is_valid_input (string input){
    bool check = 0 ;
    //regex pattern (R"([-+]?[0-9]+[/]?[-+]?[0-9]*[1-9]*\s[-+*/]\s[-+]?[0-9][0-9]*[/]?[-+]?[0-9]*[1-9]*)") ;
    regex pattern(R"([1-6BC][0-9A-F]{1}[0-9A-F]{1}[0-9A-F]{1})");
    if(!(regex_match (input , pattern))){
        return 0 ;
    }
    if (input[0] == 'C' && input.substr(1,3) != "000")
    {
        return 0 ;
    }
    if (input[0] == '4' && input[1] != '0')
    {
        return 0;
    }
    return true ;
    
}
vector <string> file_content ;
void read_file (string filename){
    ifstream file ;
    string word;
    file.open(filename , ios::in);
    while (file >> word ){
        file_content.push_back(word);
        
    }

}
bool file_check (){
    bool checker = 0 ;
    for (int i = 0 ; i < file_content.size() ; i++){
        if (file_content[i].length() != 4){
            continue;
        }
        if (is_valid_input(file_content[i])){
            checker = 1 ;
        }
        else{
            checker = 0 ;
            break ;
        }
    
}
return checker ;
}
int main (){
    read_file("test.txt");
    if (file_check()){
        cout << "success" ;
    }
    else {
        cout << "fuck" ;
    }
}