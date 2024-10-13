#include <bits/stdc++.h>
using namespace std;

class Pass1
{
public:
    map<string, pair<string, string>> opcode;
    map<string, pair<int, string>> symtab;
    vector<pair<string, int>> littab;
    vector<string> pooltab;
    int litindex = 0, lc = -1;

    void initializeOpcodeMap()
    {
        opcode = {
            {"STOP", {"IS", "00"}}, {"ADD", {"IS", "01"}}, {"SUB", {"IS", "02"}}, {"MULT", {"IS", "03"}}, {"MOVER", {"IS", "04"}}, {"MOVEM", {"IS", "05"}}, {"COMP", {"IS", "06"}}, {"BC", {"IS", "07"}}, {"DIV", {"IS", "08"}}, {"READ", {"IS", "09"}}, {"PRINT", {"IS", "10"}}, {"START", {"AD", "01"}}, {"END", {"AD", "02"}}, {"ORIGIN", {"AD", "03"}}, {"EQU", {"AD", "04"}}, {"LTORG", {"AD", "05"}}, {"DC", {"DL", "01"}}, {"DS", {"DL", "02"}}, {"AREG", {"1", ""}}, {"BREG", {"2", ""}}, {"CREG", {"3", ""}}, {"DREG", {"4", ""}}, {"LT", {"1", ""}}, {"LE", {"2", ""}}, {"EQ", {"3", ""}}, {"GT", {"4", ""}}, {"GE", {"5", ""}}, {"ANY", {"6", ""}}};
    }

    int findLiteralIndex(const string &literal)
    {
        for (size_t i = 0; i < littab.size(); ++i)
        {
            if (littab[i].first == literal)
                return i + 1; // Return 1-based index
        }
        return -1; // Not found, should not happen if used correctly
    }

    int computeNewLc(const string &operand)
    {
        // Check if the operand is a label and find its address
        if (operand.find('+') != string::npos)
        {
            // Split the operand by '+'
            string label = operand.substr(0, operand.find('+'));
            int offset = stoi(operand.substr(operand.find('+') + 1));
            if (symtab.count(label))
            {
                return symtab[label].first + offset; // Calculate new LC
            }
        }
        else if (symtab.count(operand))
        {
            return symtab[operand].first; // Set LC to the address of the label
        }
        return stoi(operand); // If it's a direct number, just return it
    }

