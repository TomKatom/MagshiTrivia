#include "RoomManager.hpp"
#include <algorithm>

void RoomManager::createRoom( RoomData room) {
	if (std::find_if(this->m_rooms.begin(), this->m_rooms.end(), [&](auto currRoom) {return currRoom.second.getName() == room.name; }) != this->m_rooms.end()) {
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

std::vector<RoomData> RoomManager::getRooms() const{
	std::vector<RoomData> rooms;
	for (auto room : this->m_rooms) {
		RoomData temp{room.second.getName(), room.second.getMaxPlayers(), room.second.getTimePerQuestion(), room.second.getQuestionsCount() };
		rooms.push_back(temp);
	}
	return rooms;
}

std::vector<std::string> RoomManager::getPlayersInRoom(int id)  {
	std::vector<std::string> playersInRoom;
	if (this->m_rooms.find(id) != this->m_rooms.end()) {
		for (LoggedUser & user : this->m_rooms[id].getAllUsers()) {
			playersInRoom.push_back(user.getUsername());
		}
		return playersInRoom;
	}
	else {
		throw std::exception("Room Doesn't Exist.");
	}
}