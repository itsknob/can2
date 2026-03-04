#pragma once

#include "can2.h"
#include <gui/scene_manager.h>

#include "gui/modules/variable_item_list.h"

/** Edit Data Simple Scene Indicies and Events */
// Input events
typedef enum {
    CAN2EditDataSimpleSaveEvent,
    CAN2EditDataSimpleNextEvent,
    CAN2EditDataSimpleTextInputEvent,
    CAN2EditDataSimpleByteInputEvent,
} CAN2EditDataSimpleInputEvent;

/** Send Data Scene Indicies and Events */
typedef enum {
    CAN2VariableListTextInputEvent,
    CAN2VariableListByteInputEvent,
} CAN2VariableListEvent;

typedef enum {
    CAN2VariableListItemDeviceId,
    CAN2VariableListItemDataLength,
    CAN2VariableListItemRawData,
} CANVariableListItem;

void can2_edit_data_simple_form_data_init(CAN2FormData* edit_data_simple_data);

/** Switch to Text Input **/
void can2_edit_data_simple_input_callback(void* context);

/** Life Cycle **/
void can2_edit_data_simple_scene_on_enter(void* context);
bool can2_edit_data_simple_scene_on_event(void* context, SceneManagerEvent event);
void can2_edit_data_simple_scene_on_exit(void* context);

/** Handle Items in Menu Changing **/
void can2_edit_data_simple_variable_item_changed(VariableItem* current_item);
void can2_edit_data_simple_variable_input_callback(void* context, uint32_t index);
