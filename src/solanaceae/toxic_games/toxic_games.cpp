#include "./toxic_games.hpp"

#include <cstdint>
#include <iostream>

ToxicGames::ToxicGames(
	Contact3Registry& cr,
	ToxI& t,
	ToxEventProviderI& tep,
	ToxContactModel2& tcm
) :
	_cr(cr),
	_t(t),
	_tep(tep),
	_tcm(tcm)
{

	// register custom packet handlers
	_tep.subscribe(this, Tox_Event::TOX_EVENT_FRIEND_LOSSLESS_PACKET);
	_tep.subscribe(this, Tox_Event::TOX_EVENT_GROUP_CUSTOM_PACKET);
	_tep.subscribe(this, Tox_Event::TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET);
}

bool ToxicGames::onToxEvent(const Tox_Event_Friend_Lossless_Packet* e) {
	//CUSTOM_PACKET_GAME_INVITE = 160,
	//CUSTOM_PACKET_GAME_DATA   = 161,

	const uint32_t friend_number = tox_event_friend_lossless_packet_get_friend_number(e);
	const uint32_t data_length = tox_event_friend_lossless_packet_get_data_length(e);
	const uint8_t* data = tox_event_friend_lossless_packet_get_data(e);

	if (data_length < 7) { // packet id + netver + gametype + 4 gameid
		return false;
	}

	if (data[0] != 160 && data[0] != 161) {
		// not a toxic games friend packet
		return false;
	}

	const uint8_t game_networking_version = data[1];
	const uint8_t game_type = data[2];
	const uint32_t game_id =
		(data[3] << 24) |
		(data[4] << 16) |
		(data[5] << 8) |
		(data[6] << 0)
	;

	if (game_networking_version != 0x01) {
		std::cerr << "TG warning: peer sent mismatching network version packet\n";
		return false;
	}

	if (data[0] == 160) {
		std::cout << "TG: game invite packet gt:" << (uint32_t)game_type << " id:" << game_id << "\n";
	} else if (data[0] == 161) {
		std::cout << "TG: game packet gt:" << (uint32_t)game_type << " id:" << game_id << "\n";
	}

	return true;
}

bool ToxicGames::onToxEvent(const Tox_Event_Group_Custom_Packet* e) {
	return false;
}

bool ToxicGames::onToxEvent(const Tox_Event_Group_Custom_Private_Packet* e) {
	return false;
}
