#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include "piles_projet.h" // stack declaration + push/pushint + pop/popint +isOperand + isOperator 

/***********************THE EVALUATING FUNCTION***********************************/

int evaluatePostfix(char * exp ,int *arr)
{
    node * top = NULL ; 
    int i =0 ; int m = 0; int s= 0 ;  
    int len = strlen(exp); 
    while (i < len)
    {
        if (isOperand(exp[i])){
        	while(s != arr[m]){
        		s=s*10+(exp[i]-48);
        		i++; 
			}
            pushint(&top , s);
            s=0 ; m++;     
   		}
        else
        {
            int val1 = popint(&top);
            int val2 = popint(&top); 
            switch (exp[i])
            {
            case '+': pushint(&top, val2 + val1); break;
            case '-': pushint(&top, val2 - val1); break;
            case '*': pushint(&top, val2 * val1); break;
            case '/': pushint(&top, val2 / val1); break;
            case '^': pushint(&top, pow(val2,val1));break;
            }
            i++; 
        }
    }
    
    printf("Result:\n%d\n", popint(&top));
}

/***********************THE BIG FUNCTION : NORAMAL EXPERSION TO POLONAISE NOTATION***********************************/
int infixToPostfix(char* exp)
{
	char copyof[strlen(exp)] ;
	strcpy(copyof, exp); 
	

	node * top = NULL ;
	push(&top , '('); 
    int i, k = -1;   
    for (i = 0; i < strlen(exp); i++)
    {
        if (isOperand(exp[i])){
        	exp[++k]=exp[i]; 
		}
        else if (exp[i] == '(')
            push(&top, exp[i]);
        else if (exp[i] == ')')
        {
            while (peek(top)!='(')
                exp[++k]=pop(&top);
            pop(&top);
        }
        else
        {
            while (peek(top)!='(' && Prec(exp[i]) <= Prec(peek(top)))
                exp[++k]=pop(top);
            push(&top, exp[i]);
        }

    }

    while (peek(top)!='(')
        exp[++k]=pop(&top);
    exp[++k] = '\0';
    
    printf("Reverse Polish Notation:\n");

    char str[100];

    strcpy(str, exp); 
    
    int len = strlen(str);
    
/*****************************in this part i made this function to find numbers like 55 or 248 ***************************/	
// if exp = 55+89/17*89 the result will be stocked in arr as [55 89 17 89] 
// we need this function too in the evaluating of the postfix exxperssion 

	int arr[100]; 
	int m = 0; 
	int c = 0 ; 
	for (int i = 0 ; i<strlen(copyof) ; i++){
		if(isOperand(copyof[i])){
			int t =1 ; 
			int k = i ; int s =0;
			c = i ; 
			while (t != 0){
				if(isOperand(copyof[i+1])){
					k++ ;
					i++ ;
				}
				else {
					for (int j =c ; j<=i ; j++){
						s = (s*10)+(copyof[j]-48);
						t= 0 ; 
					} 
					arr[m]=s ; 
				}
			} 
			arr[++m] = copyof[i+1]; 
		}
		else{
			arr[m]=copyof[i];
		
		}
	}
	
/*************************/
	
//display the notation with spaces without char problem: //555+ ==> 5 55 + : while 5 and 55 are int but "+" char  
	m=0 ; int s=0 ;
	i =0;
	while(i<len){
		if(isOperand(str[i])){
			while (s != arr[m]){
				s=s*10+(str[i]-48); 
				i++;
			}
			printf("%d ",s); 
			s=0 ; m++;
		} 
		else{
			printf("%c ",str[i]);
			i++;
		}
	} 
	printf("\n"); 
    evaluatePostfix(exp,arr); 
}


/***********************THE VALIDATION FUNCTION ***********************************/

int IsIt(char * exp){
	
	int len=strlen(exp);
	int op = 0 ; int ov =0; int clo = 0 ;  
	
	for(int i = 0 ; i<len ; i++){
		if(IsOperator(exp[i]) && IsOperator(exp[i+1])){
			op =  1 ; 
		} 
		else if (exp[i] == '(' )
			ov++ ; 
		else if (exp[i] == ')')
			clo++ ; 
	}

	
	if (op == 1 && (ov != clo)){
		printf("OPS YOU HAVE PROBLEM IN OPs && BRAKETS PLEASE FIX IT\nENTER AGAIN : \n");  
		return op ;
	}
	else if (op == 1 && (ov == clo)){
		printf("OPS YOU HAVE PROBLEM IN OPs PLEASE FIX IT\nENTER AGAIN : \n\n"); 
		return op ;
	}
	else if (op == 0 && (ov != clo)){
		printf("OPS YOU HAVE PROBLEM IN BRAKETS PLEASE FIX IT\nENTER AGAIN : \n\n"); 
		return 1 ; 
	}
	else if(!isOperand(exp[len-1]) && exp[len-1]!= ')'){
		printf("CHECK THE LAST OP !! PLEASE FIX IT\nENTER AGAIN : \n\n"); 
		return  1;
	}
	else 
		return 0 ; 
}


/*******************THE MAIN FUNCTION ***********************************/

int main()
{
	int an = 0 ; 
	do{
		printf(" ______ ______ ______ ______ ______ ______ \n"); 
		printf("|______|______|______|______|______|______|\n\n");
		char exp[100]; 
		printf("- [1] INSERT Experssion and evaluate it \n- [2] TEST an expression\n- [3] RESULT of polonaise expersion \n");
		printf(" ______ ______ ______ ______ ______ ______ \n"); 
		printf("|______|______|______|______|______|______|\n\n");
		int chois ; 
		printf("choisser : "); 
		scanf("%d",&chois); 
	
		switch(chois){
			case 1:
				do{	
					printf("===> "); 
    				scanf("%s", exp);
				}while(IsIt(exp));
				printf("Expression:\n%s\n", exp);
    			infixToPostfix(exp);
				break ; 
			case 2:		
				do{
					printf("===> ");	
    				scanf("%s", exp);
				}while(IsIt(exp));
				printf("COOL:)\n"); 
				break ; 
			
			case 3:
				printf(" ====>  SOON !!  <====\n"); break ; 
			default:
				printf("\n============= WE DON't HAVE THIS OPTION TRY 1-2-3!============= \n"); break ; 			
		} 
		printf("\n\n"); 
		printf("Do you want another try ??\n");
		printf("type '1' for YES or '0' for NO\n\n"); 
		scanf("%d",&an); 

		
	}while(an == 1); 
    return 0;
} 

