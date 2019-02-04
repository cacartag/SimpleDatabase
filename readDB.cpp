#include <iostream>
#include <fstream>
using namespace std;

const int RECORD_SIZE = 71;
const int NUM_RECORDS = 4360;
const string FILENAME = "input.txt";

/*Get record number n-th (from 1 to NUM_RECORDS) */
bool GetRecord(ifstream &Din, const int RecordNum, 
               string &Id, int &Experience, string &Married, float &Wage, string &Industry)
{
bool Success = true;
string line;

   if ((RecordNum >= 1) && (RecordNum <= NUM_RECORDS))
   {
      Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
      Din >> Id >> Experience >> Married >> Wage >> Industry;
   }
   else
      Success = false;

   return Success;
}

/*Binary Search record id */
bool binarySearch (ifstream &Din, const string Id, 
                   int &Experience, string &Married, float &Wage, string &Industry)
{
   int Low = 0;
   int High = NUM_RECORDS;
   int Middle;
   string MiddleId;

   bool Found = false;
   while (!Found && (High >= Low))
   {
      Middle = (Low + High) / 2;
      Din.seekg(Middle * RECORD_SIZE, ios::beg);
      Din >> MiddleId >> Experience >> Married >> Wage >> Industry;  

      if (MiddleId == Id)
         Found = true;
      else if (MiddleId < Id)
         Low = Middle + 1;
      else 
         High = Middle -1;
   }

   return Found;
}

int main() 
{
ifstream Din(FILENAME.c_str());
string Id = "ID";
int Experience = -1;
string Married = "UNKNOWN";
float Wage = -1.0;
string Industry = "INDUSTRY";

   if (GetRecord(Din, 3, Id, Experience, Married, Wage, Industry))
      cout << "GetRecord(3): \n" << Id << ", " << Experience << ", " << Married << ", " 
           << Wage << ", " << Industry << "\n\n";
   
   if (GetRecord(Din, 2, Id, Experience, Married, Wage, Industry))
      cout << "GetRecord(2): \n" << Id << ", " << Experience << ", " << Married << ", " 
           << Wage << ", " << Industry << "\n\n";
   
   if (GetRecord(Din, 99999, Id, Experience, Married, Wage, Industry))
      cout << "GetRecord(99999): \n" << Id << ", " << Experience << ", " << Married << ", " 
           << Wage << ", " << Industry << "\n\n";
   else
      cout << "Record 99999 not found.\n\n";
   
   Experience = -1;
   Married = "UNKNOWN";
   Wage = -1.0;
   Industry = "INDUSTRY";
   if (binarySearch(Din, "00175", Experience, Married, Wage, Industry))
   {
      cout << "binarySearch(00175): " << Experience << ", " << Married << ", " 
                                      << Wage << ", " << Industry << "\n\n";
   }
   else
      cout << "Record 00165 not found.\n\n";

   Experience = -1;
   Married = "UNKNOWN";
   Wage = -1.0;
   Industry = "INDUSTRY";
   if (binarySearch(Din, "99999", Experience, Married, Wage, Industry))
   {
      cout << "binarySearch(99999): " << Experience << ", " << Married << ", " 
                                      << Wage << ", " << Industry << "\n\n";
   }
   else
      cout << "Record 99999 not found.\n\n";

   Din.close();   //close the file when done
}
