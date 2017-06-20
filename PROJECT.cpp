#include <iostream>
#include <string>
#include <string>
#include <fstream>
#include "stdlib.h"
#include <iomanip>

using namespace std;


//Varibales

int regs[32] = { 0 };
unsigned int pc = 0x0;
char memory[8 * 1024];
bool flag = false;
string lines[200] = { " " };
int imms = 0;
int out = 0;


//start of assembler
void clean(string &op_str)
{
    for (int i = 0; i < op_str.length(); i++)
    {
        if (op_str.at(i) == ' ')
            op_str.erase(i, 1);
    }
}

void get_op(string op_str, unsigned int & op)  // checking rd, rs1, rs2 and sending back their values
{
    clean(op_str);
    if ((op_str == "zero") || (op_str == "x0"))
    {
        op = 0;
        return;
    }
    else if (op_str == "ra")
    {
        op = 1;
        return;
    }
    else if (op_str == "sp")
    {
        op = 2;
        return;
    }
    else if (op_str == "gp")
    {
        op = 3;
        return;
    }
    else if (op_str == "tp")
    {
        op = 4;
        return;
    }
    else if (op_str == "t0")
    {
        op = 5;
        return;
    }
    else if (op_str == "t1")
    {
        op = 6;
        return;
    }
    else if (op_str == "t2")
    {
        op = 7;
        return;
    }
    else if (op_str == "s0")
    {
        op = 8;
        return;
    }
    else if (op_str == "s1")
    {
        op = 9;
        return;
    }
    else if (op_str == "a0")
    {
        op = 10;
        return;
    }
    else if (op_str == "a1")
    {
        op = 11;
        return;
    }
    else if (op_str == "a2")
    {
        op = 12;
        return;
    }
    else if (op_str == "a3")
    {
        op = 13;
        return;
    }
    else if (op_str == "a4")
    {
        op = 14;
        return;
    }
    else if (op_str == "a5")
    {
        op = 15;
        return;
    }
    else if (op_str == "a6")
    {
        op = 16;
        return;
    }
    else if (op_str == "a7")
    {
        op = 17;
        return;
    }
    else if (op_str == "s2")
    {
        op = 18;
        return;
    }
    else if (op_str == "s3")
    {
        op = 19;
        return;
    }
    else if (op_str == "s4")
    {
        op = 20;
        return;
    }
    else if (op_str == "s5")
    {
        op = 21;
        return;
    }
    else if (op_str == "s6")
    {
        op = 22;
        return;
    }
    else if (op_str == "s7")
    {
        op = 23;
        return;
    }
    else if (op_str == "s8")
    {
        op = 24;
        return;
    }
    else if (op_str == "s9")
    {
        op = 25;
        return;
    }
    else if (op_str == "s10")
    {
        op = 26;
        return;
    }
    else if (op_str == "s11")
    {
        op = 27;
        return;
    }
    else if (op_str == "t3")
    {
        op = 28;
        return;
    }
    else if (op_str == "t4")
    {
        op = 29;
        return;
    }
    else if (op_str == "t5")
    {
        op = 30;
        return;
    }
    else if (op_str == "t6")
    {
        op = 31;
        return;
    }
    else
        cout << "undefined register" << endl;
}




