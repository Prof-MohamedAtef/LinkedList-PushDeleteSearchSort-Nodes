#include <iostream>
#include<cstring>
#include <string.h>
using namespace std;


class Person {
public:
    string Name;
    int PhoneNumber;
    string Address;
    int IDNumber;

    Person* next;
    Person* prev;
};

int input;
string name;

void printListForwardDirection(Person* p){
    Person* last;
    cout<<"\nTraversal in forward direction \n";
    while (p != NULL)
    {
        cout<<"ID: "<<p->IDNumber<<" Address: "<<p->Address<<" Name: "<<p->Name<<endl;
        last = p;
        p = p->next;
    }
    return;
}

/*void printListReversDirection(Person* p){

    Person* last;

    while (p != NULL)
    {
        last = p;
        p = p->next;
    }

    cout<<"\nTraversal in reverse direction \n";
    while(last!=NULL){
        cout<<"ID: "<<last->IDNumber<<" Address: "<<last->Address<<endl;
        last=last->prev;
    }
}*/
void printList(Person* p){

    Person* last;
    cout<<"\nTraversal in forward direction \n";
    while (p != NULL)
    {
        cout<<"ID: "<<p->IDNumber<<" Address: "<<p->Address<<" Name: "<<p->Name<<endl;
        last = p;
        p = p->next;
    }

    cout<<"\nTraversal in reverse direction \n";
    while(last!=NULL){
        cout<<"ID: "<<last->IDNumber<<" Address: "<<last->Address<<" Name: "<<last->Name<<endl;
        last=last->prev;
    }
}

void pushPersonNode(Person** head_ref, int newIdNum, string newAddress, string newName){
    /* 1. allocate node */
    Person* newPerson=new Person();

    /* 2. put in the data */
    newPerson->IDNumber=newIdNum;
    newPerson->Address=newAddress;
    newPerson->Name=newName;

    /* 3. Make next of new node as head
    and previous as NULL */
    newPerson->next=(*head_ref);
    newPerson->prev=NULL;

    /* 4. change prev of head node to new node */
    if((*head_ref)!=NULL){
        (*head_ref)->prev=newPerson;
    }

    /* 5. move the head to point to the new node */
    (*head_ref)=newPerson;
}

void insertAfter(Person* last_node, int newIdNum,string newAddress, string newName){
    /*1. check if the given last_node is NULL */
    if (last_node == NULL) {
        cout << "The given previous node cannot be NULL";
        return;
    }

    /* 2. allocate new node */
    Person* new_node = new Person();

    /* 3. put in the data */
    new_node->IDNumber= newIdNum;
    new_node->Address=newAddress;
    new_node->Name=newName;

    /* 4. Make next of new node as next of last_node */
    new_node->next=last_node->next;

    /* 5. Make the next of last_node as new_node */
    last_node->next=new_node;

    /* 6. Make last_node as previous of new_node */
    new_node->prev=last_node;

    /* 7. Change previous of new_node's next node */
    if(new_node->next!=NULL){
        new_node->next->prev=new_node;
    }
}

