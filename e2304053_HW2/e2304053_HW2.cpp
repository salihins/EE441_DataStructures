#define MAX_STACK_SIZE 100
#include <iostream>
using namespace std;
#include <fstream>
#include <string>

//Declaration of Student Class
class Student{
private:
    int num_of_pref;
    int stu_id;
    char stu_pref[3];
public:
    Student(){
    }

    Student(int id, char* pref, int num_of_pref){
        stu_id = id; //Parameter id is assigned to student's private member stu_id.
        this->num_of_pref = num_of_pref; //Parameter num_of_pref is assigned to student's private member num_of_pref.
        for (int i=0; i<num_of_pref; i++){
            stu_pref[i] = pref[i]; //Parameter pref[] is assigned to student's private member pref[]
        }
    }
    int Stu_pref_num(){
        return num_of_pref; //Returns the number of preferences that is taken from the input .txt file
    }

    int get_id(){
        return stu_id; //Returns the student id.
    }

    const char* Stu_pref(){
        return stu_pref; //Returns the array that holds the preferences of the student.
    }

    char num_eligible_section(int w_full, int t_full, int f_full){ //This method takes sections' full or not information as integer.
        int sec_num = 0;                                           //Then, compares with the preferences of the student.
        for(int i = 0; i<num_of_pref; i++){                        //If both student preferred a section and the section is empty,
            if(w_full == 0 && stu_pref[i] == 'W'){                 //the number of eligible section is increased by 1.
                sec_num++;
            }
            if(t_full == 0 && stu_pref[i] == 'T'){
                sec_num++;
            }
            if(f_full == 0 && stu_pref[i] == 'F'){
                sec_num++;
            }
        }
        return sec_num;
    }

    char eligible_section(int w_full, int t_full, int f_full){ //This method takes sections' full or not information as integer again.
                                                               //Then, compares with the preferences of the student.
        for(int i = 0; i<num_of_pref; i++){                    //If both student preferred a section and the section is empty,
            if(w_full == 0 && stu_pref[i] == 'W'){             //the prior section is returned.
                return stu_pref[i];
            }
            if(t_full == 0 && stu_pref[i] == 'T'){
                return stu_pref[i];
            }
            if(f_full == 0 && stu_pref[i] == 'F'){
                return stu_pref[i];
            }
        }
    }



};
//End of Student Class
//Declaration of Stack Class for Sections
template <class T>
class Stack{
private:
    T stacklist [MAX_STACK_SIZE];
    int top = -1;
    int sec_cap = 0;
public:
    Stack(int cap){
        sec_cap = cap; //cap parameter is taken from the input .txt file. Then, instead of comparing max_stack_size, sec_cap is used as the max size of the stack in the StackFull() method.
    }



    T Top(){
        if(StackEmpty()) { //We cannot return the top element of the stack is the stack empty, hence, check!
            cerr<<"Stack is empty"<<endl;
            exit(1);
        }
        else{
            return stacklist[top]; //Return the top element.
        }
    }
    void Push(const T& item){
        if(StackFull()){ // We cannot push an element if the stack is full, hence, check!
            cerr<<"Stack is full"<<endl;
            exit(1);
        }
        else {
            top = top+1; //Increase top and add the new student.
            stacklist[top] = item;

        }
    }
    int StackSize(){
        return top; //Returns the number of elements in the stack.
    }

    T Pop(){
        T temp;
        if(StackEmpty()){ //We cannot pop the top element of the stack is the stack empty, hence, check!
            cout<<"Stack is empty"<<endl;
            exit(1);
        }
        else {
        temp = stacklist[top]; //Assign top element to temp and decrease top by 1 so that the new student will be added to the deleted students place.
        top = top - 1;
        return temp; //Returns the deleted element.
        }
    }
    int StackEmpty(){
        return top == -1 ; //Returns whether the stack empty
    }

