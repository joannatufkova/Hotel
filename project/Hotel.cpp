#include"Hotel.h"
#include<fstream>
#include<cstring>
using namespace std;

const char* SAVE_FILE_NAME = "hotel_system.bin";
const size_t MAX_INPUT_LEN = 128;

Hotel::Hotel(){}

int Hotel::first_free_index() {
   for (int i = 0; i < rooms.get_size(); i++) {
      if (&rooms[i] == nullptr)
         return i;
   }
   return -1;
}
Room* Hotel::get_room(int room_num) const
{
   for (int i = 0; i < rooms.get_size(); i++) {
         if (rooms[i].get_room_num() == room_num)
            return &rooms[i];
      }
      return nullptr;
}
bool Hotel::create_reservation(const Reservation& res) {
   if (get_room(res.get_room_num()) == nullptr) {
      rooms.push_back(res);
      return true;
   }
   return false;
}

Room* Hotel::get_unavailable_rooms(int from_day,int from_month,int from_year, 
                                    int to_day,int to_month,int to_year) {
   
   Date from_date(from_day, from_month, from_year);
   Date to_date(to_day, to_month, to_year);
   
   for (int i = 0; i < rooms.get_size(); i++) {
      if (from_date == rooms[i].get_from_date() && to_date == rooms[i].get_to_date())
         return &rooms[i];
   }
   return nullptr;

   /*for (int i = 0; i < rooms.get_size(); i++) {
      if((rooms[i].get_from_date().compare_to(from_date)) == 0 && (rooms[i].get_to_date().compare_to(to_date))== 0)
      return &rooms[i];
   }*/
}

Hotel& Hotel::i()
{
   static Hotel h;
   return h;
}

bool Hotel::serialize() const {
   ofstream ofs;
      ofs.open(SAVE_FILE_NAME, ios::binary);
   if (!ofs) {
      cout << "Can not open " << SAVE_FILE_NAME << "file for writing!\n";
      return false;
   }
   int len = rooms.get_size();
   ofs.write((const char*)&len, sizeof(len));
   for (int i = 0; i < len; i++)
      rooms[i].serialize(ofs);

   ofs.close();
   return true;
}
bool Hotel::deserialize() {
   ifstream ifs;
      ifs.open(SAVE_FILE_NAME, ios::binary);
   if (!ifs.is_open()) return false;

   int len=rooms.get_size();
   ifs.read((char*)&len, sizeof(len));
   for (int i = 0; i < len; i++)
      rooms.deserialize(ifs);

   ifs.close();
   return true;
}

void Hotel::run() {
   if (deserialize()) cout << "Successfully loaded " << rooms.get_size() << " room(s)" << endl;
   else
      cout << "No previous hotel system information.\n";

   cout << endl;

   display();
   cout << endl;

   char command[MAX_INPUT_LEN];
   char note[MAX_INPUT_LEN];
   int number;  
   int from_day, from_month, from_year;
   int to_day, to_month, to_year;
  
   do {
      cout << "ENTER AN OPTION: "; cin >> command;
      if (strcmp(command, "help") == 0) {
         display();
      }
      
      else if (strcmp(command, "check_in") == 0) {
         cout << "****CHECK-IN****\n";
         cout << "Room number: "; cin >> number;
         cout << "From date: "; cin >> from_day>> from_month>> from_year; 
         cout << "To Date: "; cin >> to_day >> to_month>> to_year; 
         cout << "Note: "; cin >> note;
         if (create_reservation({number,from_day,from_month,from_year,to_day, to_month, to_year,note})) {
            cout << "Room added successfully!\n";
         }
         else {
            cout << "Room " << number << " already exists!\n";
         }
         cout << endl;

      }

      else if (strcmp(command, "extras") == 0) {
         cout << "****ADDITIONAL EXTRAS FOR YOUR ROOM****\n";
         cout << "Enter your room number: "; 
         cin >> number;
         bool breakfast;
         if (contains_room(number)) {
            cout << "Do you want breakfast? Enter: 1 for YES or 0 for NO: "; cin >> breakfast;
            if (breakfast) {
               create_reservation({ number, breakfast });               
               cout << "Successfully added breakfast to your reservation!\n";             
            }
         }
         else
            cout << "Sorry, you have to check-in first!\n";
         cout << endl;
      }

      else if (strcmp(command, "available_rooms") == 0) {
         cout << "****LISTS OF AVAILABLE ROOMS****\n";
         cout << "From date: "; cin >> from_day >> from_month >> from_year;
         cout << "To date: "; cin >> to_day >> to_month >> to_year;
         Room* res = get_unavailable_rooms(from_day, from_month, from_year, to_day, to_month, to_year);
         if (res) {  cout << *res << endl; 
            return;
         }
         else 
         cout << "There are not available rooms on this dates!\n";        
         
         cout << endl;
      }

      else if (strcmp(command, "check_out") == 0) {
         cout << "Enter your room number: "; 
         cin >> number;
         if(contains_room(number)){
               for (int i = 0; i < rooms.get_size(); i++)
               rooms.remove_at(number);
            cout << "Room with number: " << number << " checked-out successfully!\n";
         }
         else {
            cout << "Room " << number << " not found! \n";
         }
         cout << endl;
      }
      
      else if (strcmp(command, "report_rooms") == 0) {
         cout << "****LISTS OF RESERVED ROOMS****\n";
         cout << "From date: "; cin >> from_day >> from_month >> from_year;
         cout << "To date: "; cin >> to_day >> to_month >> to_year;      
         Room* res = get_unavailable_rooms(from_day, from_month, from_year, to_day, to_month, to_year);
         for (int i = 0; i < rooms.get_size(); i++) {
            if(res) {
               rooms[i].print();
               cout << endl;
            }
            else
               cout << "Room from the period: " << rooms[i].get_from_date() << " - " << rooms[i].get_to_date() << " not found!\n";    
         }
           cout << endl;       
      }

      else if (strcmp(command, "find_room") == 0) {

      }
      else if (strcmp(command, "important_guest") == 0) {

      }
      else if (strcmp(command, "unavailable_room") == 0) {

      }

      else if (strcmp(command, "exit") == 0) {
         if (serialize())
            cout << "Successfully saved the system information!\n";
         else {
            cout << "Couldn't saved the system information. Exit anyway: [y/n]? : ";
            char option;
            cin.ignore(MAX_INPUT_LEN, '\n');
            cin.get(option);
            if (option == 'y' || option == 'n') 
               command[0] = '\n';          
         }
      }      
      
      else {
         cout << "Unknown command! Type 'help' for more information: " << endl;
      }
   } while (strcmp(command, "exit") != 0);
}


void Hotel::display() {
   cout << "*********** HOTEL JOANNNA MANAGEMENT SYSTEM ***********" << endl;
   cout << "help - Prints this information." << endl;
   cout << "check_in - Check-In Room" << endl;
   cout << "extras - Additional EXTRAS for the room" << endl;
   cout << "available_rooms - Available rooms" << endl;
   cout << "check_out - Chechk-Out Room" << endl;
   cout << "report_rooms - Show report of all used rooms" << endl;
   cout << "find_room - Find suitable room with a certain number of beds" << endl;
   cout << "important_guest - Find room for important guest" << endl;
   cout << "unavailable_room - Show rooms which are unavailables to use" << endl;
   cout << "exit  - saves the system and exit the program" << endl;
}