void append(Person**head_ref, int newIdNum, string newAddress, string newName){
    /* 1. allocate node */
    Person* new_node=new Person();


    /* used in step 5*/
    Person *last=*head_ref;


    /* 2. put in the data */
    new_node->IDNumber=newIdNum;
    new_node->Address=newAddress;
    new_node->Name=newName;

     /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
    new_node->next=NULL;

    /* 4. If the Linked List is empty, then make the new
        node as head */
    if(*head_ref==NULL){
        new_node->prev=NULL;
        *head_ref=new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while(last->next!=NULL){
        last=last->next;
    }

    /* 6. Change the next of last node */
    last->next=new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev=last;

    return;
}

void deleteNodeByID(Person** head_ref, int key){
    ///store head node
    Person* temp=*head_ref;
    Person* prev=NULL;

    /// If head node itself holds
    /// the key to be deleted
    if(temp!= NULL && temp->IDNumber==key){
        *head_ref=temp->next; ///changed head
        delete temp;
        return;
    }

    /// Else Search for the key to be deleted,
    /// keep track of the previous node as we
    /// need to change 'prev->next' */

    else{

        while(temp!=NULL && temp->IDNumber!=key){
            prev=temp;
            temp=temp->next;
        }

        ///if the key not present in the linked list
        if(temp==NULL){
            return;
        }

        ///unlike the node from the linked list
        prev->next=temp->next;
        ///free memory of temp to delete
        delete temp;
    }
}

void deleteNodeByName(Person** head_ref, string key){
    ///store head node
    Person* temp=*head_ref;
    Person* prev=NULL;

    /// If head node itself holds
    /// the key to be deleted
    if(temp!= NULL && temp->Name==key){
        *head_ref=temp->next; ///changed head
        delete temp;
        return;
    }

    /// Else Search for the key to be deleted,
    /// keep track of the previous node as we
    /// need to change 'prev->next' */

    else{

        while(temp!=NULL && temp->Name!=key){
            prev=temp;
            temp=temp->next;
        }

        ///if the key not present in the linked list
        if(temp==NULL){
            return;
        }

        ///unlike the node from the linked list
        prev->next=temp->next;
        ///free memory of temp to delete
        delete temp;
    }
}

void bubbleSortAlgo(Person **pp){
    // p always points to the head of the list
    Person *p = *pp;
    *pp = NULL;

    while (p)
    {
        Person **left_ = &p;
        Person **right_ = &p->next;
        bool swapped = false;

        // keep going until qq holds the address of a null pointer
        while (*right_)
        {
            // if the left side is greater than the right side
            if ((*right_)->Name < (*left_)->Name)
            {
                // swap linked node ptrs, then swap *back* their next ptrs
                std::swap(*left_, *right_);
                std::swap((*left_)->next, (*right_)->next);
                left_ = &(*left_)->next;
                swapped = true;
            }
            else
            {   // no swap. advance both pointer-pointers
                left_ = right_;
                right_ = &(*right_)->next;
            }
        }

        // link last node to the sorted segment
        *right_ = *pp;

        // if we swapped, detach the final node, terminate the list, and continue.
        if (swapped)
        {
            // take the last node off the list and push it into the result.
            *pp = *left_;
            *left_ = NULL;
        }

        // otherwise we're done. since no swaps happened the list is sorted.
        // set the output parameter and terminate the loop.
        else
        {
            *pp = p;
            break;
        }
    }
}


void searchList(Person** head_ref, string name){
    // Stores head Node
    Person* temp = *head_ref;

    // Stores position of the name
    // in the doubly linked list
    int pos = 0;

    // Traverse the doubly linked list
    while (temp->Name != name
           && temp->next != NULL) {

        // Update pos
        pos++;

        // Update temp
        temp = temp->next;
    }

    // If the name not present
    // in the doubly linked list
    bool found;
    //for(int i=0; i<3; i++){
    //}

    if (temp->Name != name){
        cout<<name<<" Does not exist!... Enter another value...\n"<<endl;
    }else{
        found=true;
        cout<<"Name: "<<temp->Name<<" Address: "<<temp->Address<<" ID Number: "<<temp->IDNumber<<endl;
        //break;
    }

    if(!found){
        cout<<"not found.. going to main menu ...\n"<<endl;
    }

    //name
}


Person *findMiddleNode(Person *start, Person *end_){
     // if the list is empty
    if (start == NULL)
        return NULL;

     /*define two pointers: first and second*/
    Person *first = start;
    Person *second = start->next;

    while (second != end_)
    {
        second = second->next;
        if (second != end_)
        {
            first = first->next;
            second = second->next;
        }
    }


    return first;/// first points to the mid of the linked list
}


Person *binarySearchLinkedList(Person *listHead, string name){
    Person *start=listHead;
    Person *end_=NULL;

    do{
        Person *mid=findMiddleNode(start, end_);

        if(mid==NULL){
            return NULL;
        }

        if (mid->Name==name){
            return mid;
        }

        else if(mid->Name<name){
            start=mid->next;
        }

        else
            end_=mid;
    }while(end_==NULL ||
           end_!=start);

    return NULL;
}

int main()
{
    Person* head=NULL;
    Person* second=NULL;
    Person* third=NULL;

    head=new Person();
    second=new Person();
    third=new Person();
    head->IDNumber=111;
    head->Address="cairo st";
    head->Name="Mohamed";
    head->next=second;

    second->IDNumber=222;
    second->Address="Haram st";
    second->Name="Ahmed";
    second->next=third;

    third->IDNumber=333;
    third->Address="Faisal st";
    third->Name="Reham";
    third->next=NULL;

    printList(head);

    cout<<endl<<"Enter 1 to add Node at first...\nEnter 2 to insert new node ...\n";

    cin>>input;

    switch(input){
    case 1:
        pushPersonNode(&head,1, "Garden City", "Nagy");
        printList(head);
        break;
    case 2:
        cout<<endl<<"Enter value to add ...\n";
        cin>>input;
        insertAfter(second,input,"Officer club","Youssef");
        printList(head);
        break;
    }

    cout<<endl<<endl<<"Enter 0 to End program ...\nEnter 1 to append node to the end of the Linked List...\n";

    cin>>input;
    switch(input){
        case 0:
//            exit();
            break;
        case 1:
            cout<<endl<<"Enter value to add ...\n";
            cin>>input;
            append(&head,input,"Rome", "Abdo");
            printList(head);
            break;
    }

    cout<<endl<<endl<<"Enter 0 to End program ...\nEnter 1 to sort list using bubble sort Algorithm...\n";
    cin>>input;

    switch(input){
        case 0:
            break;
        case 1:
            bubbleSortAlgo(&head);
            printListForwardDirection(head);
            break;
    }

    cout<<endl<<endl<<"Enter 0 to End program ...\nEnter 1 to Search for a specific Name using binary search algorithm...\n";
    cin>>input;
    switch(input){
        case 0:
            break;
        case 1:
            string word;
            cout<<endl<<endl<<"Enter your word...\n";
            cin>>word;
            //searchList(&head,word);

             if (binarySearchLinkedList(head, word)){
                cout << "Target element: " << word<< " present in the linked list\n"<<endl;
             }else{
                cout << "Target element: " << word<< " not present in the linked list\n"<<endl;
             }


            printListForwardDirection(head);
            break;
    }

    /*
        delete node
    */
    cout<<endl<<endl<<"Enter 0 to End program ...\nEnter 1 to delete node from the Linked List...\n";
    cin>>input;

    switch(input){
        case 0:
//            exit();
            break;
        case 1:
            cout<<endl<<"Enter 1 to Delete By ID Number...\nEnter 2 to Delete By Name...\n";
            cin>>input;
            switch(input){
                case 1:
                    cout<<endl<<"Enter node value to delete...\n";
                    cin>>input;
                    deleteNodeByID(&head, input);
                    printListForwardDirection(head);
                    break;
                case 2:
                    cout<<endl<<"Enter Name to delete...\n";
                    cin>>name;
                    deleteNodeByName(&head,name);
                    printListForwardDirection(head);
                    break;
            }
            break;
    }
    return 0;
}




///sort by first name... does not sort node itself
/*void bubbleSort(Person *head){
        Person *i= head,*j=head;
        if(i==NULL){
            return;
        }
        int swapped;
        do{
        //while(i!=NULL){
            swapped=0;
            while(j->next!=NULL){
                if(j->Name>j->next->Name){
                    string temp = j->Name;
                    j->Name= j->next->Name;
                    j->next->Name= temp;
                    swapped=1;
                }
                j=j->next;
            }
            j=head;
            i=i->next;
        }
        while(swapped);
    }
*/