    int StackFull(){
        return top == sec_cap-1 ; //Returns whether the stack full.
    }

};
//End of Stack Class for Sections
//Declaration of Queue Class for Waiting Line
template <class T2>
class Queue{
private:
    int front=0;
    int rear=0;
    int count=0;
    T2 queuelist[MAX_STACK_SIZE];
public:
    Queue(){

    }
    void Q_clear(){ // All the parameters of the queue is re-assigned to 0 so that we can clear the queue.
        front = 0;
        rear = 0;
        count = 0;
    }
    void Q_add(const T2 &item){
        if(QFull()){
            cerr<<"Queue is full"<<endl; //We cannot delete a student if queue is full, hence, check!
            exit(1);
        }
        else {
        queuelist[rear] = item; //Parameter student is assigned to the rear of the queue.
        rear = rear+1;          //Rear is increased by 1 so that we can add new students to the queue.
        if(rear % MAX_STACK_SIZE == 0) rear = 0; //Adjustment of the rear value with respect to queue size.
        count = count+1;    //The number of students in the queue increased by 1, since we added 1 student.
        }
    }
    T2 Q_delete(){
        if(QEmpty()){
            cerr<<"Queue is empty"<<endl; //We cannot delete a student if queue is empty, hence, check!
            exit(1);
        }
        else{
            T2 temp;
            temp = queuelist[front]; //Front student is assigned to a temporary value, then front value is increased.
            front = front + 1;       //The front shifted and student is deleted. Also deleted student is the return value.
            if (front % MAX_STACK_SIZE == 0) front = 0; //Adjustment of the front value with respect to queue size.
            count = count - 1; //The number of students in the queue decreased by 1, since we deleted 1 student.
            return temp;
        }
    }


