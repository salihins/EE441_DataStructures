
//EE441 HW3 Can Aydýn 2304053
//Comments about result
//As can be seen from results, linked list is better for searching data and binary search tree is better for inserting data.
//As a result, we can use binary search trees when we use hugh amount of data. In specific, we can use binary search trees
//as databases. Insert will be more efficient. However, it will be harder to reach a data in the base when we compare
//performance with linked list. Overall, linked list is better for searching and reaching an element and binary search tree
//is better for storing large amounts of data.

#include <iostream>
#include <fstream>
using namespace std;

//Declaration of Node class for both linked list and binary search tree.
class NodeLL{
    //Declaration of private members
private:
    int processID;
    int arrivalTime;
    int runTime;
    int priority;
    NodeLL *next;
    NodeLL *right_T;
    NodeLL *left_T;

    //Declaration of public members
public:
    NodeLL(){} //Empty constructor
    NodeLL(int pro_ID, int arr_Time, int run_Time, int prio, NodeLL *next_ptr = NULL,NodeLL *left = NULL, NodeLL *right = NULL){ //Another constructor with necessary information is given as input of the method.
        processID = pro_ID;
        arrivalTime = arr_Time;
        runTime = run_Time;
        priority = prio;
        next = next_ptr;
        left_T = left;
        right_T =right;
    }
    //Getters and Setters starts
    int get_processID(){
        return processID;
    }
    int get_arrivalTime(){
        return arrivalTime;
    }
    int get_runTime(){
        return runTime;
    }
    int get_priority(){
        return priority;
    }
    void set_next_ptr(NodeLL *input_pointer){
        next = input_pointer;
    }
    NodeLL* get_next_ptr(){
        return next;
    }
    void set_right_ptr(NodeLL *input_pointer){
        right_T = input_pointer;
    }
    NodeLL* get_left_ptr(){

        return left_T;
    }
    void set_left_ptr(NodeLL *input_pointer){
        left_T = input_pointer;
    }
    NodeLL* get_right_ptr(){
        return right_T;
    }
    //Getters and Setters ends
    void set_run_Time(){ //decreases run time by 1
        this -> runTime--;
    }
};
//Declaration of LinkedList Class
class LinkedList{
    //Declaration of private members
private:
    NodeLL *head = NULL;
    int num_of_search = 0;
    int num_of_insert = 0;
    //Declaration of public members
public:
    LinkedList(){ //empty constructor
    }
    void add_node(NodeLL input_node){ //Node which will be added to the list is created in the below row with dynamic memory allocation.
        //General algorithm is as follows:
        //First, we check if the list is empty, if it is empty, then the node is placed into head.
        //Then, we compare the priority of the incoming nodes and the head node.If incoming node is more important, then it is placed into head.
        //Previous head and rest of the nodes are shifted by one. We can implement that since we know that linked list was in order before incoming node.
        //Finally, we know that the list is in order and the another incoming node will not be placed in the head. Hence, we can safely consider between two nodes.
        //If a suitable place is found for incoming node(n1), it will be placed into (n2) and (n3) nodes. We can satisfy that by comparing the priorities and
        //n2 next will be assigned to n1 and n1 next will be assigned to n3. Algorithm will check until the next ptr is NULL. If it is null, we know that we should place the node
        //before NULL ptr.
        NodeLL *yeni = new NodeLL(input_node.get_processID(),input_node.get_arrivalTime(),input_node.get_runTime(),input_node.get_priority());
        NodeLL *temp = head;
        bool node_added = false;
        if(head == NULL){
            head = yeni;
            yeni->set_next_ptr(NULL);
            node_added = true;
            num_of_insert ++;
        }
        else if (head->get_next_ptr() == NULL || temp->get_priority() > yeni->get_priority() ) {

                if (temp->get_priority() > yeni->get_priority()) {

                    head = yeni;
                    yeni->set_next_ptr(temp);
                    num_of_insert = num_of_insert + 2;
                    node_added = true;

                }
            }

        while (node_added == false){
            num_of_insert ++;
            NodeLL *temp2 = temp->get_next_ptr();
            if (temp2 == NULL){
                temp->set_next_ptr(yeni);
                yeni->set_next_ptr(NULL);

                node_added = true;
            }
            else{

            if(temp2->get_priority() > yeni->get_priority()){

                temp->set_next_ptr(yeni);
                yeni->set_next_ptr(temp2);
                num_of_insert ++;
                node_added = true;
            }
            }
            temp = temp2;
        }

    }
    NodeLL* get_head(){ //This method returns the head of the list. It also checks if the list is empty or not.
        NodeLL* ret_head_temp;
        if(head != NULL){

            ret_head_temp = head;
            return ret_head_temp;
        }
    }

