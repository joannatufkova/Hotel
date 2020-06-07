#ifndef RESERVATION_H
#define RESERVATION_H
#include"Room.h"
#include<fstream>
#include<iostream>
using namespace std;

class Reservation : public Room {
private:
   char* note;
   int guests;
   bool breakfast;

   void Copy_From(const Reservation& other);
   void Free();

public:
   Reservation(int room_num=0, int from_day=4, int from_month=1, int from_year=2020, int to_day=4, int to_month=1, int to_year=2021,
      const char* new_note="<Unnamed>", unsigned beds=0, int new_guests=0,bool breakfast=false);
   Reservation(const Reservation& other);
   Reservation& operator=(const Reservation& other);
   ~Reservation();

   const char* get_note() const { return note; };
   void set_note(const char* note);

   int get_guests() const { return guests; };
   
   double get_price() const { return 9.9; };

   void serialize(ofstream& ofs) const;
   void deserialize(ifstream& ifs);
  
   void print(ostream& os=cout) const;
   friend ostream& operator<<(ostream& os, const Reservation& obj);
};


#endif // !RESERVATION_H
