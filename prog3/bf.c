#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define DEBUG if(FALSE)
#define MAX_CODE_LEN 100000
#define MAX_MEM 1000

//Operations
#define INC_DATA_PTR '>'
#define DEC_DATA_PTR '<'
#define INC_DATA_VAL '+'
#define DEC_DATA_VAL '-'
#define STDOUT_DATA '.'
#define STDIN_DATA ','
#define BEGIN_LOOP '['
#define END_LOOP ']'
#define STDIN_STR ';'
#define STDOUT_DMP ':'
#define BEGIN_STR '('
#define END_STR ')'
#define CODE_TERM 0

// Data Structures 
int *code;
int *data;
int *stack;

//Operation Pointers
int *inst_ptr;
int *data_ptr;
int *STACK_HEAD;

// Allocate memory for the code, mem, and stack
// Pointers are set to the begining of allocated memory
void init()
{
	code  = calloc(MAX_CODE_LEN, sizeof(char));
	data   = calloc(MAX_MEM, sizeof(char));
    stack = calloc(MAX_MEM, sizeof(int*));

	inst_ptr   = code;
	data_ptr   = data;
	STACK_HEAD = stack; 
	
	DEBUG printf("STACK START: %d\n", stack);
	DEBUG printf("DATA START: %d\n", data);
}

void destroy()
{
	memset(code, 0, sizeof(code));
	memset(data, 0, sizeof(data));
	memset(stack, 0, sizeof(stack));
	
	free(code);
	free(data);
	free(stack);
}

// Accepts an input stream and reads
// input char by char
void input(FILE *stream)
{
	int inst;
	while((inst = fgetc(stream)) != EOF)
	{
		if(stream == stdin && inst == '\n') break;
		if(inst != '\n')
		{	
			*(inst_ptr) = inst;
			inst_ptr++;
		}	
	}
	*(inst_ptr) = CODE_TERM;
	inst_ptr = code;
}

// Accepts filename and reads the input
void load_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	if(file == 0)
	{
		printf("Unable to read file.\n");
		destroy();
		exit(EXIT_SUCCESS);
	}
	else {
		DEBUG printf("READING FILE\n");
		input(file);
	}
}

// Stack Operations
void stack_push(int *addr)
{	
	DEBUG printf("START LOOP: %d\n", addr);
	if((STACK_HEAD - stack) != MAX_MEM)
	{
		STACK_HEAD++;
		*(STACK_HEAD) = addr;
		DEBUG printf("STACK PUSH: %d->%d\n", STACK_HEAD - stack, *STACK_HEAD);
	}
	else {
		printf("Stack is full.\n");
		destroy();
		exit(EXIT_SUCCESS);
	}
}

int stack_pop()
{
	if((STACK_HEAD - stack))
	{
		int ret = *(STACK_HEAD);
		--STACK_HEAD;
		DEBUG printf("STACK POP: %d->%d\n", STACK_HEAD - stack, *STACK_HEAD);
		return ret;
	}
	else {
		printf("Stack is empty.\n");
		destroy();
		exit(EXIT_SUCCESS);
	}
}

// Operation Functions
void next_inst() { ++inst_ptr; }
void inc_data_ptr() { ++data_ptr; DEBUG printf(" -DATA PTR: %d\n", data_ptr);}
void dec_data_ptr() { --data_ptr; DEBUG printf(" -DATA PTR: %d\n", data_ptr);}
void inc_data_val() { ++*data_ptr; DEBUG printf(" -DATA VAL: %d\n", *data_ptr);}
void dec_data_val() { --*data_ptr; DEBUG printf(" -DATA VAL: %d\n", *data_ptr);}
void stdout_data() { putchar(*data_ptr); DEBUG printf(" -DATA PTR: %d\n", data_ptr); }
void stdin_data() { *data_ptr=getchar(); }

void begin_loop()
{
	int *LOOP_START = inst_ptr - 1;
	if (!*(data_ptr))
	{
		while(*(inst_ptr) != END_LOOP)
			next_inst();
		stack_pop();
	}
	else if (LOOP_START != *STACK_HEAD)
	{
		stack_push(LOOP_START);
	}
}

