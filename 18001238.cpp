#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class cliHandler
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
class flight
{
    private:
        struct seatDetails
        {
            int rowNumber;
            char Class;
            int seatCount;
            char * availableSeats;
        };

        struct flightDetails
        {
            char flightNumber [5];
            char dateTime [16];
            char departureAirport [20];
            char arrivalAirport [20];
            int rowCount;
            vector <struct seatDetails> rows;
        };
        
		vector <struct flightDetails> flights;

        void readFile()
        {
            string temp;
            int state=0;
            struct flightDetails node;
            ifstream MyReadFile("Flights.txt");
            while (getline (MyReadFile, temp))
            {
            	cout << temp << state << endl;
            	if(state==0)
            	{
            		node.flightNumber=temp;
            		node.rowCount=0;
				}
				else if(state==1)
				{
					node.dateTime=temp;
				}
				else if(state==2)
				{
					node.departureAirport=temp;
				}
				else if(state==3)
				{
					node.arrivalAirport=temp;
				}
				else if(state>3 && temp!="")
				{
					node.rowCount ++ ;
				}
            	state ++ ;
            	if(temp == "")
            		state=0;
			}
        }
    public:
        flight ()
        {
            readFile();
        }
};
int main()
{
    // cliHandler display;
    // int chose=display.mainMenu();
    // if (chose == 5)
    // {
    //     display.clear();
    // }
    flight flights;
   return 0; 
}