    int QSize(){
        return count; //Count holds the size value of the queue, hence it is returned.
    }
    int QEmpty(){
        return count == 0; //Control whether queue is empty or not
    }
    int QFull(){
        return count == MAX_STACK_SIZE; //Control whether queue is full or not
    }


};
//End of Queue Class for Waiting Line
int main() {
    string str;


    int stu_id;
    char pref[3];
    int sec_1_cap;
    char sec_1;
    int w_cap, t_cap, f_cap;
    int stu_num = 1;
    auto waiting_line = Queue<Student>();
    char comma;
    int pref_num = 0;
    string file_path;



    ifstream inputtxt;
    inputtxt.open("preferences.txt");


     if (inputtxt.is_open()) {
            //This block takes the size of the sections and sets the section's as stacks with parameter section capacity. /Start
            for (int i = 0; i<3; i++) {
                inputtxt >> sec_1;
                inputtxt >> comma;
                inputtxt >> sec_1_cap;
                if(sec_1 == 'W'){
                    w_cap = sec_1_cap;
                }
                if(sec_1 == 'T'){
                    t_cap = sec_1_cap;
                }
                if(sec_1 == 'F'){
                    f_cap = sec_1_cap;
                }
            }
            Stack<Student> wed_sec(w_cap);
            Stack<Student> thur_sec(t_cap);
            Stack<Student> fri_sec(f_cap);
            //This block takes the size of the sections and sets the section's as stacks with parameter section capacity. /End

            //This while block takes student's ID and preferences both the number of prefs and the preferences types (W or T or F) /Start
            while(inputtxt >> stu_id){
                stu_num ++;
                pref_num = 0;
                for(int k = 0; k<3; k++){
                    comma = inputtxt.get();
                    if(comma == ','){
                        inputtxt >> pref[k];
                        pref_num++;
                    }
                    else{
                        break;
                    }
                }
                //This while block takes student's ID and preferences both the number of prefs and the preferences types (W or T or F) /End

                //This block pushes students to the stacks if the number of eligible section of a student is 1 and the stack is not full. If it cannot push into stack, it pushes to the queue/Start
                Student s(stu_id, pref, pref_num);


                if(s.num_eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 1){
                    if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'W'){
                        wed_sec.Push(s);
                    }
                    else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'T'){
                        thur_sec.Push(s);
                    }
                    else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'F'){
                        fri_sec.Push(s);
                    }
                }

                else{
                    waiting_line.Q_add(s);
                }
                //This block pushes students to the stacks if the number of eligible section of a student is 1 and the stack is not full.If it cannot push into stack, it pushes to the queue/End

                //This block checks the queue after reading each student from the input .txt file. Again, if the number of eligible section of a student is 1 and the stack is not full, student
                //is pushed into the prior preferred section. Otherwise, it is sent back to the queue. If a student is pushed into a section, the conditions of the for loop is updated so that
                //it will check the queue from the start again. /Start
                int size_of_wait_line = waiting_line.QSize();
                for (int i = 0; i<size_of_wait_line;i++){
                    auto s = waiting_line.Q_delete();
                    if(s.num_eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 1){
                        if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'W'){
                            wed_sec.Push(s);
                            if(wed_sec.StackFull() == 1){
                                i = -1;
                                size_of_wait_line = waiting_line.QSize();
                            }
                        }
                        else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'T'){
                            thur_sec.Push(s);
                            if(thur_sec.StackFull() == 1){
                                i = -1;
                                size_of_wait_line = waiting_line.QSize();
                            }
                        }
                        else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'F'){
                            fri_sec.Push(s);
                            if(fri_sec.StackFull() == 1){
                                i = -1;
                                size_of_wait_line = waiting_line.QSize();
                            }
                        }
                    }
                    else{
                        waiting_line.Q_add(s);
                    }
                }
                //This block checks the queue after reading each student from the input .txt file. Again, if the number of eligible section of a student is 1 and the stack is not full, student
                //is pushed into the prior preferred section. Otherwise, it is sent back to the queue. If a student is pushed into a section, the conditions of the for loop is updated so that
                //it will check the queue from the start again. /End


               };

        //In this block if the number of eligible section of a student is not zero and the stack is not full, student
        //is pushed into the prior preferred section. Otherwise, it is sent back to the queue. This block is for the students with more than 1 eligible section.
        //If a student is pushed into a section, the conditions of the for loop is updated so that
        //it will check the queue from the start again. /Start
         int size_of_wait_line = waiting_line.QSize();
         for (int i = 0; i<size_of_wait_line;i++){
             auto s = waiting_line.Q_delete();
             if(s.num_eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) != 0){
                 if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'W'){
                     wed_sec.Push(s);
                     if(wed_sec.StackFull() == 1){
                         i = -1;
                         size_of_wait_line = waiting_line.QSize();
                     }
                 }
                 else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'T'){
                     thur_sec.Push(s);
                     if(thur_sec.StackFull() == 1){
                         i = -1;
                         size_of_wait_line = waiting_line.QSize();
                     }
                 }
                 else if(s.eligible_section(wed_sec.StackFull(),thur_sec.StackFull(),fri_sec.StackFull()) == 'F'){
                     fri_sec.Push(s);
                     if(fri_sec.StackFull() == 1){
                         i = -1;
                         size_of_wait_line = waiting_line.QSize();
                     }
                 }
             }
             else{
                 waiting_line.Q_add(s);
             }
         }
        //In this block if the number of eligible section of a student is not zero and the stack is not full, student
        //is pushed into the prior preferred section. Otherwise, it is sent back to the queue. This block is for the students with more than 1 eligible section.
        //If a student is pushed into a section, the conditions of the for loop is updated so that
        //it will check the queue from the start again. /End

        //This block prints the output file. /Start
         ofstream outputtxt;
         outputtxt.open("results.txt");
         outputtxt << "Wednesday:"<<endl;
         while(wed_sec.StackEmpty() != 1){
             auto return_stu = wed_sec.Pop();
             outputtxt << return_stu.get_id()<<endl;
         }
         outputtxt << "\nThursday:"<<endl;
         while(thur_sec.StackEmpty() != 1){
             auto return_stu = thur_sec.Pop();
             outputtxt << return_stu.get_id()<<endl;
         }
         outputtxt << "\nFriday:"<<endl;
         while(fri_sec.StackEmpty() != 1){
             auto return_stu = fri_sec.Pop();
             outputtxt << return_stu.get_id()<<endl;
         }
         outputtxt << "\nUnassigned:"<<endl;
         while(waiting_line.QEmpty()!= 1){
             auto return_stu = waiting_line.Q_delete();
             outputtxt << return_stu.get_id()<<endl;
         }

         outputtxt.close();
         inputtxt.close();
       }
       //This block prints the output file. /End
     else{
         cout<<"File is not found"<<endl; //If the input file is not found the error is given.
     }



        return 0;
    }


