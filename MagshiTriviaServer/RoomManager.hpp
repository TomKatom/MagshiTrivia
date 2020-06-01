#include "Room.hpp"
#include "RoomData.hpp"
#include <map>
class RoomManager {
public:
	void createRoom(LoggedUser user, RoomData room);
	void deleteRoom(int id);
	bool getRoomState(int id);
	std::list<Room> getRooms() const;
private:
	std::map<int, Room> m_rooms;
	int _roomIdCount;
};