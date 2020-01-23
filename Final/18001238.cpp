#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <ctime>

/*******************************************************************************
	> flight class for store the all information about ONE flight
	> Using object array we stored all flight details
	> In flight class there are two linked list, one for store the seat details
    other one for store the number of free seats  with their class
	> sys class for all operations that related with flights
ALL Linked Lists and Objects Arrays Are Dynamically Allocated According to File!
*******************************************************************************/

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
		
		//return number of freeseat with their class in the filght
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
						freeSeatCount -> nextClass=NULL;
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
							newNode ->nextClass = NULL;
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
		//create seat list
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
		struct seat * getSeats()
		{
			return seats;
		}				
};

class sys
{
	private:
		int n,Gflag;
		flight * flights;
		int chose;
			
	public:
		
		sys()
		{
			Gflag=0;
			n=countFlight();
			init();
		}

		int mainMenu()
        {
            menu();//for dislapy the UI 
            cout << "\tEnter Your Choise >>> ";
            cin  >> chose;
            while(!(chose <=5 && chose >=1))
            {
                clear();
                menu();
            	cout << "\tInvalid Input ! Enter Your Choise Again >>> ";
                cin  >> chose;
            }
            return chose;
        }
        
        // clear the screen (only working for windows)
        void clear()
        {
            system("cls");
        }
        
