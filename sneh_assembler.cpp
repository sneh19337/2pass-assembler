#include<string>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<sstream>
#include<bitset>
using namespace std;


int pc=0;				//Program Counter
bool Start=false;		//Program Start
bool End=false;			//Program End


struct symbol
{
	string name;
	int addr;
	int value;
	symbol *next;

	void init()
	{
		name="";
		addr=-1;
		value=0;
		next=NULL;
	}

	void disp()
	{
		std::cout<<name<<"  ";
		std::cout<<value<<"  ";
		std::cout<<addr<<"\n";
	}
} ;

class linkedlist
{
private:
	symbol *head,*tail;

public:
	linkedlist()
	{
		head = NULL;
		tail = NULL;
	}

	~linkedlist()
	{
		//look at this later...
	}

	void insert(int value)
	{
		/* To insert a new literal in table. */

		symbol *temp = new symbol;
		temp->init();
		temp->value = value;


		if(head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = tail->next;
		}
	}

	void insert(string name)
	{
		/*To insert a new symbol in table */

		symbol *temp = new symbol;
		temp->init();
		temp->name = name;


		if(head == NULL)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = tail->next;
		}
	}

	void display()
	{
		/* To display table contents. */

		symbol *temp=head;
		while(temp!=NULL)
		{
			temp->disp();
			temp=temp->next;
		}
	}

	symbol* search(string name)
	{
		/* To search for a name in the symbol tables */

		if(head==NULL||tail==NULL)
			return NULL;
		else if(tail->name==name)
			return tail;
		else
		{
			symbol *temp=head;
			while(temp!=NULL)
			{
				if(temp->name==name)
					return temp;
				temp=temp->next;
			}
			return NULL;
		}
	}

	symbol* search(int value)
	{
		/* To search for a value in the literal table */

		if(head==NULL||tail==NULL)
			return NULL;
		else if(tail->value==value)
			return tail;
		else
		{
			symbol *temp=head;
			while(temp!=NULL)
			{
				if(temp->value==value)
					return temp;
				temp=temp->next;
			}
			return NULL;
		}
	}

	void addval(string name, int value)
	{
		/* To add value of a symbol/literal in the table. */

		symbol *temp=search(name);
		temp->value=value;
	}

	void addaddr(string name, int addr)
	{
		/* To add address of a symbol in the table. */

		symbol *temp=search(name);
		temp->addr=addr;
	}

	void checkaddr(string msg="Symbol")
	{
		/* To check addresses and display error if symbol unused. */

		symbol *temp=head;
		while(temp!=NULL)
		{
			if(temp->addr==-1)
			{
				std::cout<<"\nError: "<<msg<<"'"+temp->name+"'"<<"not defined";
			}
			temp=temp->next;
		}
	}

	void assignaddr()
	{
		/* For assigning addresses to literals in the end. */

		symbol *temp=head;
		int newadr=::pc;
		while(temp!=NULL)
		{
			if(temp->addr==-1)
			{
				temp->addr=newadr;
				++newadr;
			}
			temp=temp->next;
		}
	}

	/* int printlit()
	{

		symbol *temp=head;
		while(temp!=NULL)
		{
			opfile<<convert(lit_tab.search(token)->addr)<<"\n";
			temp=temp->next;
		}
	}  */

} var_tab,lab_tab,lit_tab;



//converting address to binary form
// string convert(int pc)
// {
// 	string bin;
// 	for (int i=pc;i>0;i=i/2)
// 	{
// 		bin=to_string(i%2);
// 	}
// 	if(bin.length()<8)
// 		bin=string(8-bin.length(),'0').append(bin);
// 	return bin;
// }

// int convert(int pc)
// {
// 	int binaryNumber = 0;
// 	int remainder, i = 1, step = 1;

// 	while (pc!=0)
// 	{
// 		remainder = pc%2;
// 		pc/= 2;
// 		binaryNumber += remainder*i;
// 		i *= 10;
// 	}
// 	return binaryNumber;

// }





int countDigit(int n)
{
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}


