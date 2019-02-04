#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int RECORD_SIZE = 71;
const int NUM_RECORDS = 4360;
const string FILENAME = "input.txt";
const int IDSIZE = 6;
const int EXPERIENCESIZE = 11;
const int MARRIEDSIZE = 8;
const int WAGESIZE = 13;
const int INDUSTRYSIZE = 32;

struct Record
{
	string id;
	string experience;
	string married;
	string wage;
	string industry;
};

/*Get record number n-th (from 1 to NUM_RECORDS) */
bool GetRecord(ifstream &Din, const int RecordNum, string &Id, int &Experience, string &Married, float &Wage, string &Industry)
{
	bool Success = true;
	
	if ((RecordNum >= 1) && (RecordNum <= NUM_RECORDS))
	{
		string tempExperience = "";
		Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
		Din >> Id >> tempExperience >> Married >> Wage >> Industry;
		
		Experience = atoi(tempExperience.c_str());
		
		
		
		if(tempExperience == "null")
		{
			Success = false;
		}
		
		cout << "value of tempExperience.compare(null) is " << tempExperience.compare("null") << endl;
	}
	else
		Success = false;

	return Success;
}

/*Binary Search record id */
bool binarySearch (ifstream &Din, const string Id,string &MiddleId, int &Experience, string &Married, float &Wage, string &Industry,int &location)
{
	int Low = 0;
	int High = NUM_RECORDS;
	int Middle;
	string tempExperience = "";
	
	bool Found = false;
	while (!Found && (High >= Low))
	{

		Middle = (Low + High) / 2;
	
		Din.seekg(Middle * RECORD_SIZE, ios::beg);
		Din >> MiddleId >> tempExperience >> Married >> Wage >> Industry;  

		Experience = atoi(tempExperience.c_str());

		ofstream Dout("tempt.txt");
		Dout << tempExperience << endl;
		Dout << "null" << endl;
		
		if (MiddleId == Id)
			Found = true;
		else if (MiddleId < Id)
			Low = Middle + 1;
		else 
			High = Middle -1;


	}
	if(tempExperience ==  "null")
	{
		Found = false;
	}
	
	location = Middle * RECORD_SIZE;

	return Found;
}

//Pad A column value with spaces to have the right size
void PadInput(string &columnValue, const int rightLength, int column,bool standard)
{
	if(column != 0 && standard == true)
	{
		for(int x = 0; columnValue.length() < rightLength; x++)
		{
			columnValue.append(" ");
		}
		

	}else if(column != 0 && standard == false)
	{
		for(int x = 0; columnValue.length() < rightLength - 1; x++)
		{
			columnValue.append(" ");
		}
		
		if(standard == false)
		{
			columnValue.append("\n");
		}
		
	}
	else
	{
		string temp = "";
		
		for(int x = 0; (columnValue.length() + x) < (rightLength - 1); x++)
		{
			temp.append("0");
		}
		
		if(standard == true)
			columnValue.append(" ");
		
		temp.append(columnValue);
		columnValue = temp;
	}
}

//Checks to see if the length of the column is larger than it should be
//if its not it then pads the column value
bool CheckLength(string &columnValue,int column)
{
	bool valid = true;
	if(column == 1 && !(columnValue.length() <= EXPERIENCESIZE))
	{

		valid = false;
	}else if(column == 1){
		PadInput(columnValue, EXPERIENCESIZE, column,true);
	}
	
	if(column == 2 && !(columnValue.length() <= MARRIEDSIZE))
	{
		valid = false;
	}else if(column == 2){
		PadInput(columnValue, MARRIEDSIZE, column,true);
	}
	
	if(column == 3 && !(columnValue.length() <= WAGESIZE))
	{
		valid = false;
	}else if(column == 3){
		PadInput(columnValue, WAGESIZE, column,true);	
	}
	
	if(column == 4 && !(columnValue.length() <= INDUSTRYSIZE))
	{
		valid = false;
	}else if(column == 4){
		PadInput(columnValue, INDUSTRYSIZE, column, true);
	}
	
	return valid;
}