    void delete_head(){ // As it is explained in the add_node method, list is in order with respect to priorities.
                        // Hence, head node is has the most priority. Therefore, we can delete head and get rid of the
                        // node with the highest priority.
        NodeLL *temp;
        temp = head;
        if(temp == NULL){
            return;
        }
        else{
        head = temp->get_next_ptr();
        temp->set_next_ptr(NULL); // head is shifted by 1 and previous head is assigned as NULL
        num_of_search ++;
        }
    }
    void printLL(){
        NodeLL *temp;
        temp = head;
        while(temp!= NULL){
            cout<<temp->get_processID()<<"-"<<temp->get_priority()<<"\t"; //Prints the process ID's of the linked list members
            temp = temp->get_next_ptr();
        }
        cout<<endl<<num_of_search<<" nodes visited for searching"<<endl; //Prints the number of search for linked list
        cout<<num_of_insert<<" nodes visited for inserting"<<endl;//Prints the number of insert for linked list

        }

    int isEmpty(){ //Checks if the linked list is empty. If head is NULL, then we have no nodes in Linked Lists.
        return(head == NULL);
    }




};
//Declaration of Tree Class
class Tree{
private:
    //private members
    int processID;
    int arrivalTime;
    int runTime;
    int priority;
    NodeLL *root = NULL;
    int num_of_search_T = 0;
    int num_of_insert_T = 0;
public:
    //Empty Constructor
    Tree(){
    }
    //Addition of a node into the tree
    void add_node_tree(NodeLL input_node){ //added node will be taken as input.
        NodeLL *yeni = new NodeLL(input_node.get_processID(),input_node.get_arrivalTime(),input_node.get_runTime(),input_node.get_priority());
        //a new node is created dynamically and initialized as input_node

        //if root == NULL, then tree is empty. Hence, new node should be added to the tree
        if (root == NULL){
            root = yeni;
            yeni->set_left_ptr(NULL);
            yeni->set_right_ptr(NULL);
            num_of_insert_T++;
        }
        //else we have at least one element in the tree.
        else{
            //we will start looking from the root and move according to the input_node's priority.

            NodeLL *temp = root;
            num_of_insert_T++;
            while(true){//while loop will turn until the node is inserted.
            //if the node's priority is lower than root's priority, it will be placed to the left-hand side of the parent.
            if (yeni->get_priority() < temp->get_priority()){ //If the new node's priority is less than the root's priority
                if(temp->get_left_ptr() == NULL){//When an available place is found, place the new node.
                temp->set_left_ptr(yeni);
                num_of_insert_T++;
                break;
                }

            temp = temp->get_left_ptr(); //If available place could not be found, then we should iterate the temp node by and start looking again
            num_of_insert_T++;
            }
            else{
                //if the node's priority is greater than root's priority, it will be placed to the right-hand side of the parent.
                if(temp->get_right_ptr() == NULL){//When an available place is found, place the new node.
                    temp->set_right_ptr(yeni);
                    num_of_insert_T++;
                    break;
                }
                temp = temp->get_right_ptr(); //If available place could not be found, then we should iterate the temp node by and start looking again
                num_of_insert_T++;
            }
        }
        }

        return;
        }


    bool isEmpty(){
        return (root == NULL); //if root == NULL, then tree is empty
    }
    NodeLL* getroot(){ //get root method is set in case of any need.
        NodeLL* ret_root_temp;
        if(root != NULL){
            ret_root_temp = root;
            return ret_root_temp;
        }
    }