int convert(int n)
{
std::string binary = std::bitset<8>(n).to_string(); //to binary
    std::cout<<binary<<"\n";

   unsigned long decimal = std::bitset<8>(binary).to_ulong();
    std::cout<<decimal<<"\n";

}
//std:: cout << printBinary(x, 8) << std::endl;
struct mnemonic
{
	string mnemonics;
	string binary ;
} mot[13];

void opcodeassign()
{
	//mot-machine opcode tabulated
	mot[0] = {"CLA","0000"};
	mot[1] = {"LAC","0001"};
	mot[2] = {"SAC","0010"};
	mot[3] = {"ADD","0011"};
	mot[4] = {"SUB","0100"};
	mot[5] = {"BRZ","0101"};
	mot[6] = {"BRN","0110"};
	mot[7] = {"BRP","0111"};
	mot[8] = {"INP","1000"};
	mot[9] = {"DSP","1001"};
	mot[10] = {"MUL","1010"};
	mot[11] = {"DIV","1011"};
	mot[12] = {"STP","1100"};
}

int checkmot(string opcode)
{
	int num= -1;
	for(int j=0;j<13;j++)
	{
		if(mot[j].mnemonics == opcode)
		{
			num = j;
			break;
		}
	}
	return num;
}



//______________________________________________________________________

int pass1()
{
	fstream file;
	file.open("t.txt",ios::in);

	/* To check successful opening of the file */
	if(!file)
	{
		std::cout<<"Error: Unable to open file.";
	}
	else
	{
		string instr;

		while(getline(file,instr))
		{
			/* Checking for comment */
			if(instr[0]=='/' && instr[1]=='/')
			{
				continue;
			}

			int i=0;
			string token;
			string opcode;
			string label;
			string operand;
			int literal;
			string var;

			/* Reading first value/word */
			for(i=0;instr[i]!=':' && instr[i]!=' ' && instr[i]!='\0';i++)
			{
				token+=instr[i];
			}

			if(!Start)
			{
				if(token=="START")
					::Start=true;
				else
					continue;
			}
			else
			{
				if(token=="END")
				{
					/* If first word is END */
					::End=true;
					break;
				}
				else
				{
					/*
						Label, nothing or variable is found
					*/

					if(instr[i]==':')
					{
						/* If label is found, adding to label table */

						label=token;
						symbol *temp=lab_tab.search(label);
						if(temp==NULL)
						{
							lab_tab.insert(label);
							lab_tab.addaddr(label,::pc);
						}
						else if(temp->addr==-1)
						{
							lab_tab.addaddr(label,::pc);
						}
						else
						{
							std::cout<<"\nError: Multiple references assigned to label '"<<label<<"'";
						}
						i++;
					}

					else if(token=="")
					{
						/* If nothing is found, move forward to read opcode */

						while(instr[i]==' ')
						{
							i++;
						}
					}

					else
					{
						/* Otherwise, must be a variable */
						var=token;
					}

					while(instr[i]==' ')
						i++;

					//Reading opcode
					for(;instr[i]!=' ' && instr[i]!='\0';i++)
					{
						opcode+=instr[i];
					}
					/*
						check opcode validity
					*/

					while(instr[i]==' ')
						i++;

					//Reading operands (if any)
					for(;instr[i]!=' ' && instr[i]!='\0';i++)
					{
						operand+=instr[i];
					}

					if(operand.empty() && opcode!="CLA")
					{
						/* If no operand found, give error. */
						std::cout<<"\nError: Operand not specified (line "<<::pc<<")";
					}
					else if(opcode=="BRP"||opcode=="BRN"||opcode=="BRZ")
					{
						/* If operand is label, add to label table. */
						if(lab_tab.search(operand)==NULL)
							lab_tab.insert(operand);

					}
					else if(opcode=="DW")
					{
						/* If variable declaration found, adding var to variable table */

						var_tab.addval(var,stoi(operand));
						var_tab.addaddr(var,::pc);
					}
					else
					{
						if(operand[0]=='=')
						{
							/* If Literal found in operand, adding to literal table */
							string strlit;
							for(int i=1;i<operand.length();i++)
								strlit+=operand[i];

							literal=stoi(strlit);

							lit_tab.insert(literal);
						}
						else
						{
							/* Else, would be a variable. Adding to variable table. */
							if(var_tab.search(operand)==NULL)
								var_tab.insert(operand);
						}


					}

				}
				++::pc;
			}
		}
		if(Start)
		{
			if(!End)
			{
				std::cout<<"Warning: 'END' not specified.";
			}
			var_tab.checkaddr("Variable");
			lab_tab.checkaddr("Label");
			lit_tab.assignaddr();
		}
		else
		{
			std::cout<<"Warning: 'START' not specified. ";
		}


		//Just for display and testing purpose...
		std::cout<<"\n\nVariable table:\n";
		var_tab.display();
		std::cout<<"\nLabel table:\n";
		lab_tab.display();
		std::cout<<"\nLiteral table:\n";
		lit_tab.display();
	}

	file.close();

	return 0;
}

