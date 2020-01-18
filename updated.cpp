#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
using namespace std;

struct seatCount
{
    char seatClass;
    int count;
    struct seatCount * nextClass;
};
struct seat
{
    int rowNumber;
    char seatClass;
    char * freeSeats;
    struct seat * next;
};


class flight
{
	private:
		
		char flightNumber[6];
		char departureAirport[20];
        char dateTime[17];
        char arrivalAirport[20]; 
        struct seat * seats;
        
    	
		struct seatCount * freeSeatCount;
		
	public:
		flight()
		{
			seats=NULL;
			freeSeatCount=NULL;
		}
		/* functionality methods */
		struct seatCount * getFreeSeats()
		{
			
			struct seat * tmpSeat=seats;
			struct seatCount * tmpCount = freeSeatCount;
			if(tmpSeat!=NULL)
			{
				
				while(tmpSeat->next!=NULL)
				{
					if(freeSeatCount==NULL)
					{
						freeSeatCount = new struct seatCount;
						freeSeatCount -> seatClass = tmpSeat -> seatClass;
						freeSeatCount -> count = strlen(tmpSeat -> freeSeats);
					}
					else
					{
						int flag=0;
						tmpCount = freeSeatCount;
						while(tmpCount !=NULL)
						{
							if(tmpSeat->seatClass == tmpCount->seatClass)
							{
								flag=1;
								(tmpCount->count)+=strlen(tmpSeat -> freeSeats);
							}
							tmpCount=tmpCount->nextClass;
						}
						if(flag==0)
						{
							struct seatCount * newNode = new struct seatCount;
							newNode -> seatClass = tmpSeat -> seatClass;
							newNode -> count = strlen(tmpSeat -> freeSeats);
							tmpCount = freeSeatCount;
							while (tmpCount->nextClass!=NULL)
								tmpCount=tmpCount->nextClass;
							tmpCount->nextClass = newNode;
						}
					}
					tmpSeat=tmpSeat->next;
				}
			}
			return freeSeatCount;
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
			int partNumber=1;
			struct seat * tmp = new struct seat;
			tmp -> next = NULL;
			while (ptr != NULL)
			{
				
				if(partNumber==1)
				{
					tmp -> rowNumber = atoi(ptr);
				}
				else if (partNumber==2)
				{
					strcpy(&(tmp -> seatClass),ptr);
				}
				else
				{
					int len=strlen(ptr);
					tmp -> freeSeats = new char[len];
					strcpy(tmp -> freeSeats,ptr);
					partNumber=0;
				}
				ptr = strtok(NULL," ");
				partNumber++;
			}
			struct seat * trvsTmp = seats;
			if(trvsTmp==NULL)
			{
				seats = tmp;
			}
			else
			{
				while(trvsTmp->next != NULL)
				{
					trvsTmp = trvsTmp -> next;
				}
				trvsTmp -> next = tmp;
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

class sys
{
	private:
		int n;
		flight * flights;
		int chose;
			
	public:
		
		sys(char file[]="Flights.txt")
		{
			n=countFlight(file);
			init(file);
		}
		
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
        
        
		int countFlight(char file[])
		{
			int count=0;
			string temp;
			ifstream database(file);
            while (getline (database, temp))
            {
            	if(temp == "")
            	{
            		count ++ ;
				}	
        	}
        	database.close();
        	return count;
		}
		
		
		void init(char file[])
		{
			flights = new flight[n];
			
			string tempStr;
			char * temp;
			
            int state=0;
            int flightNum=0;
            
            ifstream database(file);
            while (getline (database,tempStr))
            {
            	
            	temp=new char[tempStr.size()+1];
            	strcpy(temp,tempStr.c_str());
            	//cout << temp << endl;
            	if(state==0)
            	{
            		flights[flightNum].setNumber(temp);
				}
				else if(state==1)
				{
					flights[flightNum].setDateTime(temp);
				}
				else if(state==2)
				{
					flights[flightNum].setDeparture(temp);
				}
				else if(state==3)
				{
					flights[flightNum].setArrival(temp);
				}
				else if(state>3 && temp!="")
				{
					flights[flightNum].setSeats(temp);
				}
            	state ++ ;
            	if(tempStr == "")
            	{
            		state=0;
            		flightNum++;
				}
            	
			}
			return;
		}
		
		
		void option1()
		{
			flight tmp;
			line();
			cout << "|\t Flight Number\t |\t Departure Date And Time |\t Departure Airport Code\t |\t Arrival Airport Codet\t|\tNumber Of Seats Free\t|" << endl;
			line();
			struct seatCount * ptr;
			for (int i=0;i<n;i++)
			{
				tmp=flights[i];
				ptr=tmp.getFreeSeats();
				if(ptr!=NULL)
				{
					
					cout << "|\t\t " << tmp.getNumber() <<"\t |\t "<< tmp.getDateTime() << "\t |\t " <<  tmp.getDeparture();
					cout <<	"\t \t |\t " << tmp.getArrival() << "\t\t|\t Class :" ;
					while(ptr!=NULL)
					{
						cout << "  " << ptr->seatClass << ":" << ptr->count;
						ptr=ptr->nextClass;
					}
					cout << "\t"<< "|" << endl;
					line();
					
				}	
			}
			
		}
		void line()
		{
			
			for(int i=0;i<145;i++)
					cout << "-";
			cout<< endl;
		}	
	
};

int main()
{
	sys system;
	
	
	int chose = system.mainMenu();
	switch (chose)
	{
		case 1:
			system.clear();
			break;
		case 2:
			break;
		case 3:
			system.clear();
			system.option1();
			break;
	}
	return 0;
}
