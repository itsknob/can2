#include "can2.h"
#include "read_data.h"

/** Read Data Scene Indicies and Events */
// TODO: add any events or menu options here

// Read Data
void can2_read_data_scene_on_enter(void* context) {
    App* app = context;
    text_box_reset(app->text_box);
    text_box_set_text(app->text_box, "Loading CAN Data");
    view_dispatcher_switch_to_view(app->view_dispatcher, CAN2TextBoxView);
    // todo: update this with to better handle displaying streaming data
    /**
     *  while (!back_button_pressed) {
     *      update app_state buffer with new data
     *      call text_box_set_text with data from buffer
     *      check if button pressed??
     *  }
     *
     *  OR 
     *
     *  while (!back_button_pressed) {
     *      send custom update event to can2_read_data_scene_on_event and handle there
     *  }
     */
}
bool can2_read_data_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // event not handled
}
void can2_read_data_scene_on_exit(void* context) {
    App* app = context;
    text_box_reset(app->text_box);
}