int pass2()
{
	fstream file, opfile;

	file.open("t.txt",ios::in);
	opfile.open("output.txt",ios::out);

	/* To check successful opening of the file */
	if(!file)
	{
		std::cout<<"Error: Unable to open file.";
	}
	else
	{
		string instr;
		::pc=0;
		::Start=false;
		::End=false;

		while(getline(file,instr))
		{
			/* Checking for comment */
			if(instr[0]=='/' && instr[1]=='/')
			{
				continue;
			}

			int i=0;
			string token;
			string opcode;
			string label;
			string operand;
			int literal;
			string var;

			/* Reading first value/word */
			for(i=0;instr[i]!=':' && instr[i]!=' ' && instr[i]!='\0';i++)
			{
				token+=instr[i];
			}

			if(!Start)
			{
				if(token=="START")
					::Start=true;
				else
					continue;
			}
			else
			{
				if(token=="END")
				{
					/* If first word is END */
					::End=true;
					break;
				}
				else
				{
					/*
						Label, nothing or variable is found
					*/

					if(instr[i]==':')
					{
						/* If label is found, adding to label table */
						i++;
					}

					while(instr[i]==' ')
						i++;

					//Reading opcode
					for(;instr[i]!=' ' && instr[i]!='\0';i++)
					{
						opcode+=instr[i];
					}


					while(instr[i]==' ')
						i++;

					//Reading operands (if any)
					for(;instr[i]!=' ' && instr[i]!='\0';i++)
					{
						operand+=instr[i];
					}

					if(opcode=="DW")
					{
						/* If variable declaration found, adding var to variable table */

						opfile<<convert(var_tab.search(token)->addr)<<"\n";
					}
					else
					{
						int opcn=checkmot(opcode);
						if(opcn==-1)
						{
							std::cout<<"Error: Invalid opcode '"<<opcode<<"'. (line "<<::pc<<")";
						}
						else
						{
							opfile<<mot[opcn].binary;

							if(opcn==0)
							{
								opfile<<"\n";
							}
							else if(opcn==5||opcn==6||opcn==7)
							{
								/* If operand is label, writing address from label table. */

								opfile<<" "<<convert(lab_tab.search(operand)->addr)<<"\n";


							}
							else if(operand[0]=='=')
							{
								/* If Literal found in operand, write address from literal table */
								string strlit;
								for(int i=1;i<operand.length();i++)
									strlit+=operand[i];

								literal=stoi(strlit);

								opfile<<" "<<convert(lit_tab.search(literal)->addr)<<"\n";
							}
							else
							{
								/* Else, would be a variable. Writing address from variable table. */

								opfile<<" "<<convert(var_tab.search(operand)->addr)<<"\n";
							}
						}

					}



				}
				++::pc;
			}
		}
		/* if(Start)
		{
			if(!End)
			{
				std::cout<<"Warning: 'END' not specified.";
			}
			var_tab.checkaddr("Variable");
			lab_tab.checkaddr("Label");
			lit_tab.assignaddr();
		}
		else
		{
			std::cout<<"Warning: 'START' not specified. ";
		} */




		//Just for display and testing purpose...
		/* std::cout<<"\n\nVariable table:\n";
		var_tab.display();
		std::cout<<"\nLabel table:\n";
		lab_tab.display();
		std::cout<<"\nLiteral table:\n";
		lit_tab.display();	 */
	}

	file.close();

	return 0;
}

int main()
{
	opcodeassign();
	int p1=pass1();
	pass2();
	return 0;
}

