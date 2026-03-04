#pragma once

#include "gui/scene_manager.h"

void can2_variable_list_text_input_callback(void* context);
void can2_send_data_scene_on_enter(void* context);
bool can2_send_data_scene_on_event(void* context, SceneManagerEvent event);
void can2_send_data_scene_on_exit(void* context);
