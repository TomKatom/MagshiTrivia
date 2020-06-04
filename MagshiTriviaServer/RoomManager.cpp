#include "RoomManager.hpp"
#include <algorithm>

void RoomManager::createRoom(LoggedUser user, RoomData room) {
	if (std::find_if(this->m_rooms.begin(), this->m_rooms.end(), [&](auto currRoom) {return currRoom.getName() == room.name; }) == this->m_rooms.end()) {
		throw std::exception("Room with this name already exists.");
	}
	else {
		this->_roomIdCount++;
		this->m_rooms.insert(std::pair(this->_roomIdCount, Room(this->_roomIdCount, room.name, room.maxPlayers, room.timePerQuestion)));
	}
}

void RoomManager::deleteRoom(int id) {
	this->m_rooms.erase(this->m_rooms.find(id));
}

bool RoomManager::getRoomState(int id) {
	if (this->m_rooms.find(id) != this->m_rooms.end()) {
		return this->m_rooms[id].getState();
	}
	else {
		throw std::exception("Room Doesn't Exist.");
	}
}

std::list<Room> RoomManager::getRooms() const{
	std::list<Room> rooms;
	for (auto room : this->m_rooms) {
		rooms.push_back(room.second);
	}
	return rooms;
}