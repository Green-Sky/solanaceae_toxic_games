#pragma once

#include "../toxic_game_i.hpp"

struct Chess final : public ToxicGameI {
	Chess(ToxicGames& tg);
	~Chess(void);

	// TODO: extract?
	struct Coords {
		int32_t x {};
		int32_t y {};
	};
	struct ChessCoords {
		char L {};
		uint8_t N {};
	};

	struct ChessInstance final : public ToxicGameI::InstanceI {
		Chess& _game_type_static;

		const uint32_t _opponent;

		ChessInstance(Chess& game_type_static, uint32_t opponent, uint32_t game_id);
		~ChessInstance(void) {}

		// TODO: just destructor?
		// needs to send quit to peers?
		void quit(void) override;

		bool allInvitesAccepted(void) override;

		void onPacket(uint32_t from, const uint8_t* data, const uint32_t data_size) override;

		// ??
		//virtual void tick();

		//private:
			//bool sendResign(void);
			//bool sendMove(ChessCoords p0, ChessCoords p1);

		// the toxic game stuff
		int game_x_left_bound(void);
		int game_x_right_bound(void);
		int game_y_top_bound(void);
		int game_y_bottom_bound(void);
		int game_set_window_shape(/*shape*/);
	};

	uint8_t getGameType(void) const override { return 1; };

	std::unique_ptr<InstanceI> createGame(std::vector<uint32_t> with) override;
	std::unique_ptr<InstanceI> acceptInvite(uint32_t from, uint32_t game_id) override;

	//private:
		//bool sendAcceptInvite(uint32_t to, uint32_t game_id);
};

