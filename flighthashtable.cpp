#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <chrono>
#include <regex>

#include "flighthashtable.h"
#include "mylist.h"
#include "flightticket.h"



FlightHASHTABLE::FlightHASHTABLE(int hashmethod)       //constructor, initilaize capacity as 1000 and create array of buckets
{
	capacity = 1000;
	size = 0;
	buckets = new MyList<HashNode>[capacity];
    hashmethod = hashmethod;

}

FlightHASHTABLE::~FlightHASHTABLE()
{
	delete[] buckets;					//delete array of buckets

}			

long FlightHASHTABLE::hashCode(string key)
{
	//cycle shift
    if(hashmethod ==1)
    {
	unsigned int hashValue = 0;

    for (size_t i = 0; i < key.length(); i++)
    {
        hashValue = (hashValue << 5) | (hashValue >> 27); // cycle shift left
        hashValue += key[i];
    }

    return hashValue % capacity;
    }


    //polynomial
    else if(hashmethod ==2)
    {
    unsigned int hashValue = 0;
    const unsigned int PRIME = 31; // a prime number for the polynomial calculation

    for (size_t i = 0; i < key.length(); i++)
    {
        hashValue = hashValue * PRIME + key[i];
    }

    return hashValue % capacity;
    }



   //summation
    else if(hashmethod ==3)
    {
    unsigned int hashValue = 0;

    for (size_t i = 0; i < key.length(); i++)
    {
        hashValue += key[i];
    }

    return hashValue % capacity;
    }

}		

int FlightHASHTABLE::importCSV(string path) {
    ifstream fin(path);        //access csv file
    if (!fin) {  // invalid path
        return -1;
    }

    int count = 0;  		//initialize count variable to count number of inputs
    string line;

   	 // read the first line to skip it
    getline(fin, line);			

    regex alpha_regex("^[a-zA-Z ]+$");						//initialize regex variables to check valid inputs
    regex numbers("[0-9]+");
    regex time("^(0?[0-9]|1[0-9]|2[0-3])(:[0-5][0-9])?(:[0-5][0-9])?$");
    regex date_regex("^(0?[1-9]|[1-2][0-9]|3[0-1])-([a-zA-Z]+)$");

    while (getline(fin, line)) {					//iterate through each line and collect variable
        stringstream ss(line);
        string company_name, flight_number, country_of_origin, country_of_destination, stopover, price, time_of_departure, time_of_arrival, date;

        if (!getline(ss, company_name, ',') || !getline(ss, flight_number, ',') ||					//gather variable in each line and check skip line if not in correct format
            !getline(ss, country_of_origin, ',') || !getline(ss, country_of_destination, ',') ||
            !getline(ss, stopover, ',') || !getline(ss, price, ',') ||
            !getline(ss, time_of_departure, ',') || !getline(ss, time_of_arrival, ',') || !getline(ss, date)) {
            cerr << "Error: invalid line format in file " << path << endl;
            continue;
        }

        //check if variables are valid 
        if (!regex_match(company_name, alpha_regex)) {
            continue;
        }
        else if (!regex_match(flight_number, numbers)) {
            continue;
        }
        else if (!regex_match(country_of_origin, alpha_regex)) {
            continue;
        }
        else if (!regex_match(country_of_destination, alpha_regex)) {
            continue;
        }
        else if (!regex_match(stopover, numbers)) {
            continue;
        }
        else if (!regex_match(price, numbers)) {
            continue;
        }
        else if (!regex_match(time_of_departure, time)) {
            continue;
        }
        else if (!regex_match(time_of_arrival, time)) {
            continue;
        }
        else if (!regex_match(date.substr(0,date.find('\r')), date_regex)){  //substring to remove "/r" from extracted date
        	continue;
        }

        //increase size if exceeds capacity 
        if (size >= capacity)
            increase_size();

        //create new flightticket object with variables
        Flight_Ticket* new_ticket = new Flight_Ticket(company_name, stoi(flight_number), country_of_origin,
                                                      country_of_destination, stopover, price, time_of_departure,
                                                      time_of_arrival, date.substr(0,date.find('\r')));

        //add as new node

        add(new_ticket);

        //increment count
        count++;

        
    }

    fin.close();
    return count;
}

