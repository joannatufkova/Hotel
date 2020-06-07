#include"RoomsList.h"


void RoomsList::Resize() {
   Room* temp = new Room[capacity*2];
   for (int i = 0; i < size; i++) 
      temp[i] = rooms[i];
   delete[] rooms;
   rooms = temp;
}
void RoomsList::Copy_From(const RoomsList& other) {
   rooms = new Room[other.capacity]; 
   for (int i = 0; i < other.size; i++)
      rooms[i] = other.rooms[i];

   capacity = other.capacity;
   size = other.size;
}
void RoomsList::Free() {
   delete[] rooms;
}

RoomsList::RoomsList() {
   capacity = 4;
   rooms = new Room[capacity];
   size = 0;
}
RoomsList::RoomsList(int new_capacity) {
   if (capacity == 0) {
      capacity = 1;
   }
   rooms = new Room[new_capacity];
   size = 0;
   capacity = new_capacity;
}
RoomsList::RoomsList(const RoomsList& other) {
   Copy_From(other);
}
RoomsList& RoomsList::operator=(const RoomsList& other) {
   if (this != &other) {
      Free();
      Copy_From(other);
   }
   return *this;
}
RoomsList::~RoomsList() {
   Free();
}

void RoomsList::push_back(const Room& new_room) {
   if (!is_valid_room_number(new_room.get_room_num()))
      return;   
   if (is_full()) 
      Resize();   
   rooms[size++] = new_room;
}

void RoomsList::shift_left(int index)
{
   for (int i = index; i < size - 1; i++)
   {
      rooms[i] = rooms[i + 1];
   }
}
int RoomsList::remove_at(int index)
{
      if (size == 0 || index > size)
      {
         return 0;
      }
      shift_left(index);
      size--;
      return 1;

   
   size--;
}


Room& RoomsList::operator[](int index) const {
    return rooms[index];
}

ostream& operator<<(ostream& os, RoomsList& obj) {
   obj.print(os);
   return os << endl;
}
void RoomsList::print(ostream& os) const {
   for (int i = 0; i < size; i++) {
      rooms[i].print();
   }
}

void RoomsList::serialize(ofstream& ofs) const {
   if (!ofs.is_open()) { return;}

   ofs.write((const char*)&size, sizeof(size));
   ofs.write((const char*)&capacity, sizeof(capacity));
   for (int i = 0; i < size; i++) {
      rooms[i].serialize(ofs);
   }
}
void RoomsList::deserialize(ifstream& ifs) {
   if (!ifs.is_open()) { return; }
   ifs.read((char*)&size, sizeof(size));
   ifs.read((char*)&capacity, sizeof(capacity));

   int len;
   ifs.read((char*)&len, sizeof(int));
   for (int i = 0; i < len; i++) {
      rooms[i].deserialize(ifs);
      push_back(rooms[i]);
   }
}
