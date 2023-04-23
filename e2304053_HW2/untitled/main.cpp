#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Stack //Stack, as implemented in lecture notes
{
private:
    int Capacity;
    T* stacklist;
    int top;
public:
    Stack(void);
    void Push(const T& item);
    T Pop(void);
    void Clearstack(void);
    T Peek(void) const;
    int StackEmpty(void) const;
    int StackFull(void) const;
    void set_cap(int cap);
    int get_cap(void) const;
};
template <class T>
Stack<T>::Stack(void):top(-1){}
template <class T>
int Stack<T>::StackEmpty(void) const{return (top==-1);}
template <class T>
int Stack<T>::StackFull(void) const{return (top==(Capacity-1));}
template <class T>
void Stack<T>::Push(const T& item){if (StackFull()){cerr<<"Stack is full"<<endl;exit(1);}top++;stacklist[top]=item;}
template <class T>
T Stack<T>::Pop(void){T temp;if (StackEmpty()){cerr<<"Stack is empty"<<endl;exit(1);}temp=stacklist[top];top--;return temp;}
template <class T>
T Stack<T>::Peek(void) const{if (StackEmpty()){cerr<<"Stack is empty"<<endl;exit(1);}return stacklist[top];}
template <class T>
void Stack<T>::Clearstack(){top=-1;}
template <class T>
void Stack<T>::set_cap(int cap){Capacity=cap; stacklist= new T [cap];}
template <class T>
int Stack<T>::get_cap(void) const {return Capacity;}

template<class T>
class Queue //Queue implementation
{
private:
    int front,rear,count;
    T qlist[100];
public:
    Queue(void);
    void Qinsert(const T& item);
    T Qdelete(void);
    void ClearQueue(void);
    T QFront(void) const;
    int QLength(void) const;
    int QEmpty(void) const;
    int QFull(void) const;

};
template <class T>
Queue<T>::Queue(void): front(0),rear(0),count(0) {}
template <class T>
int Queue<T>::QLength(void) const {return count;}
template <class T>
int Queue<T>::QEmpty(void) const {return (count==0);}
template <class T>
int Queue<T>::QFull(void) const {return (count==1000);}
template <class T>
void Queue<T>::Qinsert(const T& item) {if (QFull()){cerr<<"Queue Full"<<endl;exit(1);}count++;qlist[rear]=item;rear=(rear+1)%1000;}
template <class T>
T Queue<T>::Qdelete(void) {if (QEmpty()){cerr<<"Queue Empty"<<endl;exit(1);}T temp;temp=qlist[front];count--;(front=front+1)%1000;return temp;}
template <class T>
T Queue<T>::QFront(void) const {return qlist[front];}

class Student //Student class implementation
{
private:
    int ID;
    char preferences[3]={NULL,NULL,NULL};
public:
    Student();
    Student(int inp_ID);
    int get_ID(void) const;
    char* get_pref(void);
    void set_ID(int inp_ID);
    void add_pref(char inp_preference,int index);
    int No_Eligible_Sec(Stack<Student> &Stack1, Stack<Student> &Stack2, Stack<Student> &Stack3);
    char Most_Pref_Sec(Stack<Student> &Stack1, Stack<Student> &Stack2, Stack<Student> &Stack3);
};
Student::Student(){};
Student::Student(int inp_ID){ID=inp_ID;}
int Student::get_ID(void) const {return ID;}
char* Student::get_pref(void) {return preferences;}
void Student::set_ID(int inp_ID){ID=inp_ID;}
void Student::add_pref(char inp_preference,int index){preferences[index]=inp_preference;}
int Student::No_Eligible_Sec(Stack<Student> &Stack1, Stack<Student> &Stack2, Stack<Student> &Stack3)
{int available = 0;
    if ((preferences[0]=='W' || preferences[1]=='W'|| preferences[2]=='W') && !Stack1.StackFull()){available++;};
    if ((preferences[0]=='T' || preferences[1]=='T'|| preferences[2]=='T') && !Stack2.StackFull()){available++;};
    if ((preferences[0]=='F' || preferences[1]=='F'|| preferences[2]=='F') && !Stack3.StackFull()){available++;}; return available; }
char Student::Most_Pref_Sec(Stack<Student> &Stack1, Stack<Student> &Stack2, Stack<Student> &Stack3)
{if (preferences[0]=='W' && !Stack1.StackFull()) {return 'W';}
    else if (preferences[0]=='T' && !Stack2.StackFull()) {return 'T';}
    else if (preferences[0]=='F' && !Stack3.StackFull()) {return 'F';}
    else if (preferences[1]=='W' && !Stack1.StackFull()) {return 'W';}
    else if (preferences[1]=='T' && !Stack2.StackFull()) {return 'T';}
    else if (preferences[1]=='F' && !Stack3.StackFull()) {return 'F';}
    else if (preferences[2]=='W' && !Stack1.StackFull()) {return 'W';}
    else if (preferences[2]=='T' && !Stack2.StackFull()) {return 'T';}
    else if (preferences[2]=='F' && !Stack3.StackFull()) {return 'F';}
    else {return NULL;}
}