void end_loop()
{
	DEBUG printf("END LOOP JUMP: %d\n", inst_ptr);
	if(!*data_ptr)
		stack_pop();
	else
		inst_ptr = *(STACK_HEAD);
}

void stdin_str()
{
	char str[MAX_MEM];
	fgets(str, MAX_MEM-1, stdin);
	
	int i = 0;
	int *temp_data_ptr = data_ptr;
	
	while(str[i] != NULL)
	{
		*temp_data_ptr = str[i];
		temp_data_ptr++;
		i++;
	}
}

void stdout_dmp()
{
	//printf("%s", data_ptr);
	int *temp_data_ptr = data_ptr;
	while(*temp_data_ptr != NULL)
	{
		putchar(*temp_data_ptr);
		temp_data_ptr += 1;
	}
}

void begin_str()
{
	char str[MAX_MEM];
	int i = 0;
	next_inst();
	while((*inst_ptr) != END_STR)
	{
		str[i++] = *(inst_ptr);
		next_inst();
	}
	str[i] = NULL;
	DEBUG printf("%s\n", str);

	if(str[0] == '0' && str[1] == 'x')
	{
		DEBUG printf("UN-HEX\n");
		char hex[MAX_MEM];
		int j = 2;
		int i = 0;
		while(str[j] != NULL)
		{
			hex[i++] = str[j++];
		}
		
		char *ptr;
		int ret;
		ret = strtol(str, &ptr, 16);
		*data_ptr = ret;
	} 
	else{
		DEBUG printf("INJECT STRING\n");
		int i = 0;
		int *temp_data_ptr = data_ptr;
		while(str[i] != NULL)
		{
			*temp_data_ptr = str[i];
			DEBUG printf("TEMP_DATA_PTR: %d->%c\n", temp_data_ptr, *temp_data_ptr);
			i++;
			temp_data_ptr++;
		}
		*temp_data_ptr = NULL;
	}
}

void invalid_inst(char inst)
{
	printf("%c is an invalid instruction.\n", inst);
	exit(EXIT_SUCCESS);
}


void process_inst(char inst)
{
	switch(inst)
	{
		case INC_DATA_PTR :
			DEBUG printf("INC_DATA_PTR\n");
			inc_data_ptr();
			break;

		case DEC_DATA_PTR :
			DEBUG printf("DEC_DATA_PTR\n");
			dec_data_ptr();
			break;

		case INC_DATA_VAL :
			DEBUG printf("INC_DATA_VAL\n");
			inc_data_val();
			break;

		case DEC_DATA_VAL :
			DEBUG printf("DEC_DATA_VAL\n");
			dec_data_val();
			break;

		case STDOUT_DATA :
			DEBUG printf("STDOUT_DATA\n");
			stdout_data();
			break;

		case STDIN_DATA :
			DEBUG printf("STDIN_DATA\n");
			stdin_data();
			break;

		case BEGIN_LOOP :
			DEBUG printf("BEGIN_LOOP\n");
			begin_loop();
			break;

		case END_LOOP :
			DEBUG printf("END_LOOP\n");
			end_loop();
			break;
	
		case STDIN_STR :
			DEBUG printf("STDIN_STR\n");
			stdin_str();
			break;
	
		case STDOUT_DMP :
			DEBUG printf("STDOUT_DMP\n");
			stdout_dmp();
			break;

		case BEGIN_STR :
			DEBUG printf("BEGIN_STR\n");
			begin_str();
			break;

		default :
			invalid_inst(inst);
		}
}

void process_code()
{
	while(*(inst_ptr) != CODE_TERM)
	{
		char inst = *(inst_ptr);
		process_inst(inst);
		next_inst();
	}
}

int main(int argc, char *argv[]){
	if(argc < 2)
	{
		DEBUG printf("READING STDIN\n");
		printf("Brainfuck Extended Interpreter\n");
		while(TRUE)
		{
			init();
			printf(">>> ");
			input(stdin);
			process_code();
			printf("\n");
			destroy();
		}
	} 
	else {
		init();
		load_file(argv[1]);
		process_code();
		destroy();
	}
	return 0;
}
