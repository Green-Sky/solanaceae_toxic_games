#pragma once

#include <cstdint>
#include <memory>
#include <vector>

//#include <solanaceae/contact/contact_model3.hpp>
//enum class Contact3 : uint32_t {};

// fwd
class ToxicGames;

// static state/info + dynamic factory
struct ToxicGameI {
	ToxicGames& _tg;

	ToxicGameI(ToxicGames& tg) : _tg(tg) {}
	virtual ~ToxicGameI(void) {}

	struct InstanceI {
		uint32_t _id;

		virtual ~InstanceI(void) {}

		// TODO: just destructor?
		// needs to send quit to peers?
		virtual void quit(void) = 0;

		// use state instead?
		// toxic game states:
		//  - none
		//  - paused
		//  - running
		//  - finished
		//  - invalid
		virtual bool allInvitesAccepted(void) = 0;

		virtual void onPacket(uint32_t from, const uint8_t* data, const uint32_t data_size) = 0;

		// ??
		//virtual void tick();
	};

	virtual uint8_t getGameType(void) const = 0;

	// with (contact list, (in turn order?))
	// sends out invites
	virtual std::unique_ptr<InstanceI> createGame(std::vector<uint32_t> with) = 0;

	// from
	// game id
	// with (contact list)
	virtual std::unique_ptr<InstanceI> acceptInvite(uint32_t from, uint32_t id) = 0;
};

