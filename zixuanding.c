// C program for linked list implementation of stack 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
  
// A stack that contains strings
//Learnt how to implement stack in C using https://www.geeksforgeeks.org/stack-data-structure-introduction-program/ accessed on 6/11/2019
typedef struct StrStack { 
    char* substring; 
    struct StrStack *next; 
}StrStack; 
  
StrStack* createNode(char* substring) 
{ 
    StrStack* stacknode = (StrStack*)malloc(sizeof(StrStack)); 
    stacknode->substring = substring; 
    stacknode->next = NULL; 
    return stacknode; 
} 
  
int isEmpty(StrStack* root) 
{ 
    return !root; 
} 
  
void push(StrStack** root, char* substring) 
{ 
    StrStack* stacknode = createNode(substring); 
    stacknode->next = *root; 
    *root = stacknode; 
} 
  
char* pop(StrStack** root) 
{ 
    if (isEmpty(*root)) 
        return "\0"; 
    StrStack* temp = *root; 
    *root = (*root)->next; 
    char* popped = temp->substring; 
    free(temp); 

    return popped; 
} 
  
char* peek(StrStack* root) 
{ 
    if (isEmpty(root)) 
        return "\0"; 
    return root->substring; 
} 

void display(StrStack* root){
    if (isEmpty(root)) 
        printf("Empty Stack!\n"); 
    else{
        StrStack *current = root;
        while (current) {
        printf("%s ", current->substring);
        current = current->next; 
        }
    }
    printf("\n");
}

int is_bracket(char a){
    if(a == '('){
        return 1;
    }else if(a == ')'){
        return 1;
    }
    return 0;
}

int is_sqrt(char* arr,int z){
    if(arr[z] == 'S'&& arr[z+1] == 'Q'&& arr[z+2]== 'R'&&arr[z+3] == 'T'&& arr[z+4] == '('){
        return 1;
    }
    return 0;
}
//whether the slice of a string is either sqr,sin,cos,tan,log(all of those functions are 3-character long)
int is_len_three(char* arr,int z){
    if(arr[z] == 'S'&& arr[z+1] == 'Q'&& arr[z+2]== 'R'&& arr[z+3] == '('){
        return 1;
    }else if(arr[z] == 's'&& arr[z+1] == 'i'&& arr[z+2]== 'n'&& arr[z+3] == '('){
        return 1;
    }else if(arr[z] == 'c'&& arr[z+1] == 'o'&& arr[z+2]== 's'&& arr[z+3] == '('){
        return 1;
    }else if(arr[z] == 't'&& arr[z+1] == 'a'&& arr[z+2]== 'n'&& arr[z+3] == '('){
        return 1;
    }else if(arr[z] == 'l'&& arr[z+1] == 'o'&& arr[z+2]== 'g'&& arr[z+3] == '('){
        return 1;
    }
    return 0;
}

int is_operator(char* arr,int z){
    if(arr[z] == '+'|| arr[z] == '-'|| arr[z]== '*'|| arr[z] == '/'){
        return 1;
    }
    return 0;
}

int isleft_bracket(char* arr){
    if(strcmp(arr,"(") == 0){
        return 1;
    }
    return 0;
}

//all those functions only take one operand
int is_unary(char *arr){
    if(strcmp(arr,"SQR(")==0){
        return 1;
    }else if(strcmp(arr,"SQRT(")==0){
        return 1;
    }else if(strcmp(arr,"sin(")==0){
        return 1;
    }else if(strcmp(arr,"cos(")==0){
        return 1;
    }else if(strcmp(arr,"tan(")==0){
        return 1;
    }else if(strcmp(arr,"log(")==0){
        return 1;
    }
    return 0;
}

int isleft_associative(char *arr){
    if(strcmp(arr,"-")==0){
        return 1;
    }else if(strcmp(arr,"/")==0){
        return 1;
    }else if(strcmp(arr,"+")==0){
        return 1;
    }else if(strcmp(arr,"*")==0){
        return 1;
    }
    return 0;
}

int is_variable(char* arr,int z,char* variable){
    char* substring = strndup(arr+z,strlen(variable));
    if(strcmp(substring,variable)==0){
        return 1;
    }
    return 0;
}

int check_precedence(char *arr){
    if(is_unary(arr) == 1){
        return 2;
    }else if(strcmp(arr,"+") == 0 ||strcmp(arr,"-") == 0){
        return 2;
    }else if(strcmp(arr,"*") == 0 ||strcmp(arr,"/") == 0){
        return 3;
    }
    return 0;
}

