#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdexcept>
#include <iostream>
#include "Node.h"

using namespace std;

template <typename E>
class LinkedList{
private:
    Node <E> * head;
    Node <E> * tail;
    Node <E> * current;
    int size;
public:
    LinkedList(){
        current = tail = head = new Node<E>();
        size = 0;
    }
    ~LinkedList(){
        clear();
        delete head;
    }
    void insert(E pElement){
        current->next = new Node<E>(pElement, current->next);
        if(current == tail) tail = current ->next;
        size++;
    }
    void append(E pElement){
        tail->next = new Node<E>(pElement);
        tail=tail->next;
        size++;
    }
    E remove()throw(runtime_error){
        if(current == tail)throw runtime_error("No hay elemento");
        E res = current->next->element;
        Node<E> * temp = current->next;
        if(current->next== tail) tail = current;
        current->next=current->next->next;
        delete temp;
        size--;
        return res;
    }
    void clear(){
        current = head->next;
        while(head->next != NULL){
            head->next = head->next->next;
            delete current;
            current = head->next;
        }
        tail = current = head;
        size = 0;
    }
    E getElement()throw(runtime_error){
        if(current == tail)throw runtime_error("No hay elemento");
        return current->next->element;
    }
    void goToStart(){
        current = head;
    }
    void goToEnd(){
        while(current->next!=tail){
            current=current->next;
        }
    }
    void goToPos(int pos)throw(runtime_error){
        if(pos>=size || pos<0) throw runtime_error("Posicion invalida");
        current = head;
        while(pos>0){
            current=current->next;
            pos--;
        }
    }
    void previous(){
        Node<E> * cursor = head;
        while(cursor->next!=current){
            cursor=cursor->next;
        }
        current=cursor;
    }
    void next(){
        if(current->next!=tail)current=current->next;
    }

    int getPos(){
        int pos = 0;
        Node<E> * temp = head;
        while(temp != current){
            pos++;
            temp = temp->next;
            }
        return pos;
    }


    int getSize(){
        return size;
    }

    void imprimir(){
        Node<E> *temp = head;
        while(temp != tail){
            if(temp == current) cout << "Current-> ";
            cout<<"-"<<temp->next->element<<" ";
            temp = temp->next;
        }
    }
    void intercambiarNodo(){
        if(current->next == NULL) cout<<"\nDeben haber al menos 2 elementos delante del current\n";
        else if(current->next -> next == NULL) cout<<"\nDeben haber al menos 2 elementos delante del current\n";
        else{
            Node<E> *temp = current->next->next;
            current->next->next = current ->next->next->next;
            temp->next = current->next;
            current->next = temp;
            temp=head;
            while(temp->next != NULL) temp=temp->next;
            tail = temp;
        }
    }

};

#endif // LINKEDLIST_H