        //count the numer of Flights in the file
		int countFlight() 
		{
			int count=0;
			string temp;
			ifstream database("Flights.txt");
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
		
		//reading file and create flight object array in main memory
		void init()
		{
			loardLogo();//lording logo
			
			flights = new flight[n];
			
			string tempStr;
			char * temp;
			
            int state=0;
            int flightNum=0;
            
            ifstream database("Flights.txt");
            while (getline (database,tempStr))
            {
            	
            	temp=new char[tempStr.size()+1];
            	strcpy(temp,tempStr.c_str());
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
			sleep(4);
			return;
		}
		
		
		void option1()
		{
			flight tmp;
			cout << endl<< endl;
			cout << "\t----------------------------------------------------------------------------------------------------------" << endl;
			cout << "\t|   Flight      | Departure             | Departure     | Arrival       | Number Of                      |" << endl;
			cout << "\t|   Number      | Date And Time         | Airport Code  | Airport Codet | Seats Free                     |" << endl;
			cout << "\t----------------------------------------------------------------------------------------------------------" << endl;
			struct seatCount * ptr;
			for (int i=0;i<n;i++)
			{
				tmp=flights[i];
				ptr=tmp.getFreeSeats();
				if(ptr!=NULL)
				{
					
					cout << "\t| " << tmp.getNumber() <<"  \t| "<< tmp.getDateTime() << " \t| " <<  tmp.getDeparture();
					cout <<	"\t| " << tmp.getArrival() << " \t|"<<setw(10)<<" Class :" ;
					while(ptr!=NULL)
					{
						cout << "  " << ptr->seatClass << ":" << ptr->count;
						ptr=ptr->nextClass;
					}
					cout << setfill(' ')<< " \t\t |" << endl;
			cout << "\t----------------------------------------------------------------------------------------------------------" << endl;
				}	
			}
			
		}
		flight option2()
		{
			string num;
			flight tmp;
			cout << "\t\t---------------------------------------------"<<endl;
			cout << "\t\t|    Search Flights                         |"<<endl;
			cout << "\t\t---------------------------------------------"<<endl;
			cout << "\t\tEnter Flight Number :";
			cin >> num ;
			clear();
			int flag=0,i;
			for (i=0;i<n;i++)//find the flight
			{
				tmp=flights[i];
				char * number=tmp.getNumber();
				if(!(strcmp(num.c_str(),number)))
				{
					flag=1;
					break;
				}		
			}
			if(flag)
			{
				Gflag=1;
				struct seat * tmpSeat=tmp.getSeats();
				struct seatCount * ptr;
				ptr=tmp.getFreeSeats();
				cout << "\t\t-------------------------------------------------"<<endl;
				cout << "\t\t| Flight Founded !                              |"<<endl;
				cout << "\t\t-------------------------------------------------"<<endl;
				cout << "\t\t|                                               |"<<endl;
				cout << "\t\t| Flight Number\t\t : "<<tmp.getNumber()<<"\t\t|"<<endl;
				cout << "\t\t| Flight Date Time\t : "<<tmp.getDateTime()<<"\t|"<<endl;
				cout << "\t\t| Arrival Airport Code\t : "<<tmp.getArrival()<<"\t\t|"<<endl;
				cout << "\t\t| Departure Airport Code : "<<tmp.getDeparture()<<"\t\t|"<<endl;
				cout << "\t\t| Number Of Seats Free\t : ";
				while(ptr!=NULL)
					{
						cout << "  " << ptr->seatClass << ":" << ptr->count;
						ptr=ptr->nextClass;
					}
				cout <<"\t\t|"<<endl;
				cout << "\t\t|                                               |"<<endl;
				cout << "\t\t|\tROW\tCLASS\t\tSEATS\t\t|"<<endl;
				cout << "\t\t|                                               |"<<endl;
				if(tmpSeat!=NULL)
				{
					while(tmpSeat->next!=NULL)
					{
						cout << "\t\t|\t"<<tmpSeat->rowNumber<<"\t"<<tmpSeat->seatClass<<"\t\t"<<tmpSeat->freeSeats<<"\t\t|"<<endl;
						tmpSeat=tmpSeat->next;
					}
				}
				else 
				{
				cout << "\t\t|       No Seats Avialable In This Flight       |"<<endl;
				}
				cout << "\t\t|                                               |"<<endl;
				cout << "\t\t-------------------------------------------------"<<endl;
			}
			else
			{
				cout << "\t\t----------------------------------------------"<<endl;
				cout << "\t\t| Searching for Flight Faild !               |"<<endl;
				cout << "\t\t----------------------------------------------"<<endl;
				cout << "\t\t|                                            |"<<endl;
				cout << "\t\t| There is no flight called '"<<num<<"'          |"<<endl;
				cout << "\t\t|                                            |"<<endl;
				cout << "\t\t----------------------------------------------"<<endl;
			}
			return tmp;
					
		}
		void option3()
		{
			string num;
			flight tmp;
			int numSeats;
			cout << "\t\t---------------------------------------------"<<endl;
			cout << "\t\t|    Search Flights  with Seats	         |"<<endl;
			cout << "\t\t---------------------------------------------"<<endl;
			cout << "\t\tEnter Flight Number :";
			cin >> num ;
			clear();
			int flag=0,i;
			for (i=0;i<n;i++)//find the flight
			{
				tmp=flights[i];
				char * number=tmp.getNumber();
				if(!(strcmp(num.c_str(),number)))
				{
					flag=1;
					break;
				}		
			}
			if(flag)
			{
				cout << "\t\t---------------------------------------------"<<endl;
				cout << "\t\t| "<<num<<" Flight Founded !                    |"<<endl;
				cout << "\t\t---------------------------------------------"<<endl;
				cout << "\t\tEnter Number of seats do you need : ";
				cin >>  numSeats;
				clear();
				struct seatCount * ptr;
				ptr=tmp.getFreeSeats();
				struct seat * tmpSeat=tmp.getSeats();
				int count=0;
				while(ptr!=NULL)
				{
					count=count+ptr->count;
					ptr=ptr->nextClass;
					
				}
				if(count>=numSeats)
				{
					cout << "\t\t-------------------------------------------------"<<endl;
					cout << "\t\t| Flight And Seat Founded !                     |"<<endl;
					cout << "\t\t-------------------------------------------------"<<endl;
					cout << "\t\t|                                               |"<<endl;
					cout << "\t\t| Flight Number\t\t : "<<tmp.getNumber()<<"\t\t|"<<endl;
					cout << "\t\t| Flight Date Time\t : "<<tmp.getDateTime()<<"\t|"<<endl;
					cout << "\t\t| Arrival Airport Code\t : "<<tmp.getArrival()<<"\t\t|"<<endl;
					cout << "\t\t| Departure Airport Code : "<<tmp.getDeparture()<<"\t\t|"<<endl;
					cout << "\t\t|                                               |"<<endl;
					cout << "\t\t|\tROW\tCLASS\t\tSEATS\t\t|"<<endl;
					cout << "\t\t|                                               |"<<endl;
					if(tmpSeat!=NULL)
					{
						while(tmpSeat->next!=NULL)
						{
							cout << "\t\t|\t"<<tmpSeat->rowNumber<<"\t"<<tmpSeat->seatClass<<"\t\t"<<tmpSeat->freeSeats<<"\t\t|"<<endl;
							tmpSeat=tmpSeat->next;
						}
					}
					else 
						cout << "\t\t|       No Seats Avialable In This Flight       |"<<endl;
					cout << "\t\t|                                               |"<<endl;
					cout << "\t\t-------------------------------------------------"<<endl;
				}
				else
				{
					cout << "\t\t--------------------------------------------------"<<endl;
					cout << "\t\t|   Searching for Seats : Not Available !        |"<<endl;
					cout << "\t\t--------------------------------------------------"<<endl;
					cout << "\t\t|                                                |"<<endl;
					cout << "\t\t|  There are not "<<numSeats<<"--Seats in "<<num<<" flight \t |"<<endl;
					cout << "\t\t|                                                |"<<endl;
					cout << "\t\t--------------------------------------------------"<<endl;
				}
			}
			else
			{
				cout << "\t\t----------------------------------------------"<<endl;
				cout << "\t\t| Searching for Flight Faild !               |"<<endl;
				cout << "\t\t----------------------------------------------"<<endl;
				cout << "\t\t|                                            |"<<endl;
				cout << "\t\t| There is no flight called '"<<num<<"'           |"<<endl;
				cout << "\t\t|                                            |"<<endl;
				cout << "\t\t----------------------------------------------"<<endl;
			}
		}
		void option4()
		{
			int rownum,index,len;
			char seat;
			flight tmp=option2();
			if(Gflag)
			{
				struct seat * tmpSeat=tmp.getSeats();
				struct seat * prvSeat=tmpSeat;
				cout <<endl<< "\t\tFor Book A Seat  Enter Row Number (1-60 ):";
				cin >> rownum;
				cout << "\t\tEnter Seat Position (A-F) :";
				cin >> seat;
				char * pch;
				int innerFlag=0,innerFlag2=0;
				if(tmpSeat!=NULL)
				{
					while(tmpSeat->next!=NULL)
					{
						if(tmpSeat->rowNumber==rownum)
						{
							innerFlag=1;
							char * list=tmpSeat->freeSeats;
							len=strlen(list);
							for (index=0;index<len;index++)
								if(list[index]==seat)
								{
									innerFlag2=1;
									break;
								}
							if(!innerFlag2)
							{
								cout << endl << "\t\tValid Row But Invalid Seat !! "<<endl;
							}
						  	else
							{
								if(len==1)
								{
									if(prvSeat==tmpSeat)
										*prvSeat=*tmpSeat->next;
									else
										prvSeat->next=tmpSeat->next;
									cout << endl <<"\t\tYour Seat BOOKED !!"<<endl;
								}
								else
								{
									for (int i = index; i < len -1 ; i++)
									    tmpSeat->freeSeats[i] = tmpSeat->freeSeats[i + 1];
									tmpSeat->freeSeats[strlen(tmpSeat->freeSeats)-1]='\0';
									cout << endl <<"\t\tYour Seat BOOKED !!"<<endl;	
								}
						  		
							}
						    	
						}
						prvSeat=tmpSeat;
						tmpSeat=tmpSeat->next;
					}
					if (innerFlag==0)
						cout << endl << "\t\tInvalid Row Number !! "<<endl;
				}
				else 
				{
				cout << "\t\t|       No Seats Avialable In This Flight       |"<<endl;
				}
			
			}
			
			
			
		}
		void option5()
		{
			exitLogo();
			ofstream file;
			file.open ("Flights.txt");
			flight tmp;
			struct seat * ptr;
			for (int i=0;i<n;i++)
			{
				tmp=flights[i];
				ptr=tmp.getSeats();
				file << tmp.getNumber() << endl << tmp.getDateTime() << endl <<  tmp.getDeparture() << endl << tmp.getArrival() <<endl ;
				while(ptr->next!=NULL)
				{
					file << ptr->rowNumber << "  "<< ptr->seatClass << " " << ptr->freeSeats << endl;
					ptr=ptr->next;
				}
				file << endl;
			}
			file.close();
			sleep(4);
			clear();
			
		}
		
		void exitLogo()
		{
			cout<<" "<< endl<<" "<<endl;
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                            System Exiting ...                                      |" << endl;
			cout<< "\t|                                        Wait for Saving Changes  !                                  |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
		}
		void menu()
		{
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                   <<<<<<<<<<<<  Welcome To Virgin Airline  >>>>>>>>>>>>                            |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                              1       Display Available Flights                                     |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                              2       View Flight                                                   |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                              3       Seat Availability                                             |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                              4       Seat booking                                                  |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                              5       Exit  From The System                                         |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
		}
		void loardLogo()
		{
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                       Virgin Airline                                               |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                            <<<<<<<<<< System Starting >>>>>>>>                                     |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                  Wait for Database Loading...                                      |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t|                                                                                                    |" << endl;
			cout<< "\t------------------------------------------------------------------------------------------------------" << endl;
		}
		//for loading time                                           / in implementation we not need this //
		//because in this prototype database loaading time is very short so we can't see the loading screen
		void sleep(float s){
		    clock_t sc = clock();
		    float sa = s * CLOCKS_PER_SEC;
		    while(clock() < sc+sa){
		        void();
		    }
		    return;
		}	
	
};

int main()
{
	
	sys system;
	int chose,x; 
	while(1)
	{
		system.clear();
		chose = system.mainMenu();
		switch (chose)
		{
			case 1:
				system.clear();
				system.option1();
				break;
			case 2:
				system.clear();
				system.option2();
				break;
			case 3:
				system.clear();
				system.option3();
				break;
			case 4:
				system.clear();
				system.option4();
				break;
			case 5:
				system.clear();
				system.option5();
				system.clear();
				exit(0);
				break;
		}
		if(chose == 1)
			cout << "\tEnter Any Number To Return MainMenu : ";
		else
			cout << "\t\tEnter Any Number To Return MainMenu : ";
		cin >> x;
	}
	return 0;
}
