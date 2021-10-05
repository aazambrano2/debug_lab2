#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include <string.h> //ONLY USE strtok AND fgets

int32_t* reg; // Array of 32 32-bit registers
void init_regs();
void print_regs();
bool interpret(char* instr);
void write_read_demo();


bool equals(char* instr, char* match);
int parse_register(char* p);

void add_instruct(char* sum, char* op1, char* op2);
void addi_instruct(char* sum, char* op1, char* op2);
//void load_instruct(char* reg1, char* offset, char* reg2);
void load_instruct(char* reg1);
void store_instruct(char* reg1, char* offset, char* reg2);
#define MAXLINE 1000
/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	bool valid = false;
	//read_address WORKS HERE
	//int32_t read1 = read_address(0,"mem.txt");
	//printf("\nread before calling tokenizer: %d\n",read1);
	char** token = tokenize(instr);
	//read_address BREAKES HERE
	//int32_t read2 = read_address(0,"mem.txt");
	//printf("\nread after calling tokenizer: %d\n",read2);
	//TODO: Add check to validate if it is a valid instruction
	//Try to do string comparisons first
	
	if (equals(token[0],"ADD")){
		printf("ADD LOGIC\n");
		add_instruct(token[1],token[2],token[3]);
		valid = true;
	}

	else if (equals(token[0],"ADDI")){
		printf("ADDI LOGIC\n");
		addi_instruct(token[1],token[2],token[3]);
		valid = true;
	}
	else if(equals(token[0], "LW")){
		printf("LW LOGIC");
		//load_instruct(token[1],token[2],token[3]);
		load_instruct(token[1]);
		//read_address BREAKS HERE AS WELL
		valid = true;
	}
	else if(equals(token[0], "SW")){
		printf("SW LOGIC");
		store_instruct(token[1],token[2],token[3]);
		valid = true;
	}
	
	//EXTRA CREDIT
	return valid;
}

//CHECK OF USE CASES
//parsing an add instruction
void add_instruct(char* sum, char* op1, char* op2){
	int32_t address, op1_address, op2_address;
	//ADDRESSES FOR REGISTERS as integers 
	address = (int32_t) parse_register(sum);
	op1_address =(int32_t)  parse_register(op1);
	op2_address = (int32_t) parse_register(op2);
	//NOW TO USE REG ARRAY 
	int32_t data_to_write = reg[op1_address] + reg[op2_address];
	//UPDATE CONTETNS OF ADDRESS
	reg[address] = data_to_write;
}

void addi_instruct(char* sum, char* op1, char* op2){

        int32_t address, op1_address, immediate;

        //ADDRESSES FOR REGISTERS as integers
        address = (int32_t) parse_register(sum);
        op1_address =(int32_t)  parse_register(op1);
        immediate = (int32_t) parse_register(op2);

        //NOW TO USE REG ARRAY (using read_address and write_address)
        int32_t data_to_write = reg[op1_address] + immediate;
        reg[address] = data_to_write;
}

//void load_instruct(char* reg1, char* offset, char* reg2){
void load_instruct(char* reg1){
	int32_t load_reg, offset_int, base_reg;
	//TO INTEGERS
	//load_reg = (int32_t) parse_register(reg1);
        //offset_int = parse_register(offset);
        //base_reg = (int32_t) parse_register(reg2);
	
	//Debug print statement
	//printf("\n%d %d %d\n", load_reg, offset_int, base_reg);
	
	//BUG
	int32_t ad = 0; //testing purposes
	printf("Bug Found\n");
        reg[0] = read_address(ad,"mem.txt");
	//
	printf("\n%d\n",reg[load_reg]);
}

void store_instruct(char* reg1, char* offset, char* reg2){
	//TODO
}

//TODO: ADD DESCRIPTION
// *p => int
int parse_register(char* p){
	char* copy_number = p;
	//START AT NUMBER IF USING REGISTER
	printf("\ncopy_number=%s\n",p);
	if(*p == 'X')
		p = p + 1;
	printf("\np=%s\n",p);
	//SAVE WHERE YOU STARTED
	char* s = copy_number;
	while((*copy_number = *p) != '\0'){
		++copy_number;
		++p;
	}
	//GO PACK TO THE START OF YOUR NEW STRING
	copy_number = s;
	printf("\ncopy_number=%s\n",copy_number);
	//have to atoi function get you the integer
	int reg = atoi(copy_number);
	return reg;
}


//TODO: Add Description
bool equals(char* instr, char* match){
	while(*instr == *match){ 
		++instr;
		++match;
	}
	if(*instr != '\0'){
		return false;
	}
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */

void write_read_demo(){
	//REG 
	int32_t data_to_write = 68; // equal to 4095
	int32_t address = 2; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	//reg[address] = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}


/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
    int col_size = 10;
    for(int i = 0; i < 8; i++){
        printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
        printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
        printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
        printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
    }
}

/**
 * Your code goes in the main
 *
 */
/*
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	//TODO: BUG
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");
		break;
		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
*/

int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();
	print_regs();
	char line[MAXLINE];
	printf("Please enter the INSTRUCTION:\n");
    	printf("> ");
	//bool complete = false;
    	//get user input
    	if(*fgets(line,MAXLINE,stdin)!= '\n'){
            printf("USER INPUT: %s",line);
            interpret(line);
	    print_regs();
   	}
	return 0;
}