int compare_precedence(char* a,char* b){
    if(check_precedence(a)>check_precedence(b)){
        return 1;
    }else if(check_precedence(a) == check_precedence(b)){
        return 0;
    }else{
        return -1;
    }
}

//turn an infix expression into a postfix expression
//according to the shunting yard algorithm,https://en.wikipedia.org/wiki/Shunting-yard_algorithm,accessed on 6/11/2019
StrStack* infix_to_postfix(char* arr,char choice,char* variable,char* result){
    StrStack* stack_output = NULL;
    StrStack* stack_operator = NULL;
    int z=0;
    while(z<strlen(arr)){
        char* substring;
        if(arr[z] == ' '){
            z++;
            continue;
        //check whether there is a empty value, all empty values should be surrounded by brackets
        }else if(arr[z] == '('&&arr[z+1] == '-'&&isdigit(arr[z+2])){
            char* zero = "0";
            char* left_bracket  = "(";
            char* minus = "-";
            push(&stack_output,zero);
            push(&stack_operator,left_bracket);
            push(&stack_operator,minus);
            z+=2;
        }
        //check for operators
        else if(!isdigit(arr[z]) && is_bracket(arr[z])==0){
            if(is_sqrt(arr,z)){
                substring = strndup(arr+z,5);
                z+=5;
            }else if(is_len_three(arr,z) == 1){
                substring = strndup(arr+z,4);
                z+=4;
            }else if(is_operator(arr,z) == 1){
                substring = strndup(arr+z,1);
                z++;
            }else{
                if(choice == '2'){
                    if(is_variable(arr,z,variable)==1){
                        substring = result;
                        z += strlen(variable);
                        push(&stack_output,substring);
                        continue;
                    }
                }
                printf("Invalid character discovered.\n");
                z++;
                continue;
            }
            if(isEmpty(stack_operator)){
                push(&stack_operator,substring);
            }else if(is_unary(substring)==1){
                push(&stack_operator,substring);
            }else if(is_unary(peek(stack_operator))==1){
                push(&stack_operator,substring);
            }
            else{
                int k = compare_precedence(substring,peek(stack_operator));
                if(k<0){
                    char* p = pop(&stack_operator);
                    push(&stack_output,p);
                    push(&stack_operator,substring);
                }else if(k == 0 && isleft_associative(peek(stack_operator))==1){
                    char* p = pop(&stack_operator);
                    push(&stack_output,p);
                    push(&stack_operator,substring);
                }else{
                    push(&stack_operator,substring);
                }
                }
        }else if(arr[z] == '('){ 
            char* left_bracket = "(";
            push(&stack_operator,left_bracket);
            z++;
        }else if(arr[z] == ')'){
            z++;
            while(stack_operator){
                if(is_unary(peek(stack_operator))){
                    char* p = pop(&stack_operator);
                    push(&stack_output,p);
                    break;
                }else if(isleft_bracket(peek(stack_operator))==1){
                    pop(&stack_operator);
                    break;
                }
                char* p = pop(&stack_operator);
                push(&stack_output,p);
            }
        }else if(isdigit(arr[z])){
            int start = z;
            z++;
            int digit = 1;
            //operands involve in the calculation can be several digits long
            if(arr[z] == '.'){
                digit++;
                z++;
            }
            while(isdigit(arr[z])){
                digit++;
                z++;
                if(arr[z] == '.'){
                    digit++;
                    z++;
                }
            }
            substring = strndup(arr+start,digit);
            push(&stack_output,substring);
        }
        }


    while(stack_operator){
        push(&stack_output,peek(stack_operator));
        pop(&stack_operator);
    }
    return stack_output;
}

//reverse the stack so we can access from the beginning
StrStack* reverse(StrStack* stack_output){
    StrStack* reversed_stack = NULL;
    char* token;
    while(stack_output){
        token = pop(&stack_output);
        push(&reversed_stack,token);
    }
    return reversed_stack;
}

//define a stack which contains doubles
typedef struct NumStack{
    double data;
    struct NumStack *next;
}NumStack;

NumStack* createNumNode(double data) 
{ 
    NumStack* numnode = (NumStack*)malloc(sizeof(NumStack)); 
    numnode->data = data; 
    numnode->next = NULL; 
    return numnode; 
} 
  
int isnumEmpty(NumStack* root) 
{ 
    return !root; 
} 
  
void push_num(NumStack** root, double data) 
{ 
    NumStack* numnode = createNumNode(data); 
    numnode->next = *root; 
    *root = numnode; 
} 
  
double pop_num(NumStack** root) 
{ 
    if (isnumEmpty(*root)) 
        return 0; 
    NumStack* temp = *root; 
    *root = (*root)->next; 
    double popped = temp->data; 
    free(temp); 

    return popped; 
} 
  
