#include "./toxic_games.hpp"

#include <solanaceae/toxcore/tox_interface.hpp>
#include <solanaceae/tox_contacts/components.hpp>

#include <cstdint>
#include <iostream>

#include "./games/chess.hpp"

// https://youtu.be/9tLCQQ5_ado

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

	{ // chess
		auto tmp_game = std::make_unique<Chess>(*this);
		const auto game_type = tmp_game->getGameType();
		_game_types[game_type] = std::move(tmp_game);
	}

	// register custom packet handlers
	_tep.subscribe(this, Tox_Event::TOX_EVENT_FRIEND_LOSSLESS_PACKET);
	_tep.subscribe(this, Tox_Event::TOX_EVENT_GROUP_CUSTOM_PACKET);
	_tep.subscribe(this, Tox_Event::TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET);
}

//void ToxicGames::addGameInstance(uint8_t game_type, uint32_t game_id, std::unique_ptr<ToxicGameI::InstanceI> instance) {
	//// TODO: error checking
	//_game_instances[game_type][game_id] = std::move(instance);
//}

void ToxicGames::createGame(uint8_t game_type, std::vector<Contact3> with) {
}

void ToxicGames::acceptInvite(Contact3 from, uint8_t game_type, uint32_t game_id) {
}

bool ToxicGames::sendPacket(Contact3 to, uint8_t game_type, uint32_t game_id, const uint8_t* data, const size_t data_size) {
	if (!_cr.valid(to)) {
		return false;
	}

	// online gaming
	if (!_cr.all_of<Contact::Components::ToxFriendEphemeral>(to) && !_cr.all_of<Contact::Components::ToxGroupPeerEphemeral>(to)) {
		return false;
	}

	// friend
	if (_cr.all_of<Contact::Components::ToxFriendEphemeral>(to)) {
		std::vector<uint8_t> pkg;
		pkg.push_back(161); // game data
		pkg.push_back(0x01); // netver
		pkg.push_back(game_type);
		pkg.push_back((game_id >> 24) & 0xff);
		pkg.push_back((game_id >> 16) & 0xff);
		pkg.push_back((game_id >> 8) & 0xff);
		pkg.push_back((game_id >> 0) & 0xff);
		pkg.insert(pkg.cend(), data, data+data_size);

		const auto send_err = _t.toxFriendSendLosslessPacket(
			_cr.get<Contact::Components::ToxFriendEphemeral>(to).friend_number,
			pkg
		);

		return send_err == TOX_ERR_FRIEND_CUSTOM_PACKET_OK;
	}

	// group peer
	if (_cr.all_of<Contact::Components::ToxGroupPeerEphemeral>(to)) {
		return false; // TODO
	}

	return false;
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