void check_all(string word, string line, string type, unsigned int &rd, unsigned int &rs1, unsigned int &rs2)
{
    // a function to receive the line and  return the values of rd, rs1, rs2
    
    string rd_str, rs1_str, rs2_str;
    long place;
    int c = 3;
    bool flag2 = true;
    for (int i = 3; i < line.length() / 2; i++)
    {
        if (line[i] == 'r' || line[i] == 's' || line[i] == 'g' || line[i] == 't' || line[i] == 'a')
            flag2 = false;
        if (flag2)
            c++;
    }
    
    if (type == "R")
    {
        rd_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        line.replace(line.find(','), 1, " ");
        rs1_str = line.substr(place + 2, line.find(',') - place - 2);
        place = line.find(',');
        line.replace(line.find(','), 1, " ");
        rs2_str = line.substr(place + 2, line.find(',') - place - 2);
        //cout << rd_str << "   "<< rs1_str << "  " << rs2_str << endl;
        get_op(rd_str, rd);
        get_op(rs1_str, rs1);
        get_op(rs2_str, rs2);
        //cout << rd_str << "  " << rd<< endl;
        // cout << rs1_str << "  " << rs1 << endl;
        // cout << rs2_str << "  " << rs2 << endl;
        return;
    } // end R type
    if (type == "I_L")
    {
        rd_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        rs1_str = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
        get_op(rd_str, rd);
        get_op(rs1_str, rs1);
        return;
    }// end of I_L type
    if (type == "I")
    {
        rd_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        line.replace(line.find(','), 1, " ");
        rs1_str = line.substr(place + 2, line.find(',') - place - 2);
        //   cout << rs1_str << "  " << rd_str << endl;
        get_op(rd_str, rd);
        get_op(rs1_str, rs1);
        
    }// end of I typ
    if (type == "S")
    {
        rs2_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        rs1_str = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
        get_op(rs2_str, rs2);
        get_op(rs1_str, rs1);
        return;
    } //end of S type
    
    if (type == "B")
    {
        
        rs1_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        line.replace(line.find(','), 1, " ");
        rs2_str = line.substr(place + 2, line.find(',') - place - 2);
        get_op(rs2_str, rs2);
        get_op(rs1_str, rs1);
        return;
        //   cout << rs2_str <<"  " << rs2 <<endl;
        //  cout << rs1_str <<"  " << rs1 <<endl;
    } // end of brnch type
    
    if (type == "J1")
    {
        rd_str = line.substr(c, line.find(',') - c);
        place = line.find(',');
        get_op(rd_str, rd);
        
        //  cout << rd_str << "  " << rd << endl;
    }//end of J1
    
    if (type == "J2")
    {
        flag2 = true;
        c = 4;
        for (int i = 4; i < line.length() / 2; i++)
        {
            if (line[i] == 'r' || line[i] == 's' || line[i] == 'g' || line[i] == 't' || line[i] == 'a')
                flag2 = false;
            if (flag2)
                c++;
        }
        rd_str = line.substr(c, line.find(',') - (c+1));
        place = line.find(',');
        line.replace(line.find(','), 1, " ");
        rs1_str = line.substr(place + 2, line.find(',') - place - 2);
        get_op(rd_str, rd);
        get_op(rs1_str, rs1);
    }//end of J2
}

int get_address(string str)
{  //function receives the line and return if it conatins the adress as a label
    string y;
    for (int i = 0; i < 200; i = i + 4)
    {
        //  cout << str << "  " << lines[i] << endl;
        if (str.find(lines[i]) != std::string::npos)
        {
            // cout << str << "checker  found " << endl;
            return i;
        }
    }
    for (int i = 0; i < 200; i++) {
        if ((str.at(i) == '0') && (str.at(i+1) == 'x'))
        {
            y = str.substr(i, ' ');
            return atoi(y.c_str());
        }
    }
    return -1;
    
}


