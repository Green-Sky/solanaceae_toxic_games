#pragma once

#include <solanaceae/contact/contact_model3.hpp>
#include <solanaceae/tox_contacts/tox_contact_model2.hpp>

class ToxicGames : public ToxEventI {
	Contact3Registry& _cr;
	ToxI& _t;
	ToxEventProviderI& _tep;
	ToxContactModel2& _tcm;

	public:
		ToxicGames(
			Contact3Registry& cr,
			ToxI& t,
			ToxEventProviderI& tep,
			ToxContactModel2& tcm
		);

	private: // tox events
		bool onToxEvent(const Tox_Event_Friend_Lossless_Packet* e) override;
		bool onToxEvent(const Tox_Event_Group_Custom_Packet* e) override;
		bool onToxEvent(const Tox_Event_Group_Custom_Private_Packet* e) override;
};

