#include "./solanaceae_toxic_games.hpp"

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

	return false;
}

bool ToxicGames::onToxEvent(const Tox_Event_Group_Custom_Packet* e) {
	return false;
}

bool ToxicGames::onToxEvent(const Tox_Event_Group_Custom_Private_Packet* e) {
	return false;
}