void get_imm(string word, string line, string type, int & imm)
{
    // a function gets the immdiate as a string and return its value as an integer
    bool flag = true;
    string imm_str;
    int i = 0;
    if (type == "I_L")
    {
        line = line.replace(0, line.find(','), " ");
        while (line[i] != '(')
        {
            if ((int)line[i] >= '0' && (int)line[i] <= '9')
                imm_str = imm_str + line[i];
            i++;
        }
        //cout << imm_str << endl;
    }// end of I_L type
    else if (type == "I")
    {
        line = line.replace(0, line.find(',') + 1, " ");
        line = line.replace(0, line.find(',') + 1, " ");
        for (int j = 0; j < line.length(); j++)
        {
            if ((int)line[j] >= '0' && (int)line[j] <= '9')
                imm_str = imm_str + line[j];
        }
    }// end if I type
    else if (type == "S")
    {
        line = line.replace(0, line.find(',') + 1, " ");
        line = line.replace(line.find('('), line.length() - line.find('('), " ");
        for (int j = 0; j < line.length(); j++)
        {
            if ((int)line[j] >= '0' && (int)line[j] <= '9')
                imm_str = imm_str + line[j];
        }
        //   cout << imm_str << endl;
    }// S type end
    
    else if (type == "B")
    {
        
        line = line + ':';
        imm = get_address(line);
        if (imm == -1)
        {
            line = line.replace(0, line.find(',') + 1, " ");
            line = line.replace(0, line.find(',') + 1, " ");
            for (int j = 0; j < line.length(); j++)
            {
                if ((int)line[j] >= '0' && (int)line[j] <= '9')
                    imm_str = imm_str + line[j];
            }
        }
        else return;
    }// end of B type
    
    else if (type == "J1")
    {
        line = line + ':';
        imm = get_address(line);
        if (imm == -1)
        {
            line = line.replace(0, line.find(',') + 1, " ");
            for (int j = 0; j < line.length(); j++)
            {
                if ((int)line[j] >= '0' && (int)line[j] <= '9')
                    imm_str = imm_str + line[j];
            }
        }
        else return;
        
        
    }//end of J1 type
    
    else if (type == "J2")
    {
        line = line + ':';
        imm = get_address(line);
        if (imm == -1)
        {
            line = line.replace(0, line.find(',') + 1, " ");
            for (int j = 0; j < line.length(); j++)
            {
                if ((int)line[j] >= '0' && (int)line[j] <= '9')
                    imm_str = imm_str + line[j];
            }
        }
        else return;
        
    }//end of j2 type
    
    int mult = 1;
    imm = 0;
    for (int i = imm_str.length() - 1; i >= 0; i--)
    {
        imm = imm + ((int)imm_str[i] - '0')*mult;
        mult = mult * 10;
    }
}


