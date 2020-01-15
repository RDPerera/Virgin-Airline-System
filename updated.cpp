#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h> 

using namespace std;

class cli
{
    private :
        int chose;
    public:
        int mainMenu()
        {
            cout << "Welcome To Virgin Airline  " << endl ;
            cout << "=========================  " << endl ;
            cout << "1 Display available flights" << endl ;
            cout << "2 View flight              " << endl ;
            cout << "3 Seat availability        " << endl ;
            cout << "4 Seat booking             " << endl ;
            cout << "5 Exit                     " << endl ;
            cout << "=========================  " << endl ;
            cout << "Enter Your Choise >>> ";
            cin  >> chose;
            while(chose >5 || chose <1)
            {
                
                cout << "=========================  " << endl ;
                cout << chose << " is Invalid Input " << endl ;
                cout << "=========================  " << endl ;
                cout << "Enter Your Choise Again >>> ";
                cin  >> chose;
            }
            return chose;
        }
        void clear()
        {
            system("cls");
        }
};

class sys
{
	private:
		int n;
		
		
	public:
		void print()
		{
			cout << "Hello world !";	
		}
		
};
class flight
{
	private:
		struct seat
        {
        	int rowNumber;
        	char seatClass;
        	char * seats;
        	struct seat * next;
		};
		char flightNumber[6];
		char departureAirport[20];
        char dateTime[17];
        char arrivalAirport[20]; 
        struct seat * seats;
        
    	struct seatCount
        {
        	char seatClass;
        	int count;
		};
		struct seatCount * freeSeats;
	public:

		/* functionality methods */
		struct seatCount * getFreeSeats()
		{
			return freeSeats;
		}
		
		/* setter		methods */
		void setNumber(char * num)
		{
			strcpy(flightNumber,num);
		}
			
		void setDateTime(char * Date_Time)
		{
			strcpy(dateTime,Date_Time);
		}
			
		void setDeparture(char * depAirport)
		{
			strcpy(departureAirport,depAirport);
		}
			
		void setArrival(char * arriAirport)
		{
			strcpy(arrivalAirport,arriAirport);
		}
		
		void setSeats(char * rule)
		{
			char *ptr = strtok(rule," ");
			while (ptr != NULL)
			{
				cout << ptr << " ";
				ptr = strtok(NULL," ");
			}
		}
	
	
		/* getter		methodes */	
		char * getNumber()
		{
			return flightNumber;
		}
			
		char * getDateTime()
		{
			return dateTime;
		}
			
		char * getDeparture()
		{
			return departureAirport;
		}
			
		char * getArrival()
		{
			return arrivalAirport;
		}				
};

int main()
{
	cli display;
	sys System;
	
	int chose = display.mainMenu();
	switch (chose)
	{
		case 1:
			display.clear();
			System.print();
			break;
		case 2:
			flight tmp;
			tmp.setNumber("VA301");
			tmp.setDateTime("20/02/2020 10:20");
			tmp.setArrival("COLOMBO");
			tmp.setDeparture("PAN");
			cout << tmp.getNumber() << endl;
			cout << tmp.getArrival() << endl;
			cout << tmp.getDateTime() << endl;
			cout << tmp.getArrival() << endl;
	}
	return 0;
}