//Check if the file that you tried to open exists
bool checkIfFileExists(string filename)
{
	bool valid = false;
	
	ifstream tempDin(filename.c_str());
	if(tempDin.good())
	{
		valid = true;
	}
	
	return valid;
}

//Creates a new record for the database, puts it in a temp file
bool CreateRecord()
{
	bool completed;
	Record newRecord;
	
	ofstream tempDout;
	
	if(checkIfFileExists("temp.txt"))
	{
		tempDout.open("temp.txt", ios::app);
	}else{
		tempDout.open("temp.txt", ios::out);
	}
	
	
	newRecord.id = to_string(NUM_RECORDS + 1);
	
	PadInput(newRecord.id, IDSIZE, 0, true);
	
	cout << "What is the experience Value? " << endl;
	cin >> newRecord.experience;
	while(!CheckLength(newRecord.experience,1))
	{
		cout << "Experience value is too long" << endl;
		cout << "What is the experience value? " << endl;
		cin >> newRecord.experience;
	}
	
	cout << "What is the married value? " << endl;
	cin >> newRecord.married;
	
	while(!CheckLength(newRecord.married,2))
	{
		cout << "Married value is too long" << endl;
		cout << "What is the married value? " << endl;
		cin >> newRecord.married;
	}
	
	cout << "What is the wage value? " << endl;
	cin >> newRecord.wage;
	
	while(!CheckLength(newRecord.wage,3))
	{
		cout << "Wage Value is too long " << endl;
		cout << "What is the wage value " << endl;
		cin >> newRecord.wage;
	}
	
	cout << "What is the industry value? " << endl;
	cin >> newRecord.industry;
	
	while(!CheckLength(newRecord.industry,4))
	{
		cout << "Industry value is too long " << endl;
		cout << "What is the industry value " << endl;
		cin >> newRecord.industry;
	}
	
	tempDout << newRecord.id << newRecord.experience << newRecord.married 
			<< newRecord.wage << newRecord.industry << endl;
	
	if(tempDout.bad())
	{
		completed = false;
	}
	
	return completed;
}

//Gets the first line in a file where the column headers should be
void GetHeader(ifstream &Din,string &Header,int &lengthOfHeader)
{
	Din.seekg(0,ios::beg);
	Din.ignore(numeric_limits<streamsize>::max(), '\n');

	lengthOfHeader = (int)Din.tellg();
	char *firstLine= new char[lengthOfHeader];

	Din.seekg(0,ios::beg);
	Din.getline(firstLine,lengthOfHeader);
	
	Header.assign(firstLine);
	lengthOfHeader = Header.length();
}