void Assembler(string line)
{
    string word = "";   // first word
    out = 0;  // final output
    unsigned int rd, rs1, rs2, funct3, funct7, opcode, shamt;
    int imm_num;
    int temp;
    //getting the first word
    int i = 0;
    for (int i = 0; i< line.length(); i++)
    {
        if (line.at(i) != ' ')
            word = word + line.at(i);
        else
            i = line.length();
    }
    
    //R type
    if (word == "add" || word == "sub" || word == "sll" || word == "slt" || word == "sltu" || word == "xor" || word == "srl" || word == "slt" || word == "sra" || word == "slt" || word == "or" || word == "and")
    {
        opcode = 0x33;
        if (word == "add" || word == "sub")
        {
            funct3 = 0x0;
            if (word == "add")
                funct7 = 0;
            else
                funct7 = 0x20;
        }
        else if (word == "sll")
        {
            funct3 = 1;
            funct7 = 0;
        }
        else if (word == "slt")
        {
            funct3 = 2;
            funct7 = 0;
        }
        else if (word == "sltu")
        {
            funct3 = 3;
            funct7 = 0;
        }
        else if (word == "xor")
        {
            funct3 = 4;
            funct7 = 0;
        }
        else if (word == "srl" || word == "sra")
        {
            {
                funct3 = 5;
                if (word == "srl")
                    funct7 = 0;
                else
                    funct7 = 0x20;
            }
        }
        else if (word == "or")
        {
            funct3 = 6;
            funct7 = 0;
        }
        
        else if (word == "and")
        {
            funct3 = 7;
            funct7 = 0;
        }
        
        check_all(word, line, "R", rd, rs1, rs2);
        
        out = opcode & 0x0000007F;
        out = out | (rd << 7);
        out = out | (funct3 << 12);
        out = out | (rs1 << 15);
        out = out | (rs2 << 20);
        out = out | (funct7 << 25);
        out = out | 0x00000000;
        return;
        
    }
    
    else if (word == "lb" || word == "lh" || word == "lw" || word == "lbu" || word == "lhu")
    {
        opcode = 0x03;
        if (word == "lb")
            funct3 = 0;
        else if (word == "lh")
            funct3 = 1;
        else if (word == "lw")
            funct3 = 2;
        else if (word == "lbu")
            funct3 = 4;
        else if (word == "lhu")
            funct3 = 5;
        check_all(word, line, "I_L", rd, rs1, rs2);
        get_imm(word, line, "I_L", imm_num);
        //cout << dec << imm_num << endl;
        out = opcode & 0x0000007F;
        out = out | (rd << 7);
        out = out | (funct3 << 12);
        out = out | (rs1 << 15);
        out = out | (imm_num << 20);
        return;
    }
    else if (word == "addi" || word == "slli" || word == "slti" || word == "sltiu" || word == "xori" || word == "srli" || word == "srai" || word == "ori" || word == "andi")
    {
        
        opcode = 0x13;
        funct7 = 0;
        if (word == "addi")
            funct3 = 0;
        else if (word == "slli")
            funct3 = 1;
        else if (word == "slti")
            funct3 = 2;
        else if (word == "sltiu")
            funct3 = 3;
        else if (word == "xori")
            funct3 = 4;
        else if (word == "srli" || word == "srai")
        {
            funct3 = 5;
            if (word == "srli")
                funct7 = 0;
            else
                funct7 = 32;
            
        }
        else if (word == "ori")
            funct3 = 6;
        else if (word == "andi")
            funct3 = 7;
        
        check_all(word, line, "I", rd, rs1, rs2);
        get_imm(word, line, "I", imm_num);
        // cout <<dec << imm_num << "  " << dec << rs1 << endl;
        if (word == "srai")
        {
            out = opcode & 0x0000007F;
            out = out | (rd << 7);
            out = out | (funct3 << 12);
            out = out | (rs1 << 15);
            out = out | (imm_num << 20);
            out = out | (0x20 << 25);
            
        }
        else
        {
            out = opcode & 0x0000007F;
            out = out | (rd << 7);
            out = out | (funct3 << 12);
            out = out | (rs1 << 15);
            out = out | (imm_num << 20);
        }
        
    }
    
    else if (word == "sb" || word == "sh" || word == "sw")
    {
        opcode = 0x23;
        if (word == "sb")
            funct3 = 0;
        else if (word == "sh")
            funct3 = 1;
        else if (word == "sw")
            funct3 = 2;
        check_all(word, line, "S", rd, rs1, rs2);
        get_imm(word, line, "S", imm_num);
        out = opcode & 0x0000007F;
        out = out | ((imm_num & 0x1f) << 7);
        out = out | (funct3 << 12);
        out = out | (rs1 << 15);
        out = out | (rs2 << 20);
        imm_num = imm_num >> 5;
        out = out | (imm_num << 25);
    }
    else if (word == "beq" || word == "bne" || word == "blt" || word == "bge" || word == "bltu" || word == "bgeu")
    {
        opcode = 0x63;
        if (word == "beq")
            funct3 = 0;
        else if (word == "bne")
            funct3 = 1;
        else if (word == "blt")
            funct3 = 4;
        else if (word == "bge")
            funct3 = 5;
        else if (word == "bltu")
            funct3 = 6;
        else if (word == "bgeu")
            funct3 = 7;
        check_all(word, line, "B", rd, rs1, rs2);
        
        get_imm(word, line, "B", imm_num);
        // cout <<dec << imm_num << endl;
        // imm_num=(imm_num-pc-4);
        out = opcode & 0x0000007F;
        out = out | (((imm_num >> 11) & 0x1) << 7);
        out = out | (((imm_num >> 1) & 0xf) << 8);
        out = out | ((funct3) << 12);
        out = out | (rs1 << 15);
        out = out | (rs2 << 20);
        imm_num = imm_num >> 5;
        out = out | ((imm_num & 0x3f) << 25);
        imm_num = imm_num >> 7;
        out = out | ((imm_num & 0x1) << 31);
    }
    
    if (word == "lui" || word == "jal" || word == "auipc")
    {
        if (word == "lui")
            opcode = 0x37;
        else if (word == "jal")
            opcode = 0x6f;
        else
            opcode = 0x17;
        
        check_all(word, line, "J1", rd, rs1, rs2);
        get_imm(word, line, "J1", imm_num);
        //  cout << imm_num << "   imm"<<endl;
        if (word == "jal")
        {
            out = opcode & 0x0000007F;
            out = out | (rd << 7);
            out = out | (((imm_num >> 12) & 0xff) << 12);
            out = out | (((imm_num >> 11) & 0x1) << 20);
            out = out | (((imm_num >> 1) & 0x3ff) << 21);
            out = out | (((imm_num >> 20) & 0x1) << 31);
        }
        else
            
        {
            out = opcode & 0x0000007F;
            out = out | (rd << 7);
            out = out | ((imm_num >> 12) << 12);
        }
        
    }
    else if (word == "jalr")
    {
        opcode = 0x67;
        funct3 = 0;
        check_all(word, line, "J2", rd, rs1, rs2);
        get_imm(word, line, "J2", imm_num);
        out = opcode & 0x0000007F;
        out = out | (rd << 7);
        out = out | (funct3 << 12);
        out = out | (rs1 << 15);
        out = out | (imm_num << 20);
    }
    else if (word == "ECALL") {
        opcode = 0x73;
        out = opcode & 0x00000073;
    }
    
    
}

