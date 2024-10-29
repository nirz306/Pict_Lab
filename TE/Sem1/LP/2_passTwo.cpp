#include <bits/stdc++.h>
using namespace std;

class Pass_02 {
    ifstream sy, li, fin;
    ofstream fout;
    vector<pair<string, int>> symtable;
    vector<pair<string, int>> littable;

public:
    void input() {
        sy.open("pass1_assembler_sym.txt");
        li.open("pass1_assembler_lit.txt");
        fin.open("pass1_assembler_input.txt");
        fout.open("machine.txt");
    }

    void generate() {
        string line = "", word = "";

        // Load Symbol Table
        while (getline(sy, line)) {
            stringstream ss(line);
            string label;
            int address;
            ss >> label >> word >> address; // Read the symbol number, symbol name (ignore), and address
            symtable.push_back({word, address});
        }

        // Load Literal Table
        while (getline(li, line)) {
            stringstream ss(line);
            string label;
            int address;
            ss >> label >> address;
            littable.push_back({label, address});
        }

        // Generate Machine Code from Intermediate Code
        while (getline(fin, line)) {
            stringstream ss(line);
            string location, opcode, operand;
            ss >> location >> opcode; // Read the location and opcode

            if (opcode == "(IS,") {
                string code;
                ss >> code;
                string instruction = code.substr(0, code.size() - 1); // Remove the closing parenthesis
                fout << location << " " << instruction << " "; // Write location and opcode to file

                while (ss >> word) {
                    if (word == "(S,") {
                        ss >> operand;
                        int symIndex = stoi(operand.substr(0, operand.size() - 1)) - 1;
                        fout << symtable[symIndex].second << " "; // Write symbol address
                    } else if (word == "(L,") {
                        ss >> operand;
                        int litIndex = stoi(operand.substr(0, operand.size() - 1)) - 1;
                        fout << littable[litIndex].second << " "; // Write literal address
                    } else if (word.find("(C,") != string::npos) {
                        fout << word.substr(0, word.size() - 1) << " "; // Write constant
                    } else {
                        fout << word << " "; // Write register codes or anything else
                    }
                }
            } else if (opcode == "(DL,") {
                string directive;
                ss >> directive;
                if (directive == "01)") { // DC
                    ss >> word;
                    ss>>word;
                    fout << location << " 00 00 " << word.substr(0, word.size() - 1) << "\n"; // Write DC with constant
                } else if (directive == "02)") { 
                    fout << location << " 00 00 00\n"; 
                }
            }
            fout << "\n"; // New line after each machine instruction
        }
    }

    void show() {
        cout << "\n===========Symbol table ==============" << endl;
        for (auto x : symtable) {
            cout << x.first << " " << x.second << "\n";
        }
        cout << "\n===========Literal table ===============" << endl;
        for (auto x : littable) {
            cout << x.first << " " << x.second << "\n";
        }
    }

    ~Pass_02() {
        sy.close();
        li.close();
        fin.close();
        fout.close();
    }
};

int main() {
    Pass_02 obj;
    obj.input();
    obj.generate();
    obj.show();
    return 0;
}

/* 

INPUT TEXT FILES 

SYM TABLE
4 AGAIN 104
1 N 114
2 ONE 117
6 RESULT 115
3 TERM 118
5 TWO 119

LIT TABLE
='9' 104
='5' 109
='7' 110
='8' 116

        INPUT                               OUTPUT
    (AD, 01) (C, 101)
101 (IS, 04) (4) (L, 1)                  101 04 (4) 104 
102 (IS, 05) (4) (S, 1)                  102 05 (4) 104 
103 (IS, 04) (2) (L, 1)                  103 04 (2) 104 

    (AD, 03)
    (AD, 05)
104 (DL, 01) (C, 9)                       104 00 00 9
105 (IS, 01) (1) (L, 2)                   105 01 (1) 109 
106 (IS, 02) (2) (L, 3)                   106 02 (2) 110 

107 (IS, 06) (2) (S, 1)                   107 06 (2) 104 

108 (IS, 07) (1) (S, 4)                   108 07 (1) 115 

    (AD, 05)
109 (DL, 01) (C, 5)                       109 00 00 5
 
110 (DL, 01) (C, 7)                       110 00 00 7
    (AD, 04)
    (AD, 03)
111 (IS, 03) (3) (L, 4)                   111 03 (3) 116 
112 (IS, 00)                              112 00 
113 (DL, 02)                              113 00 00 00
    (AD, 02)
116 (DL, 01) (C, 8)                       116 00 00 8


                                        ===========Symbol table ==============
                                                    AGAIN 104
                                                    N 114
                                                    ONE 117
                                                    RESULT 115
                                                    TERM 118
                                                    TWO 119
                                                    
                                        ===========Literal table ===============
                                                    ='9' 104
                                                    ='5' 109
                                                    ='7' 110
                                                    ='8' 116

NO MACHINE CODE FOR AD
DL, 01 sathi 0 00 constant
DL,02 sathi 0 00 000

*/
