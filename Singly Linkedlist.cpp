/*
    Author: Fardaws Hassan Shuvro
    Date: 26 December 2020


    Singly LinkedList
    --------------------
    Documentation:
        push():         Time Complexity O(1), add element at the end, take integer as a parameter.
        pushFront():    Time Complexity O(1), add element at the front, take integer as a parameter.
        pushAfter():    Time Complexity O(1) using address and O(n) using position, add element after an element, take position number ( or address ) and a value as parameter.
        updateNode():   Time Complexity O(1) using address and O(n) using position, update an element, take position number ( or address ) and a value as parameter.
        deleteNode():   Time Complexity O(n), delete an element, take position number ( or address ) as parameter.
        pop():          Time Complexity O(n), delete an element from the end.
        show():         Time Complexity O(n), show all the elements.
*/

#include <iostream>

using namespace std;

class Node{
public:
    int value;
    Node* next;
};


class Linkedlist{
public:
    Node* head_node = NULL;
    Node* tail_node = NULL;
    void push(int value){
        // time complexity O(1)
        Node* new_node = new Node();
        new_node->value = value;
        new_node->next = NULL;
        if(tail_node==NULL){
            head_node = new_node;
        }else{
            tail_node->next = new_node;
        }
        tail_node = new_node;
    }
    void pushFront(int value){
        // time complexity O(1)
        if(head_node == NULL){
            push(value);
        }else{
            Node* new_node = new Node();
            new_node->value = value;
            new_node->next = head_node;
            head_node = new_node;
        }
    };
    void pushAfter(Node* temp,int value){
        // time complexity O(1)
        Node* new_node = new Node();
        if(tail_node==temp){
            tail_node = new_node;
        }
        new_node->value = value;
        new_node->next = temp->next;
        temp->next = new_node;
    };
    void pushAfter(long int index,int value){
        pushAfter(address_of(index),value);
    }

    void updateNode(Node* temp,int value){
        // time complexity O(1)
        temp->value = value;
    };
    void updateNode(long int index,long int value){
        updateNode(address_of(index),value);
    };

    void deleteNode(Node* address){
        // time complexity O(n)
        Node* current = head_node;
        while(true){
            if(head_node==address){
                head_node = head_node->next;
                break;
            }else if(current->next==address){
                if(address == tail_node){
                    tail_node = current;
                }
                current->next = address->next;
                break;
            }
            current = current->next;
        }
    };
    void deleteNode(long int index){
        // time complexity O(n)
        Node* prev_node = previous_of(index);
        if(prev_node==NULL){
            head_node = head_node->next;
        }else{
            if((prev_node->next)==tail_node){
                tail_node = prev_node;
            }
            prev_node->next = (prev_node->next)->next;
        }
    }
    Node* previous_of(long int index){
        Node* current = head_node;
        Node* prev = NULL;
        for(int i=1;i<index;i++){
            prev = current;
            current= current->next;
        }
        return prev;
    };
    Node* address_of(long int index){
        Node* prev_node = previous_of(index);
        if(prev_node==NULL){
            return head_node;
        }
        return prev_node->next;
    };
    void pop(){
        // time complexity O(n)
        deleteNode(tail_node);
    };
    void show(){
        // time complexity O(n)
        if(head_node == NULL){
            cout<<"No value available.\n";
        }else{
            long int index = 1;
            Node* temp = head_node;
            while(true){
                if(temp->next==NULL){
                    cout<<index<<". value: "<<temp->value<<"\taddress: "<<temp<<"\n";
                    break;
                }
                cout<<index<<". value: "<<temp->value<<"\taddress: "<<temp<<"\n";
                temp = temp->next;
                index++;
            }
        }
    }
};



int main(){
    Linkedlist L_list;
    string command;
    cout<<"available method: push  pop  update  show  pushfront  pushafter  delete\n";
    cout<<"-----------------------------------------------------------------------\n\n\n";
    while(command!="exit"){
        cin>>command;
        if(command=="push"){
            cout<<"enter value: ";
            int value;
            cin>>value;
            L_list.push(value);
        }else if(command=="pop"){
            L_list.pop();
        }else if(command=="show"){
            L_list.show();
        }else if(command=="pushfront"){
            cout<<"enter value: ";
            int value;
            cin>>value;
            L_list.pushFront(value);
        }else if(command=="pushafter"){
            cout<<"enter position and value: ";
            int value;
            long int position;
            cin>>position>>value;
            L_list.pushAfter(position,value);
        }else if(command=="update"){
            cout<<"enter position and value: ";
            int value;
            long int position;
            cin>>position>>value;
            L_list.updateNode(position,value);
        }else if(command=="delete"){
            cout<<"enter position: ";
            long int position;
            cin>>position;
            L_list.deleteNode(position);
        }
    }
    return 0;
}