string get_binary(int outt)
{int i=0;
    string out_str;
    while (outt != 0)
    {
        if (outt % 2 == 1)
            out_str = '1' + out_str;
        else
            out_str = '0' + out_str;
        outt = outt / 2;
        i++;
    }
    return out_str;
}

void check_address(string line)
{
    if (line.find(':') != std::string::npos)
    {
        lines[pc] = line;
        //cout << line << endl;
    }
    else if (line.find('#') != std::string::npos)
    {
        lines[pc] = "";
    }
    return;
}










// Start of dissasembler functions //////%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void emitError(char *s)
{
    cout << s;
    exit(0);
}

void printPrefix(unsigned int instA, unsigned int instW) {
    cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << std::setw(8) << instW;
}



void instDecExec(unsigned int instWord)
{
    
    unsigned int rd, rs1, rs2, funct3, funct7, opcode;
    unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
    regs[0] = 0;
    unsigned int instPC = pc - 4;
    
    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    funct7 = (instWord >> 25) & 0x00007F;
    
    I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
    S_imm = ((funct7 << 7) | rd) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
    U_imm = (instWord & 0xFFFFF000);
    B_imm = ((rd & 0x1E)) | ((funct7 & 0x3F) << 5) | ((rd & 0x1) << 11) | (((instWord >> 31) ? 0xFFFFF000 : 0x0));
    J_imm = ((instWord & 0x7FE00000) >> 20) | ((instWord >> 20 & 0x1) << 11) | ((instWord >> 12 & 0x7F) << 12)
    | (((instWord >> 31) ? 0xFFF80000 : 0x0));
    
    printPrefix(instPC, instWord);
    
    if(instWord == 0)
    {
        flag = true;
        return;
    }
    
    
    
    // R type
    if (opcode == 0x33)
    {
        switch (funct3) {
            case 0:
                if (funct7 == 0)
                {
                    cout << "  " << "ADD  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                    regs[rd] = regs[rs1] + regs[rs2];
                }
                
                else
                {
                    cout << "  " << "SUB  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                    regs[rd] = regs[rs1] - regs[rs2];
                }
                break;
            case 1:
                cout << "  " << "SLL  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                regs[rd] = regs[rs1] << regs[rs2];
                break;
            case 2:
                cout << "  " << "SLT  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                if (regs[rs1] < regs[rs2])
                    regs[rd] = 1;
                else
                    regs[rd] = 0;
                break;
            case 3:
                cout << "  " << "SLTU  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                if (regs[rs1] == 0)
                {
                    if (regs[rs2] != 0)
                        regs[rd] = 1;
                    else
                        regs[rd] = 0;
                }
                else
                {
                    if ((unsigned int)(regs[rs1]) < (unsigned int)(regs[rs2]))
                        regs[rd] = 1;
                    else
                        regs[rd] = 0;
                }
                break;
                
            case 4:
                cout << "  " << "XOR  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                regs[rd] = (unsigned int)regs[rs1] ^ (unsigned int)regs[rs2];
                break;
            case 5:
                if (funct7 == 0)
                {
                    cout << "  " << "SRL  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                    regs[rd] = ((unsigned int)regs[rs1]) >> regs[rs2];
                }
                
                else
                {
                    cout << "  " << "SRA  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                    regs[rd] = regs[rs1] >> (regs[rs2]);
                }
                break;
            case 6:
                cout << "  " << "OR  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                regs[rd] = (unsigned int)regs[rs1] | (unsigned int)regs[rs2];
                break;
            case 7:
                cout << "  " << "AND  x" << rd << " ,x" << rs1 << " ,x" << rs2 << endl;
                regs[rd] = (unsigned int)regs[rs1] & (unsigned int)regs[rs2];
                break;
            default:
                cout << "error, function 3 has a wrong number/ R-type" << endl;
                break;
        }
    }
    else if (opcode == 0x3)
    {
        switch (funct3)
        {
            case 0:
                cout << "  LB  x" << rd << ", " << hex << "0x" << (int)I_imm << "(x" << rs1 << ")" << endl;
                regs[rd] = 0;
                regs[rd] = (unsigned char)memory[regs[rs1] + (int)I_imm] | ((((unsigned char)memory[regs[rs1] + (int)I_imm] >> 7) ? 0xFFFFFF00 : 0x0));
                break;
            case 1:
                cout << "  LH  x" << rd << ", " << hex << "0x" << (int)I_imm << "(x" << rs1 << ")" << endl;
                regs[rd] = 0;
                regs[rd] = ((unsigned char)memory[regs[rs1] + (int)I_imm]) | ((unsigned char)memory[regs[rs1] + (int)I_imm + 1] << 8)
                | (((((unsigned char)memory[regs[rs1] + (int)I_imm + 1]) >> 15) ? 0xFFFF0000 : 0x0));
            case 2:
                cout << "  LW  x" << rd << ", " << hex << "0x" << (int)I_imm << "(x" << rs1 << ")" << endl;
                regs[rd] = ((unsigned char)memory[regs[rs1] + (int)I_imm]) | (((unsigned char)memory[regs[rs1] + (int)I_imm + 1]) << 8)
                | (((unsigned char)memory[regs[rs1] + (int)I_imm + 2]) << 16)
                | (((unsigned char)memory[regs[rs1] + (int)I_imm + 3]) << 24);
                break;
            case 4:
                cout << "  LBU  x" << rd << ", " << hex << "0x" << (int)I_imm << "(x" << rs1 << ")" << endl;
                regs[rd] = 0;
                regs[rd] = (unsigned char)memory[regs[rs1] + (int)I_imm];
                break;
            case 5:
                cout << "  LHU  x" << rd << ", " << hex << "0x" << (int)I_imm << "(x" << rs1 << ")" << endl;
                regs[rd] = 0;
                regs[rd] = ((unsigned char)memory[regs[rs1] + (int)I_imm]) | ((unsigned char)memory[regs[rs1] + (int)I_imm + 1] << 8);
                break;
            default:
                cout << "function 3 has a wrong number/ I type/ store " << endl;
                break;
        }
    }
    else if (opcode == 0x13) // I type
    {
        switch (funct3)
        {
            case 0:
                cout << "  ADDI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                regs[rd] = regs[rs1] + (int)I_imm;
                break;
            case 1:
                cout << "  SLLI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                regs[rd] = regs[rs1] << (unsigned int)rs2;
                break;
            case 2:
                cout << "  SLTI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                
                if (regs[rs1] < (int)I_imm)
                    regs[rd] = 1;
                else
                    regs[rd] = 0;
                break;
            case 3:
                cout << "  SLTIU  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                if ((unsigned int)regs[rs1] < I_imm || regs[rs1] == 0)
                    regs[rd] = 1;
                else
                    regs[rd] = 0;
                break;
            case 4:
                cout << "  XORI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                regs[rd] = (unsigned int)regs[rs1] ^ (int)I_imm;
                break;
            case 5:
                if (funct7 == 0)
                {
                    cout << "  SRLI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                    regs[rd] = ((unsigned int)regs[rs1]) >> (unsigned int)rs2;
                }
                else
                {
                    cout << "  SRAI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                    regs[rd] = (int)regs[rs1] >> rs2;
                }
                break;
            case 6:
                cout << "  ORI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                regs[rd] = (unsigned int)regs[rs1] | (int)I_imm;
                break;
            case 7:
                cout << "  ANDI  x" << rd << ", x" << rs1 << ", " << hex << "0x" << (int)I_imm << endl;
                
                regs[rd] = ((unsigned int)regs[rs1]) & (int)I_imm;
                break;
            default:
                cout << "function 3 has a wrong number/ I type  " << endl;
                break;
        }
        
    }
    else if (opcode == 0x23)
    {
        switch (funct3) {
            case 0:
                cout << "  SB  x" << rs2 << ", " << hex << "0x" << (int)S_imm << "(x" << rs1 << ")" << endl;
                memory[regs[rs1] + S_imm] = regs[rs2];
                break;
            case 1:
                cout << "  SH  x" << rs2 << ", " << hex << "0x" << (int)S_imm << "(x" << rs1 << ")" << endl;
                memory[regs[rs1] + S_imm] = regs[rs2];
                memory[regs[rs1] + S_imm + 1] = regs[rs2] >> 8;
                break;
            case 2:
                cout << "  SW  x" << rs2 << ", " << hex << "0x" << (int)S_imm << "(x" << rs1 << ")" << endl;
                memory[regs[rs1] + S_imm] = regs[rs2];
                memory[regs[rs1] + S_imm + 1] = regs[rs2] >> 8;
                memory[regs[rs1] + S_imm + 2] = regs[rs2] >> 16;
                memory[regs[rs1] + S_imm + 3] = regs[rs2] >> 24;
                break;
            default:
                cout << "function 3 has a wrong number / S-type " << endl;
                break;
                
        }
    }
    else if (opcode == 0x63)
    {
        switch (funct3)
        {
            case 0:
                cout << "  BEQ  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if (regs[rs1] == regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            case 1:
                cout << "  BNE  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if (regs[rs1] != regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            case 4:
                cout << "  BLT  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if ((int)regs[rs1] < (int)regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            case 5:
                cout << "  BGE  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if ((int)regs[rs1] >= (int)regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            case 6:
                cout << "  BLTU  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if (regs[rs1] < regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            case 7:
                cout << "  BGEU  x" << rs1 << ", x" << rs2 << ", " << hex << "0x" << (int)B_imm << endl;
                if (regs[rs1] >= regs[rs2])
                    pc += (int)B_imm - 4;
                break;
            default:
                cout << " function 3 has a wrong number/ branch instructions" << endl;
        }
    }
    
    else if (opcode == 0x37)
    {
        cout << "  LUI  x" << rd << ", " << hex << "0x" << (int)U_imm << endl;
        regs[rd] = U_imm;
    }
    else if (opcode == 0x17)
    {
        cout << "  AUIPC  x" << rd << ", " << hex << "0x" << (int)U_imm << endl;
        regs[rd] = U_imm + instPC;
    }
    
    else if (opcode == 0x6F)
    {
        cout << "  JAL  x" << rd << ", " << hex << "0x" << (int)U_imm << endl;
        regs[rd] = pc;
        pc += (int)J_imm - 4;
    }
    
    else if (opcode == 0x67)
    {
        cout << "  JALR  x" << rd << ", " << hex << "0x" << (int)U_imm << endl;
        regs[rd] = pc;
        pc = (I_imm + regs[rs1]) & 0xFFFFFFFE;
    }
    else if (opcode == 0x73)
    {
        
        cout << "  ECALL  ";
        
        if (regs[10] == 10)
        {flag = true;
            cout << "Termination  " << endl;
        }
        
        else if (regs[17] == 5)
            cin >> regs[17];
        
        else if (regs[17] == 1)
            cout << dec << regs[10] << endl;
        
        else if (regs[17] == 4)
        {
            int temp = regs[10];
            while (memory[temp] != '0')
            {
                cout << memory[temp];
                temp++;
            }
            cout << endl;
            
        }
    }
}


