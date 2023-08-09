#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
#include <string>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
			Flight_Ticket() 				// default constructor
		{
			companyName = "";
			flightNumber = 0;
			country_of_origin = "";
			country_of_destination = "";
			stopOver = "";
			price = "";
			time_of_departure = "";
			time_of_arrival = "";
			date = "";
		}

        bool operator==(const Flight_Ticket& other) 		//operator overload to compare two flight ticket values
        {
    		return companyName == other.companyName &&
           flightNumber == other.flightNumber &&
           country_of_origin == other.country_of_origin &&
           country_of_destination == other.country_of_destination &&
           stopOver == other.stopOver &&
           price == other.price &&
           time_of_departure == other.time_of_departure &&
           time_of_arrival == other.time_of_arrival &&
           date == other.date;
		}

			bool operator!=(const Flight_Ticket other) 
			{
   			 return !(*this == other);
			}

		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		// add additional methods as needed

		string toString() const {
			    string str = "Company Name: " + companyName + "\n";						//method to return a string containing variables
			    str += "Flight Number: " + to_string(flightNumber) + "\n";
			    str += "Country of Origin: " + country_of_origin + "\n";
			    str += "Country of Destination: " + country_of_destination + "\n";
			    str += "Stop Over: " + stopOver + "\n";
			    str += "Price: " + price + "\n";
			    str += "Time of Departure: " + time_of_departure + "\n";
			    str += "Time of Arrival: " + time_of_arrival + "\n";
			    str += "Date: " + date + "\n";
			    return str;
			}
		string toString2() const{									//method to return a string containing variables on same line
			string str = companyName +","+ to_string(flightNumber) + ","+ country_of_origin + ","+ country_of_destination+","+ stopOver+","+ price+","+ time_of_departure+","+ time_of_arrival+","+ date+"\n";
			return str;

		}

		friend class FlightHASHTABLE;
};

#endif