double peek_num(NumStack* root) 
{ 
    if (isnumEmpty(root)) 
        return 0; 
    return root->data; 
} 

double token_to_double(char *token){
    int z = 0;
    double value = 0;
    while(z<strlen(token)){
        int digit = token[z]-'0';
        value = value*10 + digit;
        z++;
        if(token[z]=='.'){
            z++;
            break;
        }
    }
    double dp=1.000000;
    while(z<strlen(token)){
        int digit = token[z]-'0';
        value = value + digit*pow(0.100000,dp);
        dp++;
        z++;
    }
    return value; 
}

void unary_operator(char *token,NumStack* numstack){
    double operand = pop_num(&numstack);
    double result = 0.000000;
    if(strcmp(token,"SQRT(")==0){
        if(operand<=0){
            printf("Calculation is not valid since operand is not positive.\n");
        }
        result = sqrt(operand);
    }else if(strcmp(token,"SQR(")==0){
        result = pow(operand,2.00);
    }else if(strcmp(token,"sin(")==0){
        result = sin(operand);
    }else if(strcmp(token,"cos(")==0){
        result = cos(operand);
    }else if(strcmp(token,"tan(")==0){
        result = tan(operand);
    }else if(strcmp(token,"log(")==0){
        result = log(operand);
    }
    push_num(&numstack,result);  
}

//inplement the reverse polish notation we created just now
//learnt how to implement reverse polish notation at https://www.youtube.com/watch?v=7ha78yWRDlE By Computerfile Uploaded on 21 Mar 2014 Accessed on 6/11/2019
double operate_rpn(StrStack* output){
    NumStack* numstack = NULL;
    while(output){
        char* token = pop(&output);
        if(isdigit(token[0])){
            double d_token = token_to_double(token);
            push_num(&numstack,d_token);
        //check for negative numbers
        }else if(token[0]=='-'&&isdigit(token[1])){
            char* positive = strndup(token+1,strlen(token)-1);
            double d_token = token_to_double(positive);
            d_token = -d_token;
            push_num(&numstack,d_token);
        }else{
            double result = 0.000000;
            if(strlen(token) == 1){
                double operand2 = pop_num(&numstack);
                double operand1 = pop_num(&numstack);
                double result = 0.00;
                if(strcmp(token,"+")==0){
                    result = (double)operand1+operand2;
                }else if(strcmp(token,"-")==0){
                    result = operand1-operand2;
                }else if(strcmp(token,"*")==0){
                    result = operand1*operand2;
                }else if(strcmp(token,"/")==0){
                    result = operand1/operand2;
                }
                push_num(&numstack,result);
            }else{
                unary_operator(token, numstack);
                }
            }
    }
    return peek_num(numstack);
}

int check_balance(char* arr){
    int b_left = 0,b_right = 0;
    for(int z=0;z<strlen(arr);z++){
        if(arr[z] == '('){
            b_left++;
        }else if(arr[z] == ')'){
            b_right++;
        }
    }
    if(b_right == b_left){
        return 1;
    }else{
        return 0;
    }

}
void empty_input_buffer(){
    char ch;
    while ((ch = getchar()) != '\n');
}

char user_choice(){
    char cho[3];
    fgets(cho,2,stdin);
    empty_input_buffer();
    char choice = cho[0];
    return choice;
}

char* user_input(){
    char *arr = (char*)malloc(sizeof(char)*1000);
    fgets(arr,1000,stdin);
    int z=0;
    for(int z=0;z<1000;z++){
        if(arr[z]=='\n'){
            arr[z] = '\0';
        }
    }
    return arr;
}

char* input_instructions(){
    printf("Please enter an expression which is less than 1000 characters.\n");
    printf("The operators you can use are the following:\n");
    printf("Negative number should be surrounded by brackets.\n");
    printf("+ - * / sin() cos() tan() log() SQRT() SQR()\n");
    printf("sin,cos and tan are in radian\n");
    char* input = user_input();
    return input;
}

char* check_input(char* arr){
    while(check_balance(arr)==0){
        printf("The brackets in your input is not balanced. Please input again.\n");
        arr = user_input();
    }
    return arr;
}

double calculator(char*arr,char choice,char* variable,char* result){
    StrStack* reverse_polish_notation = infix_to_postfix(arr,choice,variable,result);
    if(reverse_polish_notation == NULL){
        printf("Invalid Input!\n");
        return 0.00;
    }else{
        //a stack only allow access from end so we need to reverse it
        //we inplement the reverse polish notation from the first element of the stack
        StrStack* reverse_polish = reverse(reverse_polish_notation); 
        double final_result = operate_rpn(reverse_polish);
        free(reverse_polish);
        return final_result;
    }
}