//this is what I was working on as of 8/31/2016 at 8:06AM
bool ModifyRecord(ifstream &Din, string filename, string Header)
{	
	bool completed = true;
	string recordToModify = "";
	int columnToModify = 0;
	
	string Id = "";
	int Experience = -1;
	string Married = "";
	float Wage = -1.0;
	string Industry = "";
	string newColumnValue = "";
	
	cout << "What Record do you want to Modify?" << endl;
	cin >> recordToModify;
	
	while(!GetRecord( Din, stoi(recordToModify), Id, Experience, Married, Wage, Industry))
	{
		cout << "That Record does not exist, What Record do you want to Modify?" << endl;
		cin >> recordToModify;
	}

	string stringExperience = to_string(Experience);
	string stringWage = to_string(Wage);
	
	PadInput(Id, IDSIZE, 0,true);
	PadInput(stringExperience, EXPERIENCESIZE, 1,true);
	PadInput(Married, MARRIEDSIZE, 2,true);
	PadInput(stringWage, WAGESIZE, 3,true);
	PadInput(Industry, INDUSTRYSIZE, 4,true);	
	
	cout << endl;
	cout << Header << endl;
	cout << Id << stringExperience << Married << stringWage << Industry << endl;
	cout << endl;
	
	cout << "What column do you want to replace: \nexperience (1) \nmarried (2) \nwage (3) \nindustry (4)\n" << endl;
	cin >> columnToModify;
	
	while(columnToModify > 4 || columnToModify < 1)
	{
		cout << "Invalid input, What column do you want to replace: \nexperience (1) \nmarried (2) \nwage (3) \nindustry (4)\n" << endl;
		cin >> columnToModify;	
	}
	
	cout << "What Value do you want to insert?" << endl;
	cin >> newColumnValue;
	
	while(!CheckLength(newColumnValue,columnToModify))
	{
		cout << "That value is too long, What Value do you want to insert?" << endl;
		cin >> newColumnValue;
	}
	
	int displacement = 0;
	if(columnToModify == 1)
	{
		displacement = IDSIZE;
	}else if(columnToModify == 2){
		displacement = IDSIZE + EXPERIENCESIZE;
	}else if(columnToModify == 3){
		displacement = IDSIZE + EXPERIENCESIZE + MARRIEDSIZE;
	}else if(columnToModify == 4){
		displacement = IDSIZE + EXPERIENCESIZE + MARRIEDSIZE + WAGESIZE;
	}
	
	ofstream Dout(filename,ios::in|ios::out|ios::ate);
	Dout.seekp((stoi(recordToModify) * RECORD_SIZE)+ displacement,ios::beg);
	Dout.write(newColumnValue.c_str(), newColumnValue.length());

	if(Dout.bad())
	{
		completed = false;
	}
	
	return completed;
}

bool DeleteRecord(ifstream &Din,string filename)
{
	bool success = false;
	int RecordToDelete = 0;
	string ID = "";
	int Experience = 0;
	string Married = "";
	float Wage = 0.0;
	string Industry = "";
	int location = 0;
	
	cout << "What is the ID number of the record to be deleted? " << endl;
	cin >> RecordToDelete;

	string SID = to_string(RecordToDelete);
	PadInput(SID,IDSIZE,0,false);
	
	if(binarySearch(Din,SID,ID,Experience,Married,Wage,Industry,location))
	{
		string temp = "null";
		PadInput(temp,65,15,false);
		Din.close();
		ofstream Dout(filename,ios::in|ios::out|ios::ate);
		Dout.seekp(location + 6,ios::beg);
		Dout.write(temp.c_str(), temp.length());
		Dout.close();
		Din.open(filename);
		
		success = true;
	}
	
	return success;
}