int FlightHASHTABLE::exportCSV(string path)
{
	 ofstream fout(path); // create a new file with the specified path
    
    if (!fout) // check if the file was successfully created
    {
        return -1;
    }
    
    int count = 0; // keep track of the number of flight tickets written to the file
    
    // iterate over all the buckets in the hash table
    for (int i = 0; i < capacity; i++)
    {
        MyList<HashNode> bucket = buckets[i]; // get the current bucket
        
         for (int j = 0; j < bucket.size(); j++) 
         {
            // traverse each node in the bucket
            HashNode node = *bucket[j];
            Flight_Ticket ticket = node.value;

            // write the flight ticket to the output file
            fout << ticket.companyName << ",";
            fout << ticket.flightNumber << ",";
            fout << ticket.country_of_origin << ",";
            fout << ticket.country_of_destination << ",";
            fout << ticket.stopOver << ",";
            fout << ticket.price << ",";
            fout << ticket.time_of_departure << ",";
            fout << ticket.time_of_arrival << ",";
            fout << ticket.date << endl;

            count++;
            }
        }
    
    fout.close(); // close the file
    
    return count; // return the number of flight tickets written to the file
}


int FlightHASHTABLE::count_collisions()
{
	int collision_count = 0;		//initialize count 

    for (int i = 0; i < capacity; i++) 	//iterate through nodes in buckets
    {
    	MyList<HashNode>& bucket = buckets[i];
    	Node<HashNode>* current = bucket.head;
    	
    	//unique_keys.clear();			//clear set for each new bucket

    	if(current == NULL)				//if the bucket is empty, go on to next bucket
    		continue;
    	if(bucket.size()==1)			//if there is one node in bucket, there is no collision, go on to next bucket
    		continue;
    	if(bucket.size()>1)			//if there are multiple nodes in a bucket
    	{
	       collision_count += bucket.countCollision(); 	//call countcollision method for each bucket
		}
    }
	cout << capacity <<endl;
    return collision_count;
}

int FlightHASHTABLE::add(Flight_Ticket* data)
{    
  	string lowercaseCompanyName;				
  	string companyName = data -> companyName;				//convert company name to lowercase

	for (int i = 0; i < companyName.length(); i++) 
	{
    lowercaseCompanyName += tolower(companyName[i]);
	}
    string flightNumberStr = to_string(data->flightNumber);				//convert flight number to string
    string key = lowercaseCompanyName + flightNumberStr;				//initialize key 

   
    int index = hashCode(key);    					// compute the hash value for the key
    
    MyList<HashNode>* bucket = &(buckets[index]); 		//access bucket with hashed index
	Node<HashNode>* current = bucket->head; 		
    
	while (current!=NULL) 
	{ 
	    if (current->data->key == key && (current->data->value) == *data)      //check if there are exact same datas, if so, disallow
	    { 
	        return -1; 
	    }
	    current = current-> next;					//move on to next node
	}
    
    HashNode* newNode = new HashNode(key, *data);      	//create new node	 

    bucket->addFront(newNode);							//add the flight record to the corresponding bucket
    size++;


    if(size >= capacity){					//increment capacity if size becomes larger than capacity
    	increase_size();
    }
    return 1;

}	


