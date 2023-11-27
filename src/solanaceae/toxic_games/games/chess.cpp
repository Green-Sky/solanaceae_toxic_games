#include "./chess.hpp"

#include "../toxic_games.hpp"

Chess::ChessInstance::ChessInstance(
	Chess& game_type_static,
	uint32_t game_id
) : _game_type_static(game_type_static) {
	_id = game_id;
}

void Chess::ChessInstance::quit(void) {
}

bool Chess::ChessInstance::allInvitesAccepted(void) {
	return false;
}

void Chess::ChessInstance::onPacket(uint32_t from, const uint8_t* data, const uint32_t data_size) {
}

Chess::Chess(ToxicGames& tg) : ToxicGameI(tg) {
}

Chess::~Chess(void) {
}

std::unique_ptr<Chess::InstanceI> Chess::createGame(std::vector<uint32_t> with) {
	return nullptr;
}

std::unique_ptr<Chess::InstanceI> Chess::acceptInvite(uint32_t from, uint32_t game_id) {
	sendAcceptInvite(from, game_id);

	auto new_instance = std::make_unique<ChessInstance>(*this, game_id);

	return new_instance;
}

bool Chess::sendAcceptInvite(uint32_t to, uint32_t game_id) {
	std::vector<uint8_t> pkg;

	// init accept invite (chess specific)
	pkg.push_back(0x02);
	return _tg.sendPacket(static_cast<Contact3>(to), getGameType(), game_id, pkg.data(), pkg.size());
}

