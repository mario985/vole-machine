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
void Machine::output() {
    for (int i = 0; i < 16; i++) {
        cout << "RegIndex[" << processor.getALU().DecToHex(to_string(i)) << "]: " << processor.getReg().GetValues(i) << endl;
    }
    cout << "==============" << endl;

    for (int i = 0; i < 256; i++) {
        cout << "MemSlot[" << processor.getALU().DecToHex(to_string(i)) << "]: " << processor.getMem().Get_Value(i) << endl;
    }
}