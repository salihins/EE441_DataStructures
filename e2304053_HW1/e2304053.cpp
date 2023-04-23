#define MAX_SIZE 10
#include <iostream>
using namespace std;

//Declaration of Student class
class Student{
private: //declaration of private members
    int ID;
    string name, surname;
    int quizScores[4];
    int hwScores[3];
    int finalScore;

public: //declaration of public members
    //constructors
    Student(){

    }

    Student(int id, string Name, string Surname){
        ID = id;
        name = Name;
        surname = Surname;

    }
    //constructors
    //setter methods
    void setID(int id) {
        ID = id;
    }

    void setName(string Name){
        name = Name;
    }

    void setSurname(string Surname) {
        surname = Surname;
    }

    void setQuizScores(int quiz_scores[4]){ //this method takes an array as input and writes to the student's array one by one
        int i;

        for(i=0; i<4; i++){
            if(quiz_scores[i]<101 && quiz_scores[i]>=0)  //Control of the input grade
                quizScores[i] = quiz_scores[i];
            else
                cout<<"Invalid grade"<<endl; //Error for invalid grade
        }
    }

    void setHwScores(int hw_scores[3]){//this method takes an array as input and writes to the student's array one by one
        int i;
        int a[3];
        for(i=0; i<3; i++){
            if(hw_scores[i]<101 && hw_scores[i]>=0) //Control of the input grade
                hwScores[i] = hw_scores[i];
            else
                cout<<"Invalid grade"<<endl; //Error for invalid grade
        }

    }

    void setFinalScore(int final_grade){
        if(final_grade<=100 && final_grade>=0) //Control of the input grade
            finalScore = final_grade;
        else
            cout<<"Invalid grade"<<endl;
    }
    //setter methods
    //getter methods
    int getID(){
            return ID;
        }

    string getName(){
        return name;
    }


    string getSurname(){
        return surname;
    }

    int* getQuizScores() {
        return quizScores;
    }

    int* getHwScores(){
        return hwScores;
    }

    int getfinalScore() {
        return finalScore;
    }
    //getter methods
    double overallCourseScore(double wQ, double wHw, double wF){
        double f_av = 0;
        double gen_av = 0;
        double quiz_sum = 0,hw_sum = 0;

        for(int i = 0; i<4; i++){
            quiz_sum = quiz_sum + quizScores[i]; //summation of the quiz grades
        }
        for(int j = 0; j<3; j++){
            hw_sum = hw_sum + hwScores[j];  //summation of the homework grades
        }
        f_av = finalScore;

        gen_av = (quiz_sum*wQ)/4+(hw_sum*wHw)/3+(finalScore*wF); // division by 4 and 3 is in order to calculate the quiz average

        return gen_av;

    }

};



//declaration of course class
class Course{
private: //declaration of private members

    Student students[MAX_SIZE]; //MAX_SIZE is defined as 10 at the beginning of the file
    int num = 0;
    double weightQ = 0.3;
    double weightHW = 0.3;
    double weightF = 0.4;

public: //declaration of public members
    Course(){       //constructor function, no input or action is needed. Since there is already a change weight function

    }

    int getNum(){
        return num; //returns the number of students that are taking the course
    }

    void addNewStudent(int id, string Name, string Surname){ //creates a new student and adds the student to the course
        Student x(id,Name,Surname);
        students[num] = x;
        num++;
    }

    Student* getStudentInfo(int id) { //returns the desired student's address. the aim of the address return is to use the methods of student class in the following parts of the code.
        for(int i=0; i<num ; i++ ) {
            if(id == students[i].getID()){
                return &students[i];
            }
        }

        return nullptr; // if the desired student does not take the course, null pointer is returned and necessary actions are taken with the nullptr information
    }
    void updateWeights(double weQ, double weHW, double weF){
        if( (weQ<=1 && weQ>=0) && (weHW<= 1 && weHW>=0) && (weF<=1 && weF>=0) && (weQ+weHW+weF==1)){ //Control of the input weights
            weightQ = weQ;
            weightF = weF;
            weightHW = weHW;
        }
        else{
            cout<<"weights are invalid!"<<endl; //error for invalid weight value
        }


    }

