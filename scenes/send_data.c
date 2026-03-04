#include "can2.h"
#include "edit_data.h"
#include "gui/modules/variable_item_list.h"
#include "send_data.h"

void render_send_data_gui(void* context) {
    App* app = context;

    variable_item_list_reset(app->variable_item_list);
    VariableItem* item_device_id = variable_item_list_add(
        app->variable_item_list,
        "Device ID  ",
        1,
        can2_edit_data_simple_variable_item_changed,
        app);

    VariableItem* item_data_length = variable_item_list_add(
        app->variable_item_list,
        "Data Length",
        1,
        can2_edit_data_simple_variable_item_changed,
        app);

    VariableItem* item_raw_data = variable_item_list_add(
        app->variable_item_list,
        "Raw Data   ",
        1,
        can2_edit_data_simple_variable_item_changed,
        app);

    // // TODO: use default values from config file?
    // app->form_data->form_inputs[0]->form_input_value = "000";
    // app->form_data->form_inputs[1]->form_input_value = "8";
    // app->form_data->form_inputs[2]->form_input_value = "0x000000";

    variable_item_set_current_value_text(
        item_device_id, app->edit_data_simple_data->form_inputs[0]->form_input_value);
    variable_item_set_current_value_text(
        item_data_length, app->edit_data_simple_data->form_inputs[1]->form_input_value);
    variable_item_set_current_value_text(
        item_raw_data, app->edit_data_simple_data->form_inputs[2]->form_input_value);

    variable_item_set_current_value_index(item_device_id, CAN2VariableListItemDeviceId);
    variable_item_set_current_value_index(item_data_length, CAN2VariableListItemDataLength);
    variable_item_set_current_value_index(item_raw_data, CAN2VariableListItemRawData);

    variable_item_list_set_enter_callback(
        app->variable_item_list, can2_edit_data_simple_variable_input_callback, app);
}

// Send Data
// Custom Form input via Widget Gui Module
void can2_send_data_scene_on_enter(void* context) {
    App* app = context;

    render_send_data_gui(app);

    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2VariableItemListView);
}

// Callback to return to variable_item_list_view from text input?
void can2_variable_list_text_input_callback(void* context) {
    App* app = context;

    // Get currently selected Variable Item List index
    uint8_t current_item_index =
        variable_item_list_get_selected_item_index(app->variable_item_list);

    // Update corresponding data field with text_input's data
    app->edit_data_simple_data->form_inputs[current_item_index]->form_input_value =
        app->current_input->form_inputs[0]->form_input_value;

    // Recreate GUI with data from edit_data_simple_data
    render_send_data_gui(app);

    // return to variable_item_list view
    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2VariableItemListView);

    // reset text_input's data
    app->current_input->form_inputs[current_item_index]->form_input_value = "";
}

bool can2_send_data_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    char* prompt_text = "Device ID";
    uint8_t current_index = app->edit_data_simple_data->current_input_number;
    bool consumed = false;

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case CAN2VariableListTextInputEvent:
            // Set up Input's Header Text for Currently Selected Option
            switch(current_index) {
            case 1:
                prompt_text = "Data Length";
                break;
            case 2:
                prompt_text = "Raw Data";
                break;
            case 0:
            default:
                prompt_text = "Device ID";
                break;
            }

            // Set up Text Input Scene
            text_input_reset(app->text_input);
            text_input_set_header_text(app->text_input, prompt_text);
            text_input_set_result_callback(
                app->text_input,
                can2_variable_list_text_input_callback,
                app,
                app->current_input->form_inputs[current_index]->form_input_value,
                app->current_input->form_inputs[current_index]->form_input_size,
                true);
            view_dispatcher_switch_to_view(app->view_dispatcher, CAN2TextInputView);
            consumed = true;
            break;
        default:
            break;
        }
    default:
        break;
    }
    return consumed;
}
void can2_send_data_scene_on_exit(void* context) {
    UNUSED(context);
}
