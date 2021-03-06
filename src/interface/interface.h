#ifndef GUI_H
#define GUI_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "raylib/raylib.h"
#include "status.h"

#include "../kGui/kGui.h"
#include "../renderer/renderer.h"
#include "structs.h"

extern GUIState gui;

//--------------------------------------------------------------------------------------------------------------------//
// window                                                                                                             //
//--------------------------------------------------------------------------------------------------------------------//

Status initialise_interface();
Status terminate_interface();

//--------------------------------------------------------------------------------------------------------------------//
// main loop                                                                                                          //
//--------------------------------------------------------------------------------------------------------------------//

Status start_main_loop();

//--------------------------------------------------------------------------------------------------------------------//
// interface                                                                                                          //
//--------------------------------------------------------------------------------------------------------------------//

Status create_interface();
Status update_interface();
Status draw_additional_interface();

//--------------------------------------------------------------------------------------------------------------------//
// input                                                                                                              //
//--------------------------------------------------------------------------------------------------------------------//

Status procces_mouse_input();
Status procces_kb_input();

//--------------------------------------------------------------------------------------------------------------------//
// files and scripts                                                                                                  //
//--------------------------------------------------------------------------------------------------------------------//

char *get_root_folder();
Status get_files();

#endif