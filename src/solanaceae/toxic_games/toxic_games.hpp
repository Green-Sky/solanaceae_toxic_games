#pragma once

#include <cstdint>
#include <memory>
#include <map>
#include <vector>

#include <solanaceae/contact/contact_model3.hpp>
#include <solanaceae/tox_contacts/tox_contact_model2.hpp>

#include "./toxic_game_i.hpp"

// TODO events:
// got invite

class ToxicGames : public ToxEventI {
	Contact3Registry& _cr;
	ToxI& _t;
	ToxEventProviderI::SubscriptionReference _tep_sr;
	ToxContactModel2& _tcm;

	std::map<uint8_t, std::unique_ptr<ToxicGameI>> _game_types;
	std::map<uint8_t, std::map<uint32_t, std::unique_ptr<ToxicGameI::InstanceI>>> _game_instances;

	public:
		ToxicGames(
			Contact3Registry& cr,
			ToxI& t,
			ToxEventProviderI& tep,
			ToxContactModel2& tcm
		);

		~ToxicGames(void) {}

	public:
		// TODO: a setup game, for configurability?
		void createGame(uint8_t game_type, std::vector<Contact3> with);
		// with (contact list) ?
		void acceptInvite(Contact3 from, uint8_t game_type, uint32_t game_id);

	public: // internal, for games (TODO: extract?)
		bool sendPacket(Contact3 to, uint8_t game_type, uint32_t game_id, const uint8_t* data, const size_t data_size);

	private: // tox events
		bool onToxEvent(const Tox_Event_Friend_Lossless_Packet* e) override;
		bool onToxEvent(const Tox_Event_Group_Custom_Packet* e) override;
		bool onToxEvent(const Tox_Event_Group_Custom_Private_Packet* e) override;
};

