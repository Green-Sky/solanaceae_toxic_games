#include <solanaceae/plugin/solana_plugin_v1.h>

//#include <solanaceae/util/config_model.hpp>
#include <solanaceae/toxic_games/toxic_games.hpp>

#include <memory>
#include <iostream>

#define RESOLVE_INSTANCE(x) static_cast<x*>(solana_api->resolveInstance(#x))
#define PROVIDE_INSTANCE(x, p, v) solana_api->provideInstance(#x, p, static_cast<x*>(v))

static std::unique_ptr<ToxicGames> g_tg = nullptr;

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return "ToxicGames";
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN TG START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	//RegistryMessageModel* rmm = nullptr;
	//ConfigModelI* conf = nullptr;
	Contact3Registry* cr;
	ToxI* t;
	ToxEventProviderI* tep;
	ToxContactModel2* tcm;

	{ // make sure required types are loaded
		//rmm = RESOLVE_INSTANCE(RegistryMessageModel);
		//conf = RESOLVE_INSTANCE(ConfigModelI);
		cr = RESOLVE_INSTANCE(Contact3Registry);
		t = RESOLVE_INSTANCE(ToxI);
		tep = RESOLVE_INSTANCE(ToxEventProviderI);
		tcm = RESOLVE_INSTANCE(ToxContactModel2);

		if (cr == nullptr) {
			std::cerr << "PLUGIN TG missing Contact3Registry\n";
			return 2;
		}

		if (t == nullptr) {
			std::cerr << "PLUGIN TG missing ToxI\n";
			return 2;
		}

		if (tep == nullptr) {
			std::cerr << "PLUGIN TG missing ToxEventProviderI\n";
			return 2;
		}

		if (tcm == nullptr) {
			std::cerr << "PLUGIN TG missing ToxContactModel2\n";
			return 2;
		}
	}

	// static store, could be anywhere tho
	// construct with fetched dependencies
	g_tg = std::make_unique<ToxicGames>(*cr, *t, *tep, *tcm);

	// register types
	PROVIDE_INSTANCE(ToxicGames, "ToxicGames", g_tg.get());

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN TG STOP()\n";

	g_tg.reset();
}

SOLANA_PLUGIN_EXPORT void solana_plugin_tick(float delta) {
	(void)delta;
	//std::cout << "PLUGIN TG TICK()\n";
	//g_tg->iterate();
}

} // extern C

