#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include "flightticket.h"
#include "mylist.h" 	

using namespace std;

template<typename T>
class Node;
template<typename T>
class MyList;


class HashNode
{
	private:
		string key; // key = companyName+','+flightNumber
		Flight_Ticket value;
	public:
		HashNode(){};
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}

		string getkey() const		//method to return key of node
		{	
			return this ->key;
		}
		Flight_Ticket getvalue() const	//method to return flightticket object of node	
		{
			return this -> value;
		}

		
		friend class FlightHASHTABLE;
		template <typename> friend class MyList;
};

//=============================================================================

bool operator==(const HashNode& node1, const HashNode& node2);		//operator to compare two nodes
bool operator!=(const HashNode& node1, const HashNode& node2);

class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;		//List of Buckets, Please create your own Linked List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int hashmethod;

	public:
		FlightHASHTABLE(int hashmethod);						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file
		int count_collisions();					//return the number of collisions in the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		void increase_size();
		int next_prime(int cap);
		bool is_prime(int cap);

};

#endif