char* int_to_string(int num){
    char reversed_arr[100];
    int value;
    if(num<0){
        value = - num;
    }else{
        value = num;
    }
    int z = 0;
    char digit;
    if(value == 0){
        reversed_arr[0] = '0';
        z++;
    }
    while(value>0){
        digit = value%10 + '0';
        value = value/10;
        reversed_arr[z] = digit;
        z++;
    }
    reversed_arr[z] = '\0';
    char* arr = (char*)malloc(sizeof(char)*strlen(reversed_arr));
    int y=strlen(reversed_arr)-1;
    for(int z=0;z<strlen(reversed_arr);z++){
        arr[z] = reversed_arr[y];
        y--;
        }
    arr[strlen(reversed_arr)] = '\0';
    if(num<0){
        char* minus = "-";
        char* temp = strdup(arr);
        arr = strcpy(arr,minus);
        arr = strcat(arr,temp);
        free(temp);
    }
    return arr;
}

char* double_to_string(double num){
    int whole_part = (int)num;
    double decimal_part = num- whole_part;
    int decimal_digits = decimal_part*pow(10,6);
    char* arr_whole = int_to_string(whole_part);
    char* arr_decimal = int_to_string(decimal_digits);
    //a double always have 6 decimal places
    if(strlen(arr_decimal)<6){
        int add_zero = 6 - strlen(arr_decimal);
        char* more_zero = malloc(sizeof(char)*add_zero);
        //zeros of the decimal part of number are dropped when times 10 to the power of 6
        char* zero = "0";
        for(int z=0;z<add_zero;z++){
            strcat(more_zero,zero);
        }
        char* temp = strdup(arr_decimal);
        arr_decimal = strcpy(arr_decimal,more_zero);
        arr_decimal = strcat(arr_decimal,temp);
        free(temp);
        free(more_zero);
    }
    char* decimal_point = ".";
    char* arr = malloc(sizeof(char)*(strlen(arr_whole)+strlen(arr_decimal)));
    arr = strcpy(arr,arr_whole);
    arr = strcat(arr,decimal_point);
    arr = strcat(arr,arr_decimal);
    free(arr_whole);
    free(arr_decimal);
    return arr;
}

int check_variable(char *variable){
    for(int z=0;z<strlen(variable);z++){
        if(variable[z] == '='){
            return 1;
        }
    }
    return 0;
}

char* check_def(char* variable){
    while(check_variable(variable)==0){
        printf("Please input your definition of variable again.\n");
        variable = user_input();
    }
    return variable;
}

char* variable_name(char *variable){
    char* name;
    for(int z=0;z<strlen(variable);z++){
        if(variable[z] == '='){
            name = strndup(variable,z);
            break;
        }
    }
    for(int z=0;z<strlen(name);z++){
        if(name[z] == ' '){
            name[z] = '\0';
            break;
        }
    }
    return name;
}

char* value_variable(char *variable){
    char* variable_expression;
    for(int z=0;z<strlen(variable);z++){
        if(variable[z] == '='){
            variable_expression = strndup(variable+z+1,strlen(variable)-z+1);
            break;
        }
    }
    double result = calculator(variable_expression,'1',"\n","\n");
    char* variable_result =  double_to_string(result);
    free(variable_expression);
    return variable_result;
}

//here we operate the variable mode of the calculator
double second_mode(char* variable,char* formula){
    char* name = variable_name(variable);
    char* variable_result =  value_variable(variable);
    double final = calculator(formula,'2',name,variable_result);
    free(name);
    free(variable_result);
    return final;
}

int main(){ 
    double final_result = 0;
    printf("Please select:1 for classic mode,2 for variable mode.\n");
    char choice = user_choice();
    while(choice!='1'&&choice!='2'){
        printf("Invalid choice! Please input again!\n");
        choice = user_choice();
    }
    if(choice == '1'){
        char* arr = input_instructions();
        arr = check_input(arr);
        final_result = calculator(arr,'1'," "," ");
        free(arr);
    }else if(choice =='2'){
        printf("Please enter the definition of your variable.\n");
        printf("Please do not use the same variable name as the functions above.\n");
        printf("Spaces are not allowed within the variable name.\n");
        char* variable = user_input();
        variable = check_def(variable);
        char* arr = input_instructions();
        arr = check_input(arr);
        final_result = second_mode(variable,arr);
        free(variable);
        free(arr);
    }
    printf("final result %f\n",final_result);
    return 0;
} 
