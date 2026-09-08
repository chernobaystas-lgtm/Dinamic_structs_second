#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include  <cassert>
using namespace std;

enum class RoomType {
	Living,
	Bedroom, 
	Kitchen,
	Bathroom, 
	Dining_room,
	Toilet,
	Study,
	Hall,
	Nursery,
	Playroom,
	Dressing_room,
	Laundry_room,
	Pantry_Box_room
};

enum class Furniture {
	Sofa,
	Armchair,
	Coffee_table,
	TV_stand,
	Bookcase,
	Bed,
	Bedside_table,
	Wardrobe,
	Chest_of_drawers,
	Crib,
	Desk,
	Desk_chair,
	Kitchen_cabinet,
	Dining_table,
	Chair,
	Bar_stool,
	Countertop,
	Vanity,
	Mirror_cabinet,
	Towel_rack,
	Coat_rack,
	Shoe_rack,
	Ottoman,
	Full_length_mirror,
	Storage_shelf,
	Ironing_board
};

string room_type_to_string(RoomType t) {
	switch (t) {
	case RoomType::Living: return "Living";
	case RoomType::Bedroom: return "Bedroom";
	case RoomType::Kitchen: return "Kitchen";
	case RoomType::Bathroom: return "Bathroom";
	case RoomType::Dining_room: return "Dining room";
	case RoomType::Toilet: return "Toilet";
	case RoomType::Study: return "Study";
	case RoomType::Hall: return "Hall";
	case RoomType::Nursery: return "Nursery";
	case RoomType::Playroom: return "Playroom";
	case RoomType::Dressing_room: return "Dressing room";
	case RoomType::Laundry_room: return "Laundry room";
	case RoomType::Pantry_Box_room: return "Pantry/Box room";
	default: return "Unknown";
	}
}

class Room {

private:
	int How_much_windows;
	int How_much_sockets;
	double area;
	enum class RoomType type_of_room;
	enum class Furniture furniture;

	
public:
	
	Room() : How_much_windows(0), How_much_sockets(0), area(0.0), type_of_room(RoomType::Living), furniture(Furniture::Sofa) {
		cout << "[Room] Default constructor" << endl;
	}

	Room(int windows, int sockets, double room_area, RoomType room_type, Furniture room_furniture) : How_much_windows(windows), How_much_sockets(sockets), area(room_area), type_of_room(room_type), furniture(room_furniture) {
		cout << "[Room] Constructor" << endl;
	}

	~Room() {
		cout << "[Room] Destructor" << endl;
	}

	friend ostream& operator<<(ostream& out, const Room& room) {
		out << "Room [" << room_type_to_string(room.type_of_room) << "]: "
			<< room.area << " m2, "
			<< room.How_much_windows << " windows, "
			<< room.How_much_sockets << " sockets";
		return out;
	}

	friend istream& operator>>(istream& in, Room& room) {
		in >> room.How_much_windows >> room.How_much_sockets >> room.area;

		cout << "Choose room type (0-Living, 1-Bedroom, 2-Kitchen, 3-Bathroom, 4-Dining_room, "
			<< "5-Toilet, 6-Study, 7-Hall, 8-Nursery, 9-Playroom, 10-Dressing_room, "
			<< "11-Laundry_room, 12-Pantry_Box_room): ";
		int typeInput;
		in >> typeInput;
		room.type_of_room = static_cast<RoomType>(typeInput);

		return in;
	}

	int get_How_much_windows() const { return How_much_windows; }
	int get_How_much_sockets() const { return How_much_sockets; }
	double get_area() const { return area; }
	RoomType get_type_of_room() const { return type_of_room; }
	Furniture get_furniture() const { return furniture; }

	void set_How_much_windows(int p) { How_much_windows = p; }
	void set_How_much_sockets(int p) { How_much_sockets = p; }
	void set_area(double p) { area = p; }
	void set_type_of_room(RoomType p) { type_of_room = p; }
	void set_furniture(Furniture p) { furniture = p; }



};

class Apartment {

private:
	Room* Rooms;
	int room_count;
	int balcony_count;
	double square;
	string name_of_resident;
	string address;



public:

	void show_rooms() const {
		if (Rooms == nullptr) {
			cout << "No rooms in the apartment." << endl;
			return;
		}
		for (int i = 0; i < room_count; ++i) {
			cout << Rooms[i] << endl;
		}
	}

	inline int get_balcony_count() const {
		return balcony_count;
	}

	inline double get_square() const {
		return square;
	}

	inline string get_name_of_resident() const {
		return name_of_resident;
	}

	inline string get_address() const {
		return address;
	}

	inline void set_balcony_count(int count) {
		balcony_count = count;
	}

	inline void set_square(double sq) {
		square = sq;
	}

	inline void set_name_of_resident(const string& name) {
		name_of_resident = name;
	}

	inline void set_address(const string& addr) {
		address = addr;
	}




	Apartment() : Rooms(nullptr), balcony_count(0), room_count(0), square(0.0), name_of_resident(""), address("") {
		cout << "[Apartment] Default constructor" << endl;
	}

	Apartment(int balcony_count, double square, const string& name_of_resident, const string& address)
		: Rooms(nullptr), balcony_count(balcony_count), room_count(0), square(square), name_of_resident(name_of_resident), address(address) {
		cout << "[Apartment] Constructor" << endl;
	}

	~Apartment() {
		cout << "[Apartment] Destructor" << endl;
		delete[] Rooms;
	}

	Apartment(const Apartment& other)
		: Rooms(nullptr), balcony_count(other.balcony_count), square(other.square),
		name_of_resident(other.name_of_resident), address(other.address), room_count(other.room_count)
	{
		cout << "[Apartment] Copy constructor: " << address << endl;
		if (other.Rooms) {
			Rooms = new Room[room_count];
			for (int i = 0; i < room_count; ++i) Rooms[i] = other.Rooms[i];
		}
	}

	Apartment& operator=(const Apartment& other) {
		if (this == &other) return *this;
		balcony_count = other.balcony_count;
		square = other.square;
		name_of_resident = other.name_of_resident;
		address = other.address;
		room_count = other.room_count;
		delete[] Rooms;
		Rooms = nullptr;
		if (other.Rooms) {
			Rooms = new Room[room_count];
			for (int i = 0; i < room_count; ++i) Rooms[i] = other.Rooms[i];
		}
		return *this;
	}

	Apartment(int roomCount, int balconyCnt, double sq, const string& name, const string& addr)
		: Rooms(nullptr), room_count(roomCount), balcony_count(balconyCnt), square(sq),
		name_of_resident(name), address(addr)
	{
		cout << "[Apartment] Constructor: creating " << room_count << " rooms..." << endl;
		Rooms = new Room[room_count];
		for (int i = 0; i < room_count; ++i) {
			cout << "Enter data for room " << i + 1 << ":" << endl;
			cin >> Rooms[i];
		}
	}

	void show_apartment() const {
		cout << "Address: " << address << endl;
		cout << "Resident: " << name_of_resident << endl;
		cout << "Total area: " << square << " m2" << endl;
		cout << "Balconies: " << balcony_count << endl;
		show_rooms();
	}

};


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


}
