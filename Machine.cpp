#include "Machine.h"

void Machine::Import(string filename) {
    ifstream file;
    string word;
    file.open(filename, ios::in);
    int BitCounter = 0;
    bool End = false;
    while (file >> word) {
        if (processor.File_Check(word)) {
            processor.getMem().Set_Value(word.substr(0, 2), BitCounter++);
            processor.getMem().Set_Value(word.substr(2, 2), BitCounter++);
        }
        if (word == "C000") {
            End = true;
            break;
        }
    }
    if (!End) {
        processor.getMem().Set_Value("C0", BitCounter++);
        processor.getMem().Set_Value("00", BitCounter++);

    }
}
void Machine::setOutput() {
    
}