int main()
{
	bool Active = true;
	int operation = 0;
	string filename;
	string line;
	string newDatabaseName;
	int createOrEditOption = 0;
	
	
	int numberOfRecordsCreated = 0;
	int recordToRetrieve = 0;
	string columnForMod = "";
	string modValue = "";
	
	ifstream Din;
	
	/*ifstream tempDin("input.txt");
	tempDin.seekg(0,tempDin.end);*/
	
	while(Active)
	{
		bool sameDatabase = true;
		
		
		cout << "What would you like to do: \nCreate New Database (1)\nOpen Existing Database (2) \nQuit (3)" << endl;
		cin >> createOrEditOption;
		cout << endl;
		
		while(createOrEditOption > 3 || createOrEditOption < 1)
		{
			cout << "That's an Invalid Option, What would you like to do: \nCreate New Database (1)\nOpen Existing Database (2) \nQuit (3)" << endl;
			cin >> createOrEditOption;
			cout << endl;
		}
		
		if(createOrEditOption == 1)
		{
			cout << "What is the new Database name?" << endl;
			cin >> newDatabaseName;
			cout << endl;
	
			ofstream tempDout(newDatabaseName);
			tempDout << "id    experience married wage         industry                        " << endl;
			
			if(!tempDout.bad())
			{
				cout << "Database was created successfully " << endl;
			}else{
				cout << "Database was not created" << endl;
			}
			cout << endl;
				
			tempDout.close();
			operation = 0;
		}else if(createOrEditOption == 3){
			Active = false;
		}
		else{
			cout << "What is the name of the file? " << endl;
			cin >> filename;
			
			Din.open(filename.c_str());
			
			while(!Din.good())
			{
				cout << "That file does not exist, Try Again" << endl;
				cin >> filename;
				Din.open(filename.c_str());
	
			}
			
			string Header;
			int lengthOfHeader = 0;
		
			GetHeader(Din, Header, lengthOfHeader);
			
			cout << "What operation would you like to execute? \nCreate Record (1)\nSearch File (2) \nModify Record (3)\nDelete a Record (4)\nClose File (6) "<< endl;
			cin >> operation;
			cout << endl;
			
			while(sameDatabase)
			{
				if(operation < 0 || operation > 6)
				{
					operation = 5;
				}
	
				switch (operation)
				{
					case 0:
						//Menu
						cout << "What operation would you like to execute? \nCreate Record (1)\nSearch File (2) \nModify Record (3) \nDelete a Record(4)\nClose File (6)" << endl;
						cin >> operation;
						cout << endl;
					break;
					
					case 1:
						if(CreateRecord())
						{
							//Create Record
							
							cout << "Record was created" << endl;
							cout << endl;
							
							numberOfRecordsCreated++;
							if(numberOfRecordsCreated == 3)
							{
								system("cat input.txt temp.txt | sort > systemtemp.txt");
								system("cat systemtemp.txt > input.txt");
								system("rm systemtemp.txt");
								system("rm temp.txt");
							}
						}else{
							cout << "Record was not created" << endl;
							cout << endl;
						}
						operation = 0;
					break;
					
					case 2:
					{
						//Search Record
						int location = 0;
						string Id = "";
						int Experience = -1;
						string Married = "";
						float Wage = 1.0;
						string Industry = "";
						string idValueForSearch = "";
						
						cout << "What is the ID value?" << endl;
						cin >> idValueForSearch;
						
						PadInput(idValueForSearch,IDSIZE,0,false);
						
						if(binarySearch(Din, idValueForSearch,Id, Experience, Married, Wage, Industry,location))
						{
							string experience = to_string(Experience);
							string wage = to_string(Wage);
							
							//replace this later with first line of file
							cout << Header << endl;
							PadInput(Id, IDSIZE, 0,true);
							PadInput(experience, EXPERIENCESIZE, 1,true);
							PadInput(Married, MARRIEDSIZE, 2,true);
							PadInput(wage, WAGESIZE, 3,true);
							PadInput(Industry, INDUSTRYSIZE, 4,true);
							cout << Id << experience << Married << wage << Industry << endl;
						}else{
							cout << "Record was not found" << endl;
						}	
						operation = 0;
					}
					break;
					
					case 3:
					{
						//Modify Record
						if(ModifyRecord(Din, filename,Header))
						{
							cout << "The record has been modified " << endl;
							cout << endl;
						}else{
							cout << "The record was not modified " << endl;
							cout << endl;
						}
						operation = 0;
					}
					break;
					
					case 4:
					{
						//Delete Record
						if(DeleteRecord(Din, filename))
						{
							cout << "The record has been deleted " << endl;
							cout << endl;
						}else{
							cout << "The record was not deleted " <<endl;
							cout << endl;
						}
						operation = 0;
					}
					break;
					
					case 5:
					{
						cout << "That's not a valid option " << endl;
						cout << endl;
						operation = 0;
					}
					break;
					
					case 6:
						//Close Database
						Din.close();
						cout << "Would you like to open another file? \nNo (0) \nYes(1) " << endl;
						cin >> Active;
						if(numberOfRecordsCreated > 0)
						{
							system("cat input.txt temp.txt | sort > systemtemp.txt");
							system("cat systemtemp.txt > input.txt");
							system("rm systemtemp.txt");
							system("rm temp.txt");
						}
						
						numberOfRecordsCreated = 0;
						sameDatabase = false;
					break;
				}
			}
		}
	}
}























