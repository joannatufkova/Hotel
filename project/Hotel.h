#ifndef HOTEL_H
#define HOTEL_H
#include"Date.h"
#include"RoomsList.h"
#include"Room.h"
#include"Reservation.h"
using namespace std;

class Hotel {
private:
   RoomsList rooms;
  
   Hotel();
   Room* get_room(int room_num) const;
   Room* get_unavailable_rooms(int from_day, int from_month, int from_year,int to_day, int to_month, int to_year);

   void display();

public:
   static Hotel& i();

   int first_free_index();
   bool contains_room(unsigned room_num) const { return get_room(room_num); };
   bool create_reservation(const Reservation& res); 
  
   void run();

   bool serialize() const;
   bool deserialize();
};
#endif // !HOTEL_H