void FlightHASHTABLE::removeRecord (string companyName, int flightNumber)
{
	string lowercaseCompanyName;
	for (int i = 0; i < companyName.length(); i++) 
	{
    lowercaseCompanyName += tolower(companyName[i]);
	}
    string flightNumberStr = to_string(flightNumber);
    string key = lowercaseCompanyName + flightNumberStr;			//initialize key

    int index = hashCode(key);							//convert key to hashcode

    MyList<HashNode>* bucket = &(buckets[index]); 	//access bucket with hashed index
    Node<HashNode>* current = bucket->head; 					
    HashNode* toRemove = nullptr;					//initialize node variable to store data to remove

   										 
    while (current != nullptr) {					//traverse the list and find the node to remove
        if (current->data->key == key) {
            if (bucket->size() == 1) {				//if there is only one record in the bucket, remove it
                toRemove = current->data;			//store data to remove
                bucket->remove(current);			//remove node
                delete toRemove;					//remove data
                size--;						//decrease size
                cout << "The Flight Ticket has been successfully deleted!";
                return;
            }
            //if there are multiple records in the bucket, select one
            else 
            {
                cout << "Multiple records found : " << endl;		
                int count = 1;
                Node<HashNode>* temp = bucket->head;			//iterate nodes and display them on screen for user to select
                while (temp != nullptr) {
                    if (temp->data->key == key) {			
                        cout << count << ". " << temp->data->value.toString() << endl;
                        count++;
                    }
                    temp = temp->next;
                }
                cout << "Please select the record you want to delete: ";			//user selects record to delete
                int selection;
                cin >> selection;
                cin.clear();
                cin.ignore();
                if (selection <= 0 || selection >= count) {					//check if the user entered a valid selection
                    cerr << "Invalid selection. Record not removed." << endl;
                    return;
                }
                //traverse the list again and find the selected node to remove
                temp = bucket->head;
                count = 1;						//variable to stop at the selected node
                while (temp != nullptr) {			
                    if (temp->data->key == key) {			//if the selected node is found, delete node and data
                        if (count == selection) {
                            toRemove = temp->data;
                            bucket->remove(temp);
                            delete toRemove;
                            size--;
                            cout << "The Flight Ticket has been successfully deleted!";
                            return;
                        }
                        count++;					
                    }
                    temp = temp->next;
                }
            }
        }			
        current = current->next;
    }

    //if no record was found, print a warning message
    if (toRemove == nullptr) {
        cerr << "Record not found. Unable to remove." << endl;		
    }
}

void FlightHASHTABLE::find(string companyName, int flightNumber)
{

	string lowercaseCompanyName;	
	for (int i = 0; i < companyName.length(); i++) 
	{
    lowercaseCompanyName += tolower(companyName[i]);
	}
    string flightNumberStr = to_string(flightNumber);
    string key = lowercaseCompanyName + flightNumberStr;			//get key, hash

    int index = hashCode(key);
   
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();		//start time

    MyList<HashNode> *bucket = &buckets[index]; 		//access bucket of hashed index

    if(bucket->head == NULL)							//if the bucket is empty, return
    {
    	cout << "flight not found" << endl;
    	return;
    }
    else								//if bucket is not empty
    {
    	Node<HashNode> *current = bucket->head;		//access nodes
    	int count = 0;
    	for (int i = 0; i < bucket->size(); i++) 	//iterate nodes to display them
    	{
    		if(current->data->key == key)			//if the node's key matches the key to fins, display on screen
    			{count++;
    			cout<<count<<". "<< endl<< current -> data ->value.toString();}
    		current = current -> next;
    	}

    	 std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
		long long time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();		//stop, record time
		double time_seconds = time / 1000000.0;
		std::cout << "Time taken by find execution: " << time_seconds << " seconds" << std::endl;
    }
 
}	

void FlightHASHTABLE::allinday(string date)
{
	bool found = false;									//declare boolean variable to see if node was found
    for (int i = 0; i < capacity; i++) 			//iterate through whole hash table
    {
    	MyList<HashNode> *bucket = &buckets[i];		//access bucket
    	Node<HashNode> *current = bucket->head;

        if (current != NULL) 						//iterate through list
        {
            while(current != NULL) 
            {
                HashNode* current_data = current -> data;	//access node
                if (current_data->value.date == date) 		//if the node's data matches the date
                {
                    cout << current_data->value.toString2() << endl;		//display node
                    found = true;
                }
                current = current->next;
            }
        }
    }
    if (!found) {
        cerr << "Not Found!" << endl;				//print message if node that matches date does not exist

}	
}				

