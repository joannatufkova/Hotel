#include"Reservation.h"

bool has_digits(const char* str, int len)
{
   for (int i = 0; i < len; i++)
   {
      if (str[i] >= '0' && str[i] <= '9')
         return true;
   }
   return false;
}

void Reservation::Copy_From(const Reservation& other) {
   note = new char[strlen(other.note) + 1];
   strcpy(note, other.note);

   guests = other.guests;
   breakfast = other.breakfast;
}
void Reservation::Free() {
   delete[] note;
   note = nullptr;
}

Reservation::Reservation(int room_num, int from_day, int from_month, int from_year, int to_day, int to_month, int to_year,
   const char* new_note, unsigned beds, int new_guests, bool new_breakfast)  
   : Room(room_num,from_day,from_month,from_year,to_day,to_month,to_year,beds),
   note(new char[strlen(new_note) + 1]), guests(new_guests), breakfast(new_breakfast) {}

Reservation::Reservation(const Reservation& other) {
   Copy_From(other);
}
Reservation& Reservation::operator=(const Reservation& other) {
   if (this != &other) {
      Free();
      Copy_From(other);
   }
   return *this;
}
Reservation::~Reservation() {
   Free();
}

void Reservation::set_note(const char* note)
{
   //delete[] note; 
   int len = strlen(note);
   if (has_digits(note, len))
   {
      this->note[0] = '\0';
      return;
   }
   this->note = new char[len + 1];
   strcpy(this->note, note);

}

void Reservation::deserialize(ifstream& ifs) {
   if (!ifs.is_open()) {
   cout << "Can not open this file!\n"; 
   return;
   }
   size_t len;
   ifs.read((char*)&len, sizeof(len));
   note = new char[len+1];
   if (note) {
      ifs.read(note, len);
      note[len] = '\0';
   }
   ifs.read((char*)&guests, sizeof(guests));
   ifs.read((char*)&breakfast, sizeof(breakfast));

   if (ifs.good()) {
      cout << "Successfully deserialized!\n";
   }
   else
      cout << "Failed\n";
}

void Reservation::serialize(ofstream& out) const {
   size_t len = strlen(note) + 1;
   out.write((const char*)&len, sizeof(len));
   out.write((const char*)note, len);

   out.write((const char*)&guests, sizeof(guests));
   out.write((const char*)&breakfast, sizeof(breakfast));
}

void Reservation::print(ostream& os) const {
   Room::print(os);
   os << "The room has reserved by: " << note << " with "
      << guests << " guest(s)." << endl;
   if (breakfast) cout << get_price() << " EUR for breakfast.\n";
}

ostream& operator<<(ostream& os, const Reservation& r) {
   r.print(os);
   return os << endl;
}
