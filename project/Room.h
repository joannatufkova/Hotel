#ifndef ROOM_H
#define ROOM_H
#define _CRT_SECURE_NO_WARNINGS
#include"Date.h"
#include<iostream>
#include <fstream>
using namespace std;

class Room {
private:
   Date from_date;
   Date to_date;
   bool is_init;

   int room_num;
   unsigned beds;

public:
   Room();
   Room(int new_room_num,int from_day,int from_month,int from_year,int to_day,int to_month,int to_year, unsigned new_beds);

   const Date& get_from_date() const { return from_date; };
   const Date& get_to_date() const { return to_date; };

   int get_room_num() const { return room_num; };
   unsigned get_beds() const { return beds; };

   bool get_is_init() const { return is_init; };
   bool is_valid_date() { return from_date.compare_to(to_date) >= 0; };

   void serialize(ofstream& out) const;
   void deserialize(ifstream& ifs);

   void print(ostream& os=cout) const;
   friend ostream& operator<<(ostream& os, const Room& obj);

   /* void set_total_beds(int new_beds);
 int get_free_beds() const { return total_beds - reserved_beds; };
 int get_total_beds() const { return total_beds; }
 int get_reserved_beds() const { return reserved_beds; }*/

};
#endif // !ROOM_H
