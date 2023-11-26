#include "./chess.hpp"

Chess::Chess(ToxicGames& tg) : ToxicGameI(tg) {
}

Chess::~Chess(void) {
}

std::unique_ptr<Chess::InstanceI> Chess::createGame(std::vector<uint32_t> with) {
	return nullptr;
}

std::unique_ptr<Chess::InstanceI> Chess::acceptInvite(uint32_t from, uint32_t id) {
	return nullptr;
}

