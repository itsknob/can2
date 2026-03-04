#include "core/core_defines.h"
#include <gui/scene_manager.h>

// Config Menu
void can2_config_menu_scene_on_enter(void* context) {
    UNUSED(context);
}
bool can2_config_menu_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // event not handled
}
void can2_config_menu_scene_on_exit(void* context) {
    UNUSED(context);
}