    void execute()
    {
        initializeOpcodeMap();
        ifstream fin("input.txt");
        ofstream fout("output.txt");
        string line, word;
        symtab.clear();
        littab.clear();
        pooltab.clear();
        litindex = 0;
        lc = -1;

        while (getline(fin, line)) // Process each line from the input file
        {
            stringstream st(line); // Create a stringstream object from the line 
            st >> word; //apan kay karto ki >>word manjh enext word fetch karto from the line 
            string label = "";

            if (opcode.count(word) == 0) // If word is not in the opcode table ie it is a label
            {
                if (symtab.count(word) == 0) //// If the label is not already in the symbol table, add it
                {
                    symtab[word] = {lc, to_string(symtab.size() + 1)}; // Add the label to the symbol table with its current LC
                }
                else
                {
                    symtab[word].first = lc; // If the label already exists, update its location (LC)
                }
                label = word; // Store the label
                st >> word;  // Move to the next word which will be an operation
            }

            string operation = word; //storing the operations 
             // Handle various operations (assembly directives and instructions)
            if (operation == "START")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word;  // Read the constant value after START , which is the location counter
                fout << "(C, " << word << ") "; //C stands for constant here 
                lc = stoi(word); 
            }
            else if (operation == "END")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                fout << endl;
                pooltab.push_back("#" + to_string(litindex + 1)); // Add literals to memory and update their LC in the literal table
                for (; litindex < littab.size(); litindex++)
                {
                    fout << lc << " ";
                    fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;  //update the literal table
                    string literal = littab[litindex].first;
                    cout << literal << endl;
                    string sublit = literal.substr(2, literal.length() - 3); //='7' so processing 7
                    fout << "( C, " << sublit << ") "; //literal table madhun toh constant gheto apan 
                    fout << endl;
                    lc++;
                }
            }
            else if (operation == "LTORG")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                fout << endl;
                pooltab.push_back("#" + to_string(litindex + 1));  // Add literals to memory and update their LC in the literal table
                for (; litindex < littab.size(); litindex++)
                {
                    fout << lc << " ";
                    fout << "( " << opcode["DC"].first << ", " << opcode["DC"].second << ") ";
                    littab[litindex].second = lc;
                    string literal = littab[litindex].first;
                    string sublit = literal.substr(2, literal.size() - 3);
                    fout << "(C, " << sublit << ") ";
                    fout << endl;
                    lc++;
                }
            }
            else if (operation == "ORIGIN")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word;              
                lc = computeNewLc(word); //Update LC based on expression or label
            }
             else if (operation == "EQU")
            {
                fout << "    (" << opcode[word].first << ", " << opcode[word].second << ") ";
                st >> word; 
            }
            // General instructions and literals
            else
            {
                fout << lc << " "; //output the current lc 
                fout << "(" << opcode[word].first << ", " << opcode[word].second << ") ";

                // Process the rest of the line (operands)
                while (st >> word)
                {
                    if (operation == "DC")
                    {
                        if (word.length() == 3)
                        {
                            word = word.substr(1, word.length() - 2);
                        }
                        fout << "(C, " << word << ") ";
                    }
                    else if (operation == "DS")
                    {
                        fout << "(C, " << word << ") "; //doubt
                        lc += stoi(word) - 1;
                    }

                       // Handle literals (e.g., '=5')
                    else if (word[0] == '=') 
                    {
                        bool found = false;
                        //check if literal is already present in the literal table
                        for (const auto &lit : littab)
                        {
                            if (lit.first == word)  
                            {
                                found = true;
                                break;
                            }
                        }
                        
                        //if the literal is new , add it to the table   
                        if (!found)
                        {
                            littab.push_back({word, lc}); 
                            fout << "(L, " << littab.size() << ") ";
                        }
                        else
                        {
                            fout << "(L, " << findLiteralIndex(word) << ") "; 
                        }
                    }

                    //handle the symbols
                    else if (opcode.count(word) > 0)
                    {
                        fout << "(" << opcode[word].first << ") ";
                    }
                    else
                    {
                        if (symtab.count(word) == 0)
                        {
                            symtab[word] = {lc, to_string(symtab.size() + 1)};
                        }
                        fout << "(S, " << symtab[word].second << ") ";
                    }
                }
                lc++;
            }
            fout << endl;
        }

        // Close the input and output files

        fin.close();
        fout.close();

        // Write the symbol table, literal table, and pool table to their files
        writeSymtab();
        writeLittab();
        writePooltab();

        cout << "\nInput file is Processed Successfully!" << endl;
    }

    void writeSymtab()
    {
        ofstream sout("sym.txt");
        for (auto &i : symtab)
        {
            sout << i.second.second << " " << i.first << " " << i.second.first;
            sout << endl;
        }
        sout.close();
    }

    void writeLittab()
    {
        ofstream lout("lit.txt");
        for (auto &i : littab)
        {
            lout << i.first << " " << i.second;
            lout << endl;
        }
        lout.close();
    }

    void writePooltab()
    {
        ofstream pout("pool.txt");
        for (auto &i : pooltab)
        {
            pout << i;
            pout << endl;
        }
        pout.close();
    }

    void displaySymtab()
    {
        ifstream fin("sym.txt");
        string line;
        cout << "\nSymbol Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }

    void displayLittab()
    {
        ifstream fin("lit.txt");
        string line;
        cout << "\nLiteral Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }

    void displayPooltab()
    {
        ifstream fin("pool.txt");
        string line;
        cout << "\nPool Table:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }
    void displayOutput()
    {
        ifstream fin("output.txt");
        string line;
        cout << "\nOutput:" << endl;
        while (getline(fin, line))
        {
            cout << line << endl;
        }
        fin.close();
    }
};

int main()
{
    Pass1 obj;
    int choice;
    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Process the input file" << endl;
        cout << "2. Display Output" << endl;
        cout << "3. Display Symbol Table" << endl;
        cout << "4. Display Literal Table" << endl;
        cout << "5. Display Pool Table" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.execute();
            break;
        case 2:
            obj.displayOutput();

            break;
        case 3:
            obj.displaySymtab();

            break;
        case 4:
            obj.displayLittab();
            break;
        case 5:
            obj.displayPooltab();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
}



/*
Output:
    (AD, 01) (C, 101)
101 (IS, 04) (4) (L, 1)
102 (IS, 05) (4) (S, 1)
103 (IS, 04) (2) (L, 1)
    (AD, 03)
    (AD, 05)
104 ( DL, 01) (C, 9)

105 (IS, 01) (1) (L, 2)
106 (IS, 02) (2) (L, 3)
107 (IS, 06) (2) (S, 1)
108 (IS, 07) (1) (S, 4)
    (AD, 05)
109 ( DL, 01) (C, 5) 
110 ( DL, 01) (C, 7)

    (AD, 04)
    (AD, 03)
111 (IS, 03) (3) (L, 4)
112 (IS, 00)
113 (DL, 02) (C, 3)
    (AD, 02)
116 ( DL, 01) ( C, 8)
*/

/*
Pool Table:
#1
#2
#4

Literal Table:
='9' 104
='5' 109
='7' 110
='8' 116

*/
