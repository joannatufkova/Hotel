#include "Date.h"
#include<iostream>
using namespace std;

void Date::set_day(int day) {
   if (day < 1 || day>31)
      day = 1;
   this->day = day;
}
void Date::set_month(int month) {
   if (month < 1 || month>12)
      month = 1;
   this->month = month;
}
void Date::set_year(int year) {
   if (year < 2020||year>=2022)
      year = 2020;
   this->year = year;
}

Date::Date() {
   day = 4;
   month = 1;
   year = 2020;
}
Date::Date(int day, int month, int year) {
   set_day(day);
   set_month(month);
   set_year(year);
}

bool Date::operator==(const Date& other) const {
   return ((this->day == day) && (this->month == month) && (this->year == year));
}

void Date::deserialize(ifstream& ifs) {
   if (!ifs.is_open()) {
      cout << "Can not open this file!\n";
      return;
   }
   ifs.read((char*)&day, sizeof(day));
   ifs.read((char*)&month, sizeof(month));
   ifs.read((char*)&year, sizeof(year));
 
   if (ifs.good()) {
      cout << "Successfully deserialized!\n";
      return;
   }
   else
      cout << "Failed\n";
}
void Date::serialize(ofstream& ofs) const {
   ofs.write((const char*)&day, sizeof(day));
   ofs.write((const char*)&month, sizeof(month));
   ofs.write((const char*)&year, sizeof(year));
}

ostream& operator<<(ostream& os, const Date& obj) {
   obj.print(os);
   return os << endl;
}
void Date::print(ostream& os) const {
   os << year;
   os << "/";
   os << setw(2);
   os << setfill('0');
   os << month;
   os << "/";
   os << day;
}
int Date::compare_to(const Date& other) const
{
   if (get_day() > other.get_day())
      return -1;
   else if (get_day() < other.get_day())
   {
      return 1;
   }
   else
   {
      if (get_month() > other.get_month())
         return -1;
      else if (get_month() < other.get_month())
         return 1;
      else
      {
         if (get_year() > other.get_year())
            return -1;
         else if (get_year() < other.get_year())
            return 1;
         else
            return 0;
      }
   }
}

/*bool Date::is_leap_year(int year) {
   return((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}
void Date::optional(int n) {
   this->day += n;
   int* this_year = nullptr;
   if (is_leap_year(year)) {
      this_year = leap;
   }
   else
      this_year = not_leap;
   if (day > this_year[month]) {
      day -= this_year[month];
      ++month;
   }
   if (month > 12) {
      month = 1;
      ++year;
   }


}*/
