
#include<iostream>
#include<cstdlib>
#include<sstream>
#include <regex>

#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with any necessary method definitions

//==========================================================
int main(void)
{
	int hashmethod;
	cout << "Choose Hash Method (1.cycle shift 2. polynomial 3. summation) : ";
	cin >> hashmethod;
	cin.clear();
	cin.ignore();
	cout <<endl;

	FlightHASHTABLE myFlightHASHTABLE(hashmethod);

	while(true)
	{
	listCommands();
	string user_input;
	string command;
	string parameter;
	string parameter2;
	cout<<">";
	getline(cin,user_input);
	stringstream sstr(user_input);
	getline(sstr,command,' '); 
	getline(sstr,parameter,',');
	getline(sstr,parameter2);


	if(command == "import")
	{
		cout << myFlightHASHTABLE.importCSV(parameter) <<endl;
	}

	else if(command == "export")
	{
		cout << myFlightHASHTABLE.exportCSV(parameter) <<endl;
	}

	else if(command == "count_collisions")
	{
		cout << "Total Number of collisions is "<< myFlightHASHTABLE.count_collisions();
	}
	else if(command == "add")
	{
		string company_name, country, destination, stopover, price, departure, arrival, date;    //check valid inputs to add
		int flight;
		cout << endl << "Please enter the details of the flight ticket: " <<endl;

		cout << "Company Name : ";
		regex alpha_regex("^[a-zA-Z ]+$");				//check if input is lower case or upper case alphabets
		while (true) {
		    getline(cin, company_name);
		    if (regex_match(company_name, alpha_regex)) {
		        break; 										//break if input is valid
		    } else {		
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Flight Number : ";
		regex numbers("[0-9]+");				//check if input is numbers
		while (true) {
		    string input;
		    getline(cin, input);
		    if (regex_match(input, numbers)) {
		        flight = stoi(input);
		        break; 
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Country of Origin : ";
		regex alpha_regex2("^[a-zA-Z ]+$");		//check if input is lower case or upper case alphabets
		while (true) {
		    getline(cin, country);
		    if (regex_match(country, alpha_regex2)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Country of Destination : ";		//check if input is lower case or upper case alphabets
		while (true) {
		    getline(cin, destination);
		    if (regex_match(destination, alpha_regex2)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Stopover : ";
		regex numbers2("[0-9]+");			//check if input is numbers
		while (true) {
		    getline(cin, stopover);
		    if (regex_match(stopover, numbers2)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Price : ";
		while (true) {						//check if input is numbers
		    getline(cin, price);
		    if (regex_match(price, numbers2)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		regex time("^(0?[0-9]|1[0-9]|2[0-3])(:[0-5][0-9])?(:[0-5][0-9])?$");	//check for valid time input with optional second colon
		cout << "Time of Departure : ";
		while (true) {
		    getline(cin, departure);
		    if (regex_match(departure, time)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		cout << "Time of Arrival: ";				//check for valid time input with optional second colon
		while (true) {
		    getline(cin, arrival);
		    if (regex_match(arrival, time)) {
		        break;
		    } else {
		        cout << "Invalid input, please enter again: ";
		    }
		}
		cout << endl;

		regex date_regex("^(0?[1-9]|[1-2][0-9]|3[0-1])-([a-zA-Z]+)$");		//check for valid date input 
		cout << "Date : ";
		while (true) {
		    getline(cin, date);
		    if (regex_match(date, date_regex)) {
		        break;
		    } else{
		    	cout << "Invalid input, please enter again: ";
		    }
		}

		cin.clear();
		cin.ignore();

		Flight_Ticket* new_flightticket = new Flight_Ticket(company_name, flight, country, destination, stopover, price, departure, arrival, date);	//create new flightticket object	
		
		if(myFlightHASHTABLE.add(new_flightticket)==1)			//print message if add was successful
			cout<<"Flight Ticket has been successfully added!";
		else
			cout<<"Failed to add";				//fail to add if all values are the same
	}

	else if(command == "delete")
	{
		myFlightHASHTABLE.removeRecord(parameter, stoi(parameter2));
	}
	else if(command == "find")
	{
		myFlightHASHTABLE.find(parameter, stoi(parameter2));
	}
	else if(command == "allinday")
	{
		myFlightHASHTABLE.allinday(parameter);
	}
	else if(command == "printASC")
	{
		myFlightHASHTABLE.printASC(parameter,stoi(parameter2));
	}
	else if(command =="exit")
	{
		break;
	}
	else
	{
		cout << "Invalid Command!" <<endl;
	}

	}

	return 0;
}