    NodeLL* deleteTree(){ //
        NodeLL *temp;
        NodeLL *old = NULL;
        temp = root;
        num_of_search_T++;
        while(temp->get_left_ptr()!=NULL){ //temp will start from the root and search through the binary search tree.
            old = temp;
            temp = temp->get_left_ptr(); //As we will iterate the temp, we should also remember the old value of the temp.
            num_of_search_T++;
        }
        if(old == NULL){
            root = temp->get_right_ptr();
            return temp;
        }
        else {
            if(temp->get_right_ptr() == NULL){
                old->set_left_ptr(NULL);
                return temp;
            }
            else{
                old->set_left_ptr(temp->get_right_ptr()); //reconnect the tree
                return temp;
            }
        }

    }

    void printT(){ //prints the number of search and number of insert
        cout<<endl<<num_of_search_T<<" nodes visited for searching"<<endl;
        cout<<num_of_insert_T<<" nodes visited for inserting"<<endl<<endl;
    }
};

int main() {

    //Taken from homework manuel

    /* reading processes from file */

     ifstream processesFile; /* input file stream */

     processesFile.open ("processes.txt");
     int numProcesses; /* number of processes */
     processesFile >> numProcesses; /* read from file */
      NodeLL process_arr_LL[numProcesses]; /* create Node array */
      NodeLL process_arr_T[numProcesses]; /* create Node array */
      LinkedList RQ;
      Tree RQT;
      int processID, arrivalTime, runTime, priority;
      for(int i=0; i<numProcesses; ++i){  /* read 4 integers from file */
          processesFile >> processID >> arrivalTime >> runTime >> priority; /* construct i'th element of the array */
          process_arr_LL[i] = NodeLL(processID, arrivalTime, runTime, priority); // Create Node
          process_arr_T[i] = NodeLL(processID, arrivalTime, runTime, priority); // Create Node
      }
      processesFile.close();

/* end of reading from file */


     cout<<"Linked List Implementation RQ"<<endl<<endl;
     //Initialization of variables for Linked List Implementation
     int time = 0;
     bool CPUBusy = false;
     NodeLL *currentProcess = NULL;
     int processIndex = 0;

     while(processIndex < numProcesses || (!RQ.isEmpty()) || (CPUBusy == true)){
         if (processIndex < numProcesses){
             if (process_arr_LL[processIndex].get_arrivalTime() == time){
                 RQ.add_node(process_arr_LL[processIndex]);
                 processIndex++;

             }
         }
         if (CPUBusy == true){
             currentProcess->set_run_Time();

         }
         if(currentProcess != NULL){
             if(currentProcess->get_runTime() == 0){
                 cout<<currentProcess->get_processID()<<endl;
                 CPUBusy = false;
                 //cout<<"3.if"<<endl;
             }
         }
         if((CPUBusy == false) && (!RQ.isEmpty())){
             currentProcess = RQ.get_head();
             RQ.delete_head();
             CPUBusy = true;

         }

       time++;
     }

       RQ.printLL();




          cout<<endl<<"Binary Search Tree Implementation RQ"<<endl<<endl;
          //Initialization of variables for Binary Search Tree Implementation
          int time_T = 0;
          bool CPUBusy_T = false;
          NodeLL *currentProcess_T = NULL;
          int processIndex_T = 0;

          while(processIndex_T < numProcesses || (!RQT.isEmpty()) || (CPUBusy_T == true)){
              if (processIndex_T < numProcesses){
                  if (process_arr_T[processIndex_T].get_arrivalTime() == time_T){
                      RQT.add_node_tree(process_arr_T[processIndex_T]);
                      processIndex_T++;

                  }
              }
              if (CPUBusy_T == true){
                  currentProcess_T->set_run_Time();

              }
              if(currentProcess_T != NULL){
                  if(currentProcess_T->get_runTime() == 0){
                      cout<<currentProcess_T->get_processID()<<endl;
                      CPUBusy_T = false;

                  }
              }
              if((CPUBusy_T == false) && (!RQT.isEmpty())){
                  currentProcess_T = RQT.deleteTree();
                  CPUBusy_T = true;

              }

              time_T++;

          }

          RQT.printT();

     return 0;
     }