void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{

    string lowercaseCompanyName;
    for (int i = 0; i < companyName.length(); i++) 
    {
        lowercaseCompanyName += tolower(companyName[i]);
    }
    string flightNumberStr = to_string(flightNumber);
    string key = lowercaseCompanyName + flightNumberStr; 			

    unsigned int index = hashCode(key);						//get key, hashcode

    MyList<HashNode> *bucket = &buckets[index]; 		//access bucket, list
    Node<HashNode> *current = bucket->head;

    if(bucket->head == nullptr)							//if bucket is empty, print message, return
    {
        cout << "Flight not found" << endl;
        return;
    }
    else							//if bucket is not empty,
    {
        const int MAX_FLIGHTS = bucket->size();		//maximum number of flights in the bucket
        Flight_Ticket flights[MAX_FLIGHTS];			//array to store flight tickets with matching key
        int count = 0;								//counter for the number of flights found

        while (current != nullptr)
        {
            if (current->data->getkey() == key)		//if the corresponding key matches the key to search
            {
                flights[count] = current->data->value;
                count++;
            }
            current = current->next;
        }

        //sort the flights based on the destination country using bubble sort algorithm
        for (int i = 0; i < count - 1; i++) 
        {
            for (int j = 0; j < count - i - 1; j++) 
            {
                if (flights[j].country_of_destination > flights[j + 1].country_of_destination)		//compare alphabetical order of country
                 {
                    Flight_Ticket temp = flights[j];			//swap in order
                    flights[j] = flights[j + 1];
                    flights[j + 1] = temp;
                }
            }
        }

        	//display the sorted flights
        for (int i = 0; i < count; i++) 
            cout << flights[i].toString2();
    }
}


int FlightHASHTABLE::next_prime(int cap)			//method to find the next largest prime number
{
	int nextPrime = cap;
    bool foundPrime = false;				
    while (!foundPrime) 			//increment number until prime value is found
    {
        nextPrime++;
        if (is_prime(nextPrime)) {
            foundPrime = true;
        }
    }
    return nextPrime;


}

bool FlightHASHTABLE::is_prime(int cap)
{
	if (cap <= 1) {			//if number is smaller or equivalent to one, its not a prime number
        return false;
    }
    for (int i = 2; i <= sqrt(cap); i++) 		//see modula for values until sqrt(number) and if modula of 0 is found, return false
    {
        if (cap % i == 0) 
        {
            return false;
        }
    }
    return true;
}


void FlightHASHTABLE::increase_size()
{
	int old_capacity = capacity;			//store old capacity for iteration
    capacity = next_prime(1.25 * this->capacity);			//increment capacity by next largest prime number

   
	MyList<HashNode>* new_table = new MyList<HashNode>[capacity];	 //create new hashtable

	//iterate through the original hash table, use the hashcode to copy them into the new hashtable
	for (int i = 0; i < old_capacity; i++) 
	{
		MyList<HashNode>* bucket = &buckets[i];		//access lists of original hash table
		Node<HashNode>* current = bucket->head;
		
		while(current != NULL)						//iterate through list
		{
			HashNode* node = current->data;					//access data of current node
			int hashcode = hashCode(node->getkey());		//get the new hashcode for the current node
			new_table[hashcode].addFront(node);				//insert into new hashtable
			current = current->next;
		}
	}
	delete[] buckets;			//delete original hashtable
	buckets = new_table;			//assign new hashtable 
}

bool operator==(const HashNode& node1, const HashNode& node2) 			//operator overload to compare two node values
{
    return (node1.getkey() == node2.getkey() && node1.getvalue() == node2.getvalue());
}

bool operator!=(const HashNode& node1, const HashNode& node2) 
{
    return !(node1 == node2);
}



