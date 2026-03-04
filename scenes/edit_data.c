#include "can2.h"
#include "gui/modules/variable_item_list.h"
#include "edit_data.h"

// TODO: Update entire allocation process using correct data types
void can2_edit_data_simple_form_data_init(CAN2FormData* edit_data_simple_data) {
    // Device ID
    edit_data_simple_data->form_inputs[0]->form_input_value = "000";
    // Data Length
    edit_data_simple_data->form_inputs[1]->form_input_value = "8";
    // Raw Data (hex)
    edit_data_simple_data->form_inputs[2]->form_input_value = "0x000000";
}

void can2_edit_data_simple_input_callback(void* context) {
    App* app = context;

    scene_manager_handle_custom_event(app->scene_manager, CAN2EditDataSimpleSaveEvent);
}

struct AppContextWithCurrentItem {
    App* app;
    VariableItem* current_item;
};

// Edit Data Simple
void can2_edit_data_simple_scene_on_enter(void* context) {
    /**
        Options:
      - Label: Device ID Input (Required)
        Type: ByteInput
      - Label: Data Length Code (DLC) (Optional)
        Type: TextInput # Maybe Just a selection from a list. Maybe this is in the config menu?
      - Label: Raw Message Data Input (Required)
        Type: ByteInput
    */
    App* app = context;
    bool clear_text = true;
    text_input_reset(app->text_input);
    text_input_set_header_text(app->text_input, "Device Identifier (DID)");
    text_input_set_result_callback(
        app->text_input,
        can2_edit_data_simple_input_callback,
        app,
        app->form_data->form_inputs[app->form_data->current_input_number]->form_input_value,
        app->form_data->form_inputs[app->form_data->current_input_number]->form_input_size,
        clear_text);

    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2TextInputView);
}
bool can2_edit_data_simple_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // event not handled
}
void can2_edit_data_simple_scene_on_exit(void* context) {
    UNUSED(context);
}

// TODO: add any events or menu options here
void can2_edit_data_simple_variable_item_changed(VariableItem* current_item) {
    App* app = variable_item_get_context(current_item);
    uint8_t current_index = variable_item_get_current_value_index(current_item);

    variable_item_set_current_value_text(
        current_item, app->edit_data_simple_data->form_inputs[current_index]->form_input_value);
}

// Set current item index on app state and open text input
void can2_edit_data_simple_variable_input_callback(void* context, uint32_t index) {
    App* app = context;
    app->edit_data_simple_data->current_input_number = index;
    // open text input view -> update app->form_data->form_input[1
    scene_manager_handle_custom_event(app->scene_manager, CAN2VariableListTextInputEvent);
}