int main()
{
    Stack<Student> Wednesday, Thursday, Friday;
    Queue<Student> waiting_list;
    fstream inputtxt;
    inputtxt.open("C:\\Users\\Can\\Desktop\\Okul\\EE4.1\\EE441\\hw2\\preferences.txt");
    char output[100];
    char blank[100];
    int cap;
    int ID;
    Student students[9999]={NULL};
    int counter;
    int student_counter=0;
    if (inputtxt.is_open()) {
        while (!inputtxt.eof()) {
            fill(output, output+100, '\0');
            cap=0;
            inputtxt >> output;
            counter++;
            char temp[100];
            int tempidx;
            if (output[0]=='W'){for (int i=0;i<sizeof(output);i++)
                {if (output[i]==','){tempidx=i;}}
                for (int j=tempidx+1;j<sizeof(output);j++)
                {temp[j-tempidx-1]=output[j];}
                cap=atoi(temp);
                Wednesday.set_cap(cap);}
            if (output[0]=='T'){for (int i=0;i<sizeof(output);i++)
                {if (output[i]==','){tempidx=i;}}
                for (int j=tempidx+1;j<sizeof(output);j++)
                {temp[j-tempidx-1]=output[j];}
                cap=atoi(temp);
                Thursday.set_cap(cap);}
            if (output[0]=='F'){for (int i=0;i<sizeof(output);i++)
                {if (output[i]==','){tempidx=i;}}
                for (int j=tempidx+1;j<sizeof(output);j++)
                {temp[j-tempidx-1]=output[j];}
                cap=atoi(temp);
                Friday.set_cap(cap);}
            if (counter>3)
            {   ID=atoi(output);
                Student temps=Student(ID);
                if (output[to_string(ID).length()+1]=='W'||output[to_string(ID).length()+1]=='T'||output[to_string(ID).length()+1]=='F')
                {
                    temps.add_pref(output[to_string(ID).length()+1],0);
                }
                if (output[to_string(ID).length()+3]=='W'||output[to_string(ID).length()+3]=='T'||output[to_string(ID).length()+3]=='F')
                {
                    temps.add_pref(output[to_string(ID).length()+3],1);
                }
                if (output[to_string(ID).length()+5]=='W'||output[to_string(ID).length()+5]=='T'||output[to_string(ID).length()+5]=='F')
                {
                    temps.add_pref(output[to_string(ID).length()+5],2);
                }
                if (temps.No_Eligible_Sec(Wednesday,Thursday,Friday)==1)
                {
                    if (temps.Most_Pref_Sec(Wednesday,Thursday,Friday)=='W')
                    {
                        Wednesday.Push(temps);
                    }
                    else if (temps.Most_Pref_Sec(Wednesday,Thursday,Friday)=='T')
                    {
                        Thursday.Push(temps);
                    }
                    else if (temps.Most_Pref_Sec(Wednesday,Thursday,Friday)=='F')
                    {
                        Friday.Push(temps);
                    }

                }
                else {waiting_list.Qinsert(temps);}
                int countq=0;
                int length=waiting_list.QLength();
                while (countq<length)
                {
                    Student qmember;
                    qmember=waiting_list.Qdelete();

                    if (qmember.No_Eligible_Sec(Wednesday,Thursday,Friday)==1&&qmember.Most_Pref_Sec(Wednesday,Thursday,Friday)=='W')
                    {
                        Wednesday.Push(qmember);
                        countq=0;
                        length=waiting_list.QLength();
                    }
                    else if (qmember.No_Eligible_Sec(Wednesday,Thursday,Friday)==1&&qmember.Most_Pref_Sec(Wednesday,Thursday,Friday)=='T')
                    {
                        Thursday.Push(qmember);
                        countq=0;
                        length=waiting_list.QLength();
                    }
                    else if (qmember.No_Eligible_Sec(Wednesday,Thursday,Friday)==1&&qmember.Most_Pref_Sec(Wednesday,Thursday,Friday)=='F')
                    {
                        Friday.Push(qmember);
                        countq=0;
                        length=waiting_list.QLength();
                    }
                    else {waiting_list.Qinsert(qmember);
                        length=waiting_list.QLength();}
                    countq++;
                }



            }
        };
    };

    inputtxt.close();
    Student temp2;
    while (!waiting_list.QEmpty() && !(Wednesday.StackFull()&&Thursday.StackFull()&&Friday.StackFull()))
    {
        temp2=waiting_list.Qdelete();
        if (temp2.Most_Pref_Sec(Wednesday,Thursday,Friday)=='W')
        {
            Wednesday.Push(temp2);
        }
        else if (temp2.Most_Pref_Sec(Wednesday,Thursday,Friday)=='T')
        {
            Thursday.Push(temp2);
        }
        else if (temp2.Most_Pref_Sec(Wednesday,Thursday,Friday)=='F')
        {
            Friday.Push(temp2);
        }
        else {waiting_list.Qinsert(temp2);}

    }

    ofstream results;
    results.open("C:\\Users\\Can\\Desktop\\Okul\\EE4.1\\EE441\\hw2\\results.txt");
    results << "Wednesday:\n";
    int rID;
    if(Wednesday.StackEmpty()){results<<"-\n\n";}
    else{
        while(!Wednesday.StackEmpty()){

            rID=Wednesday.Pop().get_ID();
            results<<rID<<"\n";
        }
        results<<"\n";
    }
    results << "Thursday:\n";
    if(Thursday.StackEmpty()){results<<"-\n\n";}
    else{
        while(!Thursday.StackEmpty()){
            rID=Thursday.Pop().get_ID();
            results<<rID<<"\n";
        }
        results<<"\n";
    }
    results << "Friday:\n";
    if(Friday.StackEmpty()){results<<"-\n\n";}
    else{
        while(!Friday.StackEmpty()){
            rID=Friday.Pop().get_ID();
            results<<rID<<"\n";
        }
        results<<"\n";
    }
    results << "Unassigned:\n";
    if(waiting_list.QEmpty()){results<<"-\n\n";}
    else{
        while(!waiting_list.QEmpty()){
            rID=waiting_list.Qdelete().get_ID();
            results<<rID<<"\n";
        }
    }
    results.close();
}
