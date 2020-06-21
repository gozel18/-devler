#include <iostream>
#include <math.h>
using namespace std;

//define type node_d as struct digit -linked list node
typedef struct digit{

    int value;
    struct digit *nextDigit;

}node_d;

//define type node_s as struct student -stack array node
typedef struct studentNumber{

    struct digit *id;
    struct studentNumber *nextStudent;

}node_s;

//add a digit to the student number linked list
void pushDigit(node_d **current_digit, int sn, int which_digit){
    
    if (which_digit < 0)
        return;

    *current_digit = (node_d* ) malloc(sizeof(node_d));
    (*current_digit)->value = ((int) (sn / pow(10, which_digit))) % 10;
    (*current_digit)->nextDigit = NULL;
    which_digit --;

    pushDigit(&((*current_digit)->nextDigit), sn, which_digit);
    
    return;
}

//create new node_s node with given value
node_s *newnode(int sn){

    node_s *student = (node_s *) malloc(sizeof(node_s));
    
    student->id = (node_d *) malloc(sizeof(node_d));
    student->id->value = sn % 1000;
    student->nextStudent = NULL;

    pushDigit(&(student->id->nextDigit), sn, 8);
    
    return student;
}

//create new stack array node
void push(node_s **root, int sn){

    node_s *student = newnode(sn);
    
    student->nextStudent = *root;
    *root = student;
    
    cout << "student " << sn << " added successfully." << endl << endl;
}

//print the student number registered at the given node
void printStudentNumber(node_d **node_ref){

    if (*node_ref == NULL)
        return;
    
    cout << (*node_ref)->value;

    printStudentNumber(&((*node_ref)->nextDigit));

}

//display the student numbers
void display(node_s **root){
    
    if(*root == NULL)
        return;

    display(&((*root)->nextStudent));

    printStudentNumber(&((*root)->id->nextDigit));
    
    cout << endl;
    
}

//find the student number with the minimum id value and keep it in mini
void minimum(node_s **node_ref, node_s **mini){
    
    if (*node_ref == NULL){
        return;
    }
    
    if ((*node_ref)->id->value < (*mini)->id->value) {
        *mini = (*node_ref);
    }

    minimum(&((*node_ref)->nextStudent), mini);

}

int main(){

    node_s *head = NULL;
    int n_students, sn;
    int choice;
    
    //get number of students and student numbers

    GETSTUDENTS:
    
    cout << endl << "Please enter the number of students." << endl;    
    
    cin >> n_students;
    
    if( cin.fail() ){
    
        cout << "End of file or data type mismatch occured. ";
        return 1;
    
    }

    cout << endl;

    for(int i = 0; i < n_students; i++){

        cout << "Please enter student number of student " << i + 1 << endl;
        cin >> sn;
        
        if( cin.fail() ){
        
            cout << "End of file or data type mismatch occured. ";
            return 1;
        
        }
        
        if (sn >= 1000000000 || sn < 100000000){
        
            cout << "this is not a valid student number" << endl << endl;
            i--;
            continue;
        
        }
        
        push(&head, sn);
    
    }

    node_s *mini = head;

    //asks for the operation to do next

    while(1){

        cout << endl << "1: display all students\n\
2: display the student number with the minimum id value\n\
3: add new students\n\
4: exit\n\
please specify the operation you want by entering the \
associated number in the list above." << endl << endl;

        cin >> choice;

        if( cin.fail() ){
        
            cout << "End of file or data type mismatch occured. ";
            return 1;
        
        }

        switch(choice){

            case 1:
            
                //if 1 list the student numbers

                cout << "registered students:" << endl;
                display(&head);
                break;

            case 2:

                //if 2 print the student number with the smallest id value

                minimum(&head, &mini);
                cout << "minimum student number is ";
                printStudentNumber(&(mini->id->nextDigit));
                cout << endl;
                break;

            case 3:

                //if 3 go to tag GETSTUDENTS 
            
                goto GETSTUDENTS;
                break;
            
            case 4:

                //if 4 return 0

                return 0;
                break;

        }

    }
   
}