#include "can2.h"
#include "main_menu.h"

/** Main Menu Scene Indicies and Events */
typedef enum {
    CAN2MainMenuSceneReadData,
    CAN2MainMenuSceneSendData,
    CAN2MainMenuSceneConfig,
} CAN2MainMenuSceneIndex;

typedef enum {
    CAN2MainMenuSceneReadDataEvent,
    CAN2MainMenuSceneSendDataEvent,
    CAN2MainMenuSceneConfigEvent,
} CAN2MainMenuEvent;

/** Menu Item Selection **/
// Fires Event Specific to Option Selected
// Events fired here are handled by `can2_main_menu_scene_on_event`
static void can2_menu_callback(void* context, uint32_t index) {
    App* app = context;
    switch(index) {
    case CAN2MainMenuSceneReadData:
        scene_manager_handle_custom_event(app->scene_manager, CAN2MainMenuSceneReadDataEvent);
        break;
    case CAN2MainMenuSceneSendData:
        scene_manager_handle_custom_event(app->scene_manager, CAN2MainMenuSceneSendDataEvent);
        break;
    case CAN2MainMenuSceneConfig:
        scene_manager_handle_custom_event(app->scene_manager, CAN2MainMenuSceneConfigEvent);
        break;
    }
}

/** Callbacks for each Scene **/
// Main Menu
void can2_main_menu_scene_on_enter(void* context) {
    App* app = context;

    // Use Submenu instead of Menu to include a Header/Title
    submenu_reset(app->submenu);

    // Set Title for Submenu
    submenu_set_header(app->submenu, "CAN Two");

    // Add Options that call general menu_callback Function
    // general menu_callback function handles which Custom SceneManagerEvent to fire
    submenu_add_item(
        app->submenu, "Read Data", CAN2MainMenuSceneReadData, can2_menu_callback, app);
    submenu_add_item(
        app->submenu, "Send Data", CAN2MainMenuSceneSendData, can2_menu_callback, app);
    submenu_add_item(app->submenu, "Settings", CAN2MainMenuSceneConfig, can2_menu_callback, app);

    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2SubMenuView);
    UNUSED(context);
}

// Handle Custom SceneManagerEvents fired by options within Scenes
// options in scenes are generally defined within the <scene>_on_enter functions
// optionn defined on those scenes are fired from the callback function specified in the definition
bool can2_main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    bool consumed = false;
    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case CAN2MainMenuSceneReadDataEvent:
            scene_manager_next_scene(app->scene_manager, CAN2ReadDataScene);
            consumed = true;
            break;
        case CAN2MainMenuSceneSendDataEvent:
            scene_manager_next_scene(app->scene_manager, CAN2SendDataScene);
            consumed = true;
            break;
        }
        break;
    default:
        break;
    }
    return consumed; // event not handled
}

// Clear the submenu so it can be reused by another view
void can2_main_menu_scene_on_exit(void* context) {
    App* app = context;
    submenu_reset(app->submenu);
}