    int calculateAverage(){
        int* Qscores;
        int* Hwscores;
        double Qsum = 0 ;
        double Hwsum= 0;
        double fin_sum= 0;
        double Q_av, Hw_av, F_av, G_av;


        for(int i=0; i < num; i++) {
            Qscores = students[i].getQuizScores();
            Hwscores = students[i].getHwScores();
            fin_sum = fin_sum+students[i].getfinalScore();

            for(int j = 0; j<4;j++){
                Qsum = Qscores[j]+Qsum;
            }

            for(int k=0; k<3; k++) {
                Hwsum = Hwsum + Hwscores[k];
            }
        }

        Q_av = Qsum / (4*num);
        Hw_av = Hwsum / (3*num);
        F_av = fin_sum / num;
        G_av = ((Q_av*weightQ)+(Hw_av*weightHW)+(F_av*weightF)) ;
        cout<<"Quizzes-Avg: "<<Q_av<<endl;
        cout<<"Homeworks-Avg: "<<Hw_av<<endl;
        cout<<"Final-Avg: "<<F_av<<endl;
        cout<<"General-Avg: "<<G_av<<endl;
    }
    //getter methods for weights
    double getWeightQ(){
        return weightQ;
    }
    double getWeightHw(){
        return weightHW;
    }
    double getWeightF(){
        return weightF;
    }
    //getter methods for weights
    void student_average_above(int threshold){ //threshold is input as can be seen. this method checks all of the students' grades. After comparing with the threshold, prints the necessary ones.
        double a;

        for (int i = 0; i<num; i++){
            a = students[i].overallCourseScore(weightQ,weightHW,weightF);
            if(a>threshold){
                cout<<students[i].getID()<<" "<<students[i].getName()<<" "<<students[i].getSurname()<<" "<<a<<endl;
            }

        }



    }
    void student_average_below(int threshold){//threshold is input as can be seen. this method checks all of the students' grades.After comparing with the threshold, prints the necessary ones.
        double a;

        for (int i = 0; i<num; i++){
            a = students[i].overallCourseScore(weightQ,weightHW,weightF);
            if(a<threshold){
                cout<<students[i].getID()<<" "<<students[i].getName()<<" "<<students[i].getSurname()<<" "<<a<<endl;
            }
        }



    }



};

Course data_struc; //global course variable

void addNewStudent(int ID, string name, string surname){
    data_struc.addNewStudent(ID, name, surname); //sends the information of the new student to the course's method.
}


void showStudent(int id){
    Student* stu_ins; //variable for address of students that is returned from getStudentInfo method
    stu_ins = data_struc.getStudentInfo(id);
    if(stu_ins == nullptr){ //check of the student
        cout<<"No such student!"<<endl;//error, if the desired student is not found
    }
    else{
        cout<<id<<" "<<stu_ins->getName()<<" "<<stu_ins->getSurname()<<" ";
        int* q_score;
        q_score = stu_ins->getQuizScores(); //gets the desired student's quiz grades and prints them
        for(int i = 0; i<4; i++){

            cout<<q_score[i]<<" ";
        }
        int* hw_score;
        hw_score = stu_ins -> getHwScores(); //gets the desired student's homework grades and prints them
        for(int i = 0; i<3; i++){

            cout<<hw_score[i]<<" ";
        }
        cout<<stu_ins->getfinalScore()<<endl; //gets the desired student's final grade and prints them
    }
}

