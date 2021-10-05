/**
AARON ZAMBRANO

LAB 1

Last Edited: 9/19/2021 12:11 AM
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
# define MAXLINE 1000


char** tokenize(char* str);
char *word_start(char* str);
char *end_word(char* str);
int count_token(char*str);
char *copy_str(char *intStr, short len);
void print_all_tokens(char** tokens,int length);

/*
int main(){
    char ** start;
    int len;
    char line[MAXLINE]; // current input line 
    printf("Please enter the input string:\n");
    printf("> ");
    //get user input
    if(*fgets(line,MAXLINE,stdin)!= '\n'){
	    printf("USER INPUT: %s",line);
	    start = tokenize(line);
   }
    return 0;
}
*/
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
    
    return c == ' ' || c == '\t';
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
    return c != ' ' || c != '\t' || c != '\0';
}



/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){
    char* s = str;
    while(non_delim_character(*s)){
	if(delim_character(*s))
	    break;
        ++s;
    }
    return s + 1;
}
/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    char* s = str;
    while(non_delim_character(*s)){
	if(delim_character(*s))
	    break;
        ++s;
    }
    return s;
}

/* Returns the count of the number of words or tokens*/
int count_tokens(char* str){
    int acc;
    acc = 0;
    while(*str != '\0'){
        if(delim_character(*str))
	  ++acc;
        ++str;
    }
    if (*str == '\0')
       ++acc;
    return acc;
}
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
inStr is start i believe
*/
char *copy_str(char *inStr, short len){
    char* new_string = (char*) malloc((len)*sizeof(char));
    char* s = new_string;
   // printf("TOKEN LENGTH %d",len);
    while((*new_string = *inStr) != ' '){
        ++inStr;
        ++new_string;
    }

    *new_string ='\0';
    //Go back to the intial character of the tokenized string
    new_string = s;
    return new_string;
}

/*Returns a double pointer that references the base of a pointer array
where every pointer points to the base of character arrays*/
char** tokenize(char* str){
    char* start;
    char* end;
    char* current_string;
    int t_count,sub_length, i;
    t_count = count_tokens(str);
    //Initialize token array
    char **ptr = malloc(t_count*sizeof(char*));
    //Have a double pointer poiting to the base of pointer array
    char **initial = ptr;
    start = str;
    i = 0;
    while(*str != '\0'){
        if(delim_character(*str)){
		//update end
		end = end_word(start);
		sub_length = (end - start) + 1;
	        //store this to a token
		current_string = copy_str(start,sub_length);
                ptr[i] = current_string;
	        //update start
	        start = word_start(str);
	        //make sure to start at the next spaced word
	        str = start;
		++i;
	}
        ++str;
    }
    //last spaced word case
    if(*str == '\0'){
	end = str;
        printf("%s\n",end);
	sub_length = end - start;
        //store to tokenizer
	current_string = copy_str(start,sub_length);
        ptr[i] = current_string;
    }
    print_all_tokens(initial,t_count);
    return initial;
}

/*Prints all tokenized tokens given the pointer array and the number of tokens
representing the length of the pointer array*/
void print_all_tokens(char** tokens,int length){
    int i;
    i = 0;
    
    for(i = 0; i< length; ++i){
    	printf("Tokens[%d]: %s\n",i,tokens[i]);
    }
}



