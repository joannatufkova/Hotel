#ifndef ROOMSLIST_H
#define ROOMSLIST_H
#define _CRT_SECURE_NO_WARNINGS
#include"Room.h"
using namespace std;

class RoomsList {
private:
   Room* rooms;
   int size;
   int capacity;

   void Resize();
   void Copy_From(const RoomsList& other);
   void Free();

public:
   RoomsList();
   RoomsList(int new_capacity);
   RoomsList(const RoomsList& other);
   RoomsList& operator=(const RoomsList& other);
   ~RoomsList();

   void push_back(const Room& room);
   void shift_left(int index);
   int remove_at(int index);

   int get_size() const { return size; };
   int get_capacity() const { return capacity; };
   
   bool is_full() { return size == capacity; };
   bool is_valid_room_number(int room_number) { return (room_number >= 1 && room_number <= 50); };
   Room& operator[](int index) const;

   void serialize(ofstream& ofs) const;
   void deserialize(ifstream& ifs);

   friend ostream& operator<<(ostream& os, const RoomsList& obj);
   void print(ostream& os=cout) const;
};

#endif // !ROOMSLIST_H