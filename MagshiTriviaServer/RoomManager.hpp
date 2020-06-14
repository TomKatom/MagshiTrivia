#include "Room.hpp"
#include "RoomData.hpp"
#include <map>
class RoomManager {
public:
	void createRoom(RoomData room);
	void deleteRoom(int id);
	bool getRoomState(int id);
	std::vector<RoomData> getRooms() const;
	std::vector<std::string> getPlayersInRoom(int id);

private:
	std::map<int, Room> m_rooms;
	int _roomIdCount;
};