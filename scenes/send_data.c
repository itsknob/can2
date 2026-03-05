#include "can2.h"
#include "edit_data.h"
#include "gui/modules/byte_input.h"
#include "gui/modules/variable_item_list.h"
#include "gui/view_dispatcher.h"
#include "send_data.h"

/**
* 1. Send Data Screen 
*   - Form
*       - Labels
*       - Values
*   - Up/Down Buttons
*       - Navigate between Form Inputs
*   - Center Button
*       - Edit Value for Label (2)
*   - Right Button
*       - Go to Filter (3)
*   - Left Button
*       - Go to Config (4)
* 2. Edit Data Screen
*   - TextInput View
*       - Save -> Go to Send Data Screen (1)
*   - NumberInput View
*       - Save -> Go to Send Data Screen (1)
*   - ByteInput View
*       - Save -> Go to Send Data Screen (1)
*   - Back Button
*       - Go to Send Data Screen (1)
* 3. Filter Screen
*   - List of IDs already in filter list?
*       - Last Row is "+ Add Entry"
*   - Up/Down Buttons
*       - Navigate between Form Inputs
*   - Center Button
*       - On populated row
*           - Confirmation Popup
*               - Right Button
*                   - Delete -> Go to Filter Screen (3)
*               - Left Button
*                   - Cancel -> Go to Filter Screen (3)
*               - Back Button
*                   - Cancel -> Go to Filter Screen (3)
*       - On "+ Add Entry" Row
*           - NumberInput?
*               - Save -> Go to Filter Screen (3)
*       
**/

void can2_send_data_scene_render(void* context) {
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
/** When switching to the Send Data Scene 
 * First set up the View
 * Then Switch to it
 **/
void can2_send_data_scene_on_enter(void* context) {
    App* app = context;

    // (Re)Render Scene
    can2_send_data_scene_render(app);

    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2VariableItemListView);
}

// Callback to return to variable_item_list_view from text input?
// Move the curren_input value into the correct edit_data_simple_data-form data value
void can2_send_data_input_callback(void* context) {
    App* app = context;

    // Get currently selected Variable Item List index
    uint8_t current_item_index =
        variable_item_list_get_selected_item_index(app->variable_item_list);

    // Update corresponding data field with text_input's data
    app->edit_data_simple_data->form_inputs[current_item_index]->form_input_value =
        app->current_input->form_inputs[0]->form_input_value;

    // Recreate GUI with data from edit_data_simple_data
    can2_send_data_scene_render(app);

    // return to variable_item_list view
    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2VariableItemListView);

    // reset CAN2FormData's buffer for app->current_input-
    app->current_input->form_inputs[current_item_index]->form_input_value = "";
}

bool can2_send_data_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    char* prompt_text = "Device ID";
    uint8_t current_index = app->edit_data_simple_data->current_input_number;
    bool consumed = false;

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

    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case CAN2VariableListTextInputEvent:
            // Set up Text Input Scene
            text_input_reset(app->text_input);
            text_input_set_header_text(app->text_input, prompt_text);
            text_input_set_result_callback(
                app->text_input,
                can2_send_data_input_callback,
                app,
                app->edit_data_simple_data->form_inputs[current_index]->form_input_value,
                app->edit_data_simple_data->form_inputs[current_index]->form_input_size,
                true);
            view_dispatcher_switch_to_view(app->view_dispatcher, CAN2TextInputView);
            consumed = true;
            break;
        case CAN2VariableListByteInputEvent:
            // NOTE: Is there a reset for byte_input?
            byte_input_set_header_text(app->byte_input, "Raw Data");
            byte_input_set_result_callback(
                app->byte_input,
                can2_send_data_input_callback,
                can2_send_data_scene_render,
                app,
                (unsigned char*)app->edit_data_simple_data
                    ->form_inputs[app->edit_data_simple_data->current_input_number]
                    ->form_input_value,
                app->edit_data_simple_data
                    ->form_inputs[app->edit_data_simple_data->current_input_number]
                    ->form_input_size);
            view_dispatcher_switch_to_view(app->view_dispatcher, CAN2ByteInputView);
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
