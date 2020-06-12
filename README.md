# 2pass-assembler
This a cpp code to implement a two pass assembler . 
This program is a two-pass assembler written in C++, that assembles the source code written in assembly language for a 12-bit system following accumulator architecture and generates an object code written in machine language.
A)Input file: A text file (*.text) containing the assembly language code to be assembled
B)Output file: A text file(*.text) containing the assembled machine language code.

How to run the assembler:
1.Open the executable file Assembler.exe(use a compiler supporting C++11 or C++14).
2.Type in the name of the source code file. (Make sure the file is in the same folder as the assembler)[make sure START and END statements are present in the file otherwise error will be shown]. 
3.Errors while assembling (if any) will be displayed on the console.
4.An error-free assembly will be followed by a message “Assembled successfully”, and the object code in machine language will be generated as a text file in the same folder.

Assembly Language  
General Syntax: 
    START [location value/line number]
[label] [opcode] [operand]
.
.
END

Assembler Directives:
START  [Value] - value specifies the beginning location of the program
END – indicates the end for program execution
DW – to declare a word length variable
DS – to declare a data space for a variable

Opcodes:
The following opcodes are allowed:
Opcode	Description
CLA	Clear accumulator
LAC	Load into accumulator from address
SAC	Store accumulator contents into the address
ADD	Add address contents to accumulator contents
SUB	Subtract address contents from accumulator contents
BRZ	Branch to address if accumulator contains zero
BRN	Branch to address if accumulator contains a negative value
BRP	Branch to address if accumulator contains a positive value
INP	Read from the terminal and put in the address
DSP	Display value in the address on terminal
MUL	Multiply accumulator and address contents
DIV	Divide accumulator contents by address content. The quotient in R1 and remainder in R2
STP	Stop execution

Comments:
Single line comments only, using double forward slash.
    Syntax:            ADD x
            //This is a comment
Note: Mid instruction comments are not allowed

Labels:
Label name followed by a colon at the beginning of an instruction.
    Syntax:        label_name: ADD x

Operands:
For using a variable as an operand, use the variable name after the opcode.
For using a constant (literal), use ‘=’ followed by the constant value.
    Syntax:        ADD var_name
ADD =1

Error Reporting:
1.Unable to open file
2.Variable not declared
3.Non-existing label used
4.Invalid opcode
5.Multiple references assigned to a label
6.Start or End not found
Brief Review of Pass1() and Pass2 ()function
This program represents  a 2 pass assembler.
These passes are shown using pass1() and pass2() functions in this code 
1.Pass1()-
In this function the instruction is read line by line and then first of all the line is split into words.
The spit words are then checked if it represents a comment or not.
Comment is checked by successive “//”. If comment the whole line is ignored if not
Then the words are then processed with the check whether the word is ‘literal’, ’label’ , ‘variable’. These are stored according to their categories in the respective tables (literal table, label table, variable table).
2.Pass2()-
In this function the code is read again . Now the words are checked with the tables made in the  
first pass. If they are found then they are assigned addresses. If not then error is reported.
The operand are first checked if present are assigned opcode if not then error is reported.
Now when all the words are checked and the suitable values are assigned . 
Finally the machine code equivalent of the assembly code is saved in output .txt file and the work of the assembler is finished. 

