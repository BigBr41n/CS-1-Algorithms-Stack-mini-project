// Declaration of the stack (pile)
typedef struct node node ; 
struct node {
	int val; 
	node * next ;  
}; 

void push(node ** top , char n){ //push char to reverse the notation 
	node * p = (node*)malloc(sizeof(node)); 
	p->val = n ; 
	p->next = *top ; 
	*top = p; 
}
void pushint(node ** top , int n){// push int to evaluate the experssion 
	node * p = (node*)malloc(sizeof(node)); 
	p->val = n ; 
	p->next = *top ; 
	*top = p; 
}

int isEmpty(node *top)
{
    return !top; 
}

char peek(node * top)  
{//sommet Pile 
    return top->val;
}


char pop(node ** top)
{// pop char used in the reverse part 
	char k ; 
    if (!isEmpty(*top))
		k = (*top)->val;
		node * temp =(*top) ; 
		(*top) = (*top)->next ; 
		free (temp);
	return k ; 
}

int popint(node ** top)
{// pop int used int evaluating part to return int value 
	int k ; 
    if (!isEmpty(*top))
		k = (*top)->val;
		node * temp =(*top) ; 
		(*top) = (*top)->next ; 
		free (temp);
	return k ; 
}


int isOperand(char ch)
{
	return (ch >= '0' && ch <= '9');
}
int IsOperator(char ch){
	return (ch >= 42 && ch <= 47); 
}

int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}
























