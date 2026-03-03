#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/menu.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_box.h>
#include <gui/modules/text_input.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/dialog_ex.h>

/** Enums **/

/* Scenes and Views */
typedef enum {
    CAN2MainMenuScene,
    CAN2ReadDataScene,
    CAN2SendDataScene,
    CAN2EditDataSimpleScene,
    CAN2EditDataAdvancedScene,
    CAN2ConfigMenuScene,
    CAN2ConfigReadScene,
    CAN2ConfigSendScene,
    CAN2SceneCount
} CAN2Scene;

typedef enum {
    CAN2MenuView,
    CAN2SubMenuView,
    CAN2TextInputView,
    CAN2ByteInputView,
    CAN2TextBoxView,
    CAN2VariableItemListView,
    CAN2DialogView,
    CAN2WidgetView,
} CAN2View;

/** Data Structs **/
/* Single Input */
typedef struct {
    char* form_input_value;
    uint8_t form_input_size;
} CAN2FormInput;

/* Form Data Struct - Multiple Input Container */
typedef struct {
    uint8_t current_input_number;
    CAN2FormInput* form_inputs[];
} CAN2FormData;

typedef struct App {
    // Gui Management
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    // GUI Module
    Menu* menu;
    Submenu* submenu;
    TextInput* text_input;
    ByteInput* byte_input;
    TextBox* text_box;
    VariableItemList* variable_item_list;
    VariableItem* current_item;
    DialogEx* dialog;
    Widget* widget;

    // Data
    CAN2FormData* current_input;
    CAN2FormData* form_data;
    CAN2FormData* edit_data_simple_data;
} App;