void changeStudentScores(int ID, int* quiz_scores, int* hw_scores,int final_score){
    Student* stu_ins;
    stu_ins = data_struc.getStudentInfo(ID);
    if(stu_ins == nullptr){//check of the student
        cout<<"No such student!"<<endl; //error, if the desired student is not found
    }
    else{
        stu_ins->setFinalScore(final_score); //sets the desired student's final grade
        stu_ins->setHwScores(hw_scores); //sets the desired student's homework grades
        stu_ins->setQuizScores(quiz_scores); //sets the desired student's quiz grades
    }


}
void changeWeights(double weightQ, double weightHW, double weightF){
    data_struc.updateWeights(weightQ, weightHW, weightF); //changes the weights of the assignments
}


void showAverage(){

    data_struc.calculateAverage(); // calculates average grade of the course

}
void showAbove(int threshold){
    data_struc.student_average_above(threshold);
}
void showBelow(int threshold){
    data_struc.student_average_below(threshold);
}







int main() {

    int option_num;
    int stu_id;
    string stu_name;
    string stu_surname;
    int final_score;
    double w_Q,w_HW,w_F;
    int grade_th;




    cout<<"EE441 Classroom Interface"<<endl<<"Choose your option:"<<endl;
    cout<<"1) Add a student"<<endl;
    cout<<"2) Search a student by ID"<<endl;
    cout<<"3) Change a student's score"<<endl;
    cout<<"4) Update weights"<<endl;
    cout<<"5) Show class average"<<endl;
    cout<<"6) Show students with overall score above a threshold"<<endl;
    cout<<"7) Show students with overall score below a threshold"<<endl;
    cout<<"8) Exit"<<endl;
    while (true) {
        cout<<"Enter your option:";
        cin>>option_num;



        if (option_num == 1){
            cout<<"Enter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;
            int score_q[4];
            int score_hw[3];
            cin>>stu_id>>stu_name>>stu_surname>>score_q[0]>>score_q[1]>>score_q[2]>>score_q[3]>>score_hw[0]>>score_hw[1]>>score_hw[2]>>final_score;
            if(stu_id>0){//check for valid id number
            addNewStudent(stu_id, stu_name,stu_surname); //creates the new student
            changeStudentScores(stu_id,score_q, score_hw,final_score); //since in the example, grades are taken as input here, after creating student this line sets the grades of the student.
            }
            else{
                cout<<"Invalid ID"<<endl; //error message for invalid ID
            }
        }

        else if(option_num == 2) {
            cout<<"Enter student ID"<<endl;
            cin>>stu_id;
            if(stu_id>0){//check for valid id number
                showStudent(stu_id);
            }
            else{
                cout<<"Invalid ID"<<endl;//error message for invalid ID
            }


        }

        else if(option_num == 3){//grades are taken as input and are sent to the method.
            cout<<"Enter ID, quiz, homework and final scores:"<<endl;
            int score_q2[4];
            int score_hw2[3];
            cin>>stu_id>>score_q2[0]>>score_q2[1]>>score_q2[2]>>score_q2[3]>>score_hw2[0]>>score_hw2[1]>>score_hw2[2]>>final_score;
            changeStudentScores(stu_id,score_q2, score_hw2,final_score);
        }

        else if(option_num == 4){//weight are taken as input and are sent to the method.
            cout<<"Enter quiz, homework, final weights:"<<endl;
            cin>>w_Q>>w_HW>>w_F;
            changeWeights(w_Q,w_HW,w_F);
        }

        else if(option_num == 5) {
            showAverage();
        }

        else if(option_num == 6) {
            cout<<"Enter threshold:";
            cin>>grade_th;
            if(grade_th<=100 && grade_th>=0) //threshold should be between 0 and 100
                showAbove(grade_th);
            else
                cout<<"Invalid threshold"<<endl;
        }

        else if(option_num == 7) {
            cout<<"Enter threshold:";
            cin>>grade_th;
            if(grade_th<=100 && grade_th>=0) //threshold should be between 0 and 100
                showBelow(grade_th);
            else
                cout<<"Invalid threshold"<<endl;
        }

        else if(option_num == 8) {
            cout<<"Program closed."<<endl;
            break;
        }

        else{
            cout<<"Not a valid option"<<endl; // check for invalid option
        }
    }

    return 0;
}
