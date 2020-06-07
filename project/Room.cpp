#include"Room.h"

Room::Room() : from_date(4,1,2020), to_date(4,1,2021), is_init(false) , beds(0),room_num(0) {}

Room::Room(int new_room_num, int from_day, int from_month, int from_year, int to_day, int to_month, int to_year, unsigned new_beds)
   :from_date(from_day,from_month,from_year),to_date(to_day,to_month,to_year) , room_num(new_room_num),beds(new_beds)
{
   if (!is_valid_date()) 
      to_date = from_date;
   
}
void Room::deserialize(ifstream& ifs) {
   if (!ifs.is_open()) {
      cout << "Can not open this file!\n";
      return;
   }
    ifs.read((char*)&from_date, sizeof(from_date));
   ifs.read((char*)&to_date, sizeof(to_date));
   ifs.read((char*)&room_num, sizeof(room_num));
   ifs.read((char*)&beds, sizeof(beds));

   if (ifs.good()) {
      cout << "Successfully deserialized!\n";
   }
   else
      cout << "Failed\n";
}
void Room::serialize(ofstream& out) const
{ 
   out.write((const char*)&from_date, sizeof(from_date));
   out.write((const char*)&to_date, sizeof(to_date));
   out.write((const char*)&room_num, sizeof(room_num));
   out.write((const char*)&beds, sizeof(beds));
  
   /*const char* n_date = from_date.get_date();
    int len = strlen(n_date)+1;
    out.write((const char*)&len, sizeof(len));
    out.write(n_date, len);

     n_date = to_date.get_date();
     len = strlen(n_date) + 1;
    out.write((const char*)&len, sizeof(len));
    out.write(n_date, len);
    */

}

void Room::print(ostream& os) const {
   os << "Room number: " << room_num << endl;
   os << "From date: "; from_date.print();
   os <<' '<<"To date: "; to_date.print();
}
ostream& operator<<(ostream& os, const Room& obj) {
      obj.print(os);
      return os << endl;
   
}