#include <iostream>     // for use of cin, cout, endl
#include <string>       // for use of strings, string member functions
#include <cmath>        // for use of pow(x,y) function
// NO OTHER LIBRARIES ARE ALLOWED!

using namespace std;

// function: disassemble takes in a string representing
//          an assembled MIPS instruction as a string
//          and returns the instruction itself
//
//          This is a limited disassembler: we can safely assume the input is:
//          a) legitimate (an actual MIPS instruction)
//          b) is ONLY an I-type and ONLY one of: addi, addiu, andi, ori, slti, sltiu
//          c) has ONLY registers $t0 thru $t7, or $s0 thru $s7 in the instruction
//
string disassemble( string hex ) {
    // You want to retrieve all the separate fields of an I-type instruction
    //      to help you figure out what the assembly instruction is.
    // HINT: Use bitwise masking and bit-shifting to isolate the 
    //      different parts of the hex instruction!
    // YOUR CODE GOES HERE!!

   
   int v[] = {0b001000, 0b001001,0b001100, 0b001101, 0b001010, 0b001011}; 
   string names[] = {"addi", "addiu", "andi", "ori", "slti", "sltiu"};


    int maskO= 0b11111100000000000000000000000000;
    int hex1 = stoi(hex, nullptr, 16); 
    int op = (hex1 & maskO) >> 26;
    string opcode;
    string oneReg; 
    string dosReg;
    string immReg;


    for(int i = 0; i < 6; i++){
        if (op == v[i]){
            opcode=names[i];
        }
    }

    int mask1 =  0b00000011111000000000000000000000; //rs
    int mask2 =  0b00000000000111110000000000000000; //rt
    int mask3 = 0b0000000000000001111111111111111; //immedaite 

    int rs = ( hex1 & mask1) >> 21;
    int rt = (hex1 & mask2) >> 16;
    int immd = (hex1 & mask3) >> 0;
    //cout << rs << endl;
    //cout <<rt << endl;
    //cout << immd << endl;
    
    int mask_bin = 0b1000000000000000;
    int immd2 = (immd & mask_bin) >> 15;
    if (immd2 == 1){
      if (opcode == "slti" || opcode ==  "addi") {
        immd = immd - (1 << 16);
        }
    }

    int d[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23}; 
    string labels[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6","$t7","$s0","$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7" };



    for ( int j =0; j < 16; j++){
        if (rs == d[j]){
            oneReg = labels[j];
        }
        if (rt == d[j]){
            dosReg = labels[j];
        }
    }
    
        return opcode + " " + dosReg +  ", " + oneReg + ", " + to_string(immd);
}

int main() {
// Do NOT change ANY code in main() function!!
//      or you will fail this task (get a zero)

    string hex, inst;
    
    cout << "Enter your assembled instruction as a hex number: 0x";
    cin >> hex;
    
    inst = disassemble( hex );
    cout << "Your instruction is:\n" << inst << endl;

    return 0;
}
