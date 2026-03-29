#include "globals.hpp"
#include <hyprland/src/config/ConfigManager.hpp>
#include <hyprland/src/desktop/DesktopTypes.hpp>
#include <hyprland/src/desktop/Workspace.hpp>
#include "nstackLayout.hpp"
#include <unistd.h>
#include <thread>
// Methods
inline std::unique_ptr<Layout::Tiled::CHyprNstackAlgorithm> g_pNstackLayout;

// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:orientation", Hyprlang::STRING{"left"});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:new_on_top", Hyprlang::INT{0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:new_is_master", Hyprlang::INT{1});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:no_gaps_when_only", Hyprlang::INT{0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:special_scale_factor", Hyprlang::FLOAT{0.8f});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:inherit_fullscreen", Hyprlang::INT{1});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:stacks", Hyprlang::INT{2});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:center_single_master", Hyprlang::INT{0});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:mfact", Hyprlang::FLOAT{0.5f});
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:nstack:layout:single_mfact", Hyprlang::FLOAT{0.5f});
    g_pNstackLayout  = std::make_unique<Layout::Tiled::CHyprNstackAlgorithm>();
	  if (!HyprlandAPI::addTiledAlgo(PHANDLE, "nStack", &typeid(Layout::Tiled::CHyprNstackAlgorithm), [] { return makeUnique<Layout::Tiled::CHyprNstackAlgorithm>(); })) {
			HyprlandAPI::addNotification(PHANDLE, "[hyprgollum] addTiledAlgo failed! Can't proceed.", CHyprColor{1.0, 0.2, 0.2, 1.0}, 5000);
    }
    HyprlandAPI::reloadConfig();

    return {"hyprNStack", "Plugin for column layout", "Zakk", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    HyprlandAPI::invokeHyprctlCommand("seterror", "disable");
}
