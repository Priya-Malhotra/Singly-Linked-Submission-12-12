#include "slist.h"
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>


using namespace std;

// this i the one in your lib
// Constructor
slist::slist() {
 length = 0;
 head = NULL;
}

// Destructor
slist::~slist(){
 Node* current = this->head;
 while(current){
 this->head = current->next;
 this->length -= 1;
	delete current;
	current = this->head;
 }
 cout << "LIST DELETED: " << this->length << endl;
}

// add(value)	//Adds a new value to the end of this list.
void slist::add(Airport value) {
//making a new node with the thing from slist.h
 Node* newNode = new Node();
 //making the data part of the newNode to be set to the input value
 newNode->data = value;
 //this newNode isn't pointing to anything
 newNode->next = NULL;

 //making a Node variable cursor thing and making it start at the first node in the list
 //SOURCE OF ERROR? should it be this->head or just head?
 //asked, no diff. 
 Node *current = head;

 if(current != NULL) {//checking to make sure that the list just isn't completely empty
 while(current->next != NULL) {//as long as there is a next thing
 current = current ->next;//go to the next thing; so the cursor is moving over to the next Node
 }
 current->next = newNode;


 }
 else {
 head = newNode;
 }
 this->length++;

}

/* double Complex:: imag(const Complex& c) */
// clear()	//Removes all elements from this list.
void slist::clear() {
 Node* current = this->head;
 while(current){
 this->head = current->next; // making the head of the list actually the next Node in the list
 this->length -= 1;//just as we added one to this->length at the end of add because we put one more, we need to make the length of the list shorter because we are going to delete a Node
	delete current;
	current = this->head;
 }
}
//equals() //Returns true if the two lists contain the same elements in the same order.
bool slist::equals(slist list)	{
 bool isEqual = true;
 Node* current = head;
 Node* other = list.head;

 if(list.size() != length) {//if something as simple as length isn't the same, then obviously the lists aren't the same. It'll return false.
 isEqual = false;
 }

 while(current) {
 string codeThis(current->data.code);
 string codeOther(other->data.code);
 bool code = codeThis.compare(codeOther) == 0;
 bool lat = (current->data.latitude) == (other->data.latitude);
 bool longt = (current->data.longitude) == (other->data.longitude);
 if(!(code && lat && longt )){
 isEqual = false;
 }

 current = current->next;
 other = other->next;
 }

 return isEqual;

}

//get(index)	//Returns the element at the specified index in this list.
Airport slist::get(int index) {
  Airport a;
 Node* current = head;
 Node* returnNode;
 int i = 0;
 while(current!= NULL) {
 if(i == index) {
    returnNode = current;
    return returnNode->data;
 }
  i++;
  current = current->next;
 }
 return a; 
}
//insert(index, value)	//Inserts the element into this list before the specified index.
void slist::insert(int index, Airport value){
 Node* current = head;
 Node* previous = head;
 Node* ahead = head->next;
 Node* addNode = new Node();
 addNode->data = value;
 int i = 0;
 if(index == 0) {
 head->next = addNode;
 addNode->next = ahead;
 }
 else if(index == length) {
 while(current) {
 current = current->next;
 }

 current->next = addNode;
 addNode->next = NULL;
 }
 else {
 while(current != NULL || i != index) {
 previous = current;
 current = current->next;

 i++;
 }
 previous->next = addNode;
 addNode->next = current;
 }

 length++;

}

void slist::exchg(int index1, int index2) { //Switches the payload data of specified indexex.
 Airport index1Airport = get(index1);
 Airport index2Airport = get(index2);

 Node* current1 = head;
 Node* returnNode1;
 int one = 0;
 while(current1!= NULL) {
 if(one == index1) {
 current1->data = index1Airport;
 }
 one++;
 current1 = current1->next;
 }

 Node* current2 = head;
 Node* returnNode2;
 int two = 0;
 while(current2!= NULL) {
 if(two == index2) {
 current2->data = index2Airport;
 }
 two++;
 current2 = current2->next;
 }

}

void slist::swap( int index1, int index2) { //Swaps node located at index1 with node at index2
 Node* ind1;
 Node* previous1;
 Node* ind2;
 Node* previous2;

 int one = 0;
 int two = 0;

 while(ind1 || index1 == one) {
 previous1 = ind1;
 ind1 = ind1->next;

 }
 while(ind2 || index2 == two) {
 previous2 = ind2;
 ind2 = ind2->next;
 }


 if(index2 < index1) {
 Node* temp;
 temp = ind1;
 ind1 = ind2;
 ind2 = temp;

 int tempNum = index1;
 index1 = index2;
 index2 = tempNum;
 }
 //swap ind1 is first
 if(index1 != 0 && index2 != length-1) {
 Node* ahead = ind1->next;
 ind1->next = ind2->next;
 previous2->next = ind1;
 previous1->next = ind2;
 ind2->next = ahead;
 } else if(index1 == 0 && index2 != length-1){
 Node* ahead = ind2->next;
 previous2->next = ind1;
 ind1->next = ahead;

 head = ind2;

 }
 else if(index1 == 0 && index2 == length-1){
 ind1->next = NULL;
 previous2->next = ind1;
 head = ind2;
 }else {
 ind2->next = ind1->next;
 previous1->next = ind2;
 previous2->next = ind1;
 ind1->next = NULL;
 }


}


bool slist::isEmpty() {	//Returns true if this list contains no elements.
 if(length == 0) {
 return true;
 }else {
 return false;
 }

}

void slist::remove( int index) { //Removes the element at the specified index from this list.
 int i = 0;
 Node *current = head;
 Node *previous;

 //check if there is anything in the list at all
 if(current != NULL) {

 //go through the list until either you reach the end or if you get to ur position
 while(i != index && current->next != NULL) {
 previous = current;
 current = current ->next;
 i++;
 }
 // if we have reached the right spot
 if(index == i) {
 this->length--;
 //check for special case 0
 if(index == 0 ) {
 head = head->next;
 }
 //regular numbers
 else {
 previous->next = current ->next;

 }

 }
 //if we didnt reach the location, that means index out of bounds
 else {}

 }
 else {}


}

// set(index, value)	//Replaces the element at the specified index in this list with a new value.
void slist::set(int index, Airport value) {
 Node *current = head;
 int i = 0;
 while(current || i != index ) {
 current = current->next;
 }
 current->data = value;

}


int slist::size() { //Returns the number of elements in this list.
 return length;

}

slist slist::subList(int start, int length) { //
 Node* starting = head;
 int s =0;
 while(starting || s != start) {
 starting = starting->next;

 }

 slist *newList = new slist();
 for(int i = 0; i < length; i++) {
 newList->add(starting->data);
 starting = starting->next;
 }

 return *newList;

}

// toString() //Converts the list to a printable string representation.
void slist::toString(){
  Node* head = this->head;
 int i = 0;
 while(head){

 string code(head->data.code);
 cout << i << ": " << code << " " << head->data.latitude << " " << head->data.longitude << endl;
 head = head->next;
 i++;
 }
}