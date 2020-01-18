#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <map>
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
        
        struct flightDetails
        {
            char flightNumber[6];
            char dateTime[16];
            char departureAirport[20];
            char arrivalAirport[20];
            int rowCount;
    		char seats[6][60];
        };
        
		vector <struct flightDetails> flights;
		void split(char str[]) 
		{ 
		    char *token = strtok(str, " ")
			int count=0;
			map <char,int> classifiedSeats;
			char ch;
			int num;
		    while (token != NULL) 
		    { 
		        
				count++; 
				if (count==2)
				{
					classifiedSeats.find(token)
				}
		        token = strtok(NULL, " "); 
		    } 
		} 
        void readFile()
        {
            string temp;
            int state=0;
            struct flightDetails tempFlight;
            ifstream MyReadFile("Flights.txt");
            while (getline (MyReadFile, tempStr))
            {
            	cout << temp << state << endl;
            	if(state==0)
            	{
            		tempFlight.flightNumber=tempStr;
            		tempFlight.rowCount=0;
				}
				else if(state==1)
				{
					tempFlight.dateTime=tempStr;
				}
				else if(state==2)
				{
					tempFlight.departureAirport=tempStr;
				}
				else if(state==3)
				{
					tempFlight.arrivalAirport=tempStr;
				}
				else if(state>3 && temp!="")
				{
					tempFlight.rows.push_back(tempStr)
					tempFlight.rowCount ++ ;
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