int main()
{
    char checker;
    cout << "To use disassembler press D and enter, to use assembler press A and enter" << endl;
    cin >> checker;
    if (checker=='d' || checker=='d')
    {
    ///// disassembler
    unsigned int instWord = 0;
    string x = "/Users/Air/Desktop/Assembly Project/Samples/mult1.bin";
    ifstream inFile;
    inFile.open(x.c_str(), ios::in | ios::binary | ios::ate);
    
    if (inFile.is_open())
    {
        int fsize = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        if (!inFile.read((char *)memory, fsize)) emitError("Cannot read from input file\n");
        
        while (!flag) {
            instWord = (unsigned char)memory[pc] |
            (((unsigned char)memory[pc + 1]) << 8) |
            (((unsigned char)memory[pc + 2]) << 16) |
            (((unsigned char)memory[pc + 3]) << 24);
            pc += 4;
            instDecExec(instWord);
        }
        
        for (int i = 0; i<32; i++)
            cout << "x" << dec << i << ": \t" << "0x" << hex << std::setfill('0') << std::setw(8) << regs[i] << "\n";
        
    }
    else emitError("Cannot access input file\n");
    }
    
    else
    {
        ////assembler
        ifstream Assembler_read;
        ofstream outfile;
        string line;
        string file = "/Users/Air/Desktop/file2.txt";
        string output = "/Users/Air/Desktop/div.bin";
        Assembler_read.open(file.c_str());
        outfile.open(output.c_str(), ios::out | ios::binary | ios::ate );
        
        for (int i = 0; i < 200; i++)
            lines[i] = "%%%%%%%%%%";
        
        // reading the lines and storing their addresses
        while (!Assembler_read.eof())
        {
            getline(Assembler_read, line);
            check_address(line);
            pc = pc + 4;
        }
        
        Assembler_read.close();
        Assembler_read.open(file.c_str());
        pc=0;
        if (Assembler_read.is_open())
        {
            while (!Assembler_read.eof())
            {
                getline(Assembler_read, line);
                Assembler(line);
                pc=pc+4;
                if (out != 0) {
                    cout << "0x" << hex << std::setfill('0') << std::setw(8) << out <<"  " << get_binary(out)<< endl;
                    outfile << get_binary( out )  << endl;
                    //   outfile.write(reinterpret_cast <const char*> (&out), sizeof(out));
                }
                
            }
        }
        Assembler_read.close();
        outfile.close();
        
        system("pause");
    }
}
