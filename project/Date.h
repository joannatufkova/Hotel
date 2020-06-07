#ifndef DATE_H
#define DATE_H
#include<iomanip>
#include<iostream>
#include <fstream>
using namespace std;

class Date {
private:
   int day;
   int month;
   int year;

public:
   void set_day(int);
   void set_month(int);
   void set_year(int);
 
   int get_day() const { return day; };
   int get_month() const { return month; };
   int get_year() const { return year; };

   Date();
   Date(int day, int month, int year);

   int compare_to(const Date& other) const;

   bool operator==(const Date& other) const;
   //bool is_leap_year(int year);
   //void optional(int n);

   friend ostream& operator<<(ostream& os, const Date& obj);
   virtual void print(ostream& os=cout) const;

   void serialize(ofstream& ofs) const;
   void deserialize(ifstream& ifs);
};
#endif