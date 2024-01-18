#include <solanaceae/plugin/solana_plugin_v1.h>

#include <solanaceae/toxic_games/toxic_games.hpp>
#include <solanaceae/toxcore/tox_interface.hpp>

#include <memory>
#include <limits>
#include <iostream>

static std::unique_ptr<ToxicGames> g_tg = nullptr;

constexpr const char* plugin_name = "ToxicGames";

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return plugin_name;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN " << plugin_name << " START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	try {
		auto* cr = PLUG_RESOLVE_INSTANCE_VERSIONED(Contact3Registry, "1");
		auto* t = PLUG_RESOLVE_INSTANCE(ToxI);
		auto* tep = PLUG_RESOLVE_INSTANCE(ToxEventProviderI);
		auto* tcm = PLUG_RESOLVE_INSTANCE(ToxContactModel2);

		// static store, could be anywhere tho
		// construct with fetched dependencies
		g_tg = std::make_unique<ToxicGames>(*cr, *t, *tep, *tcm);

		// register types
		PLUG_PROVIDE_INSTANCE(ToxicGames, plugin_name, g_tg.get());
	} catch (const ResolveException& e) {
		std::cerr << "PLUGIN " << plugin_name << " " << e.what << "\n";
		return 2;
	}

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN " << plugin_name << " STOP()\n";

	g_tg.reset();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_tick(float delta) {
	(void)delta;
	//g_tg->iterate();
	return std::numeric_limits<float>::max();
}

} // extern C

