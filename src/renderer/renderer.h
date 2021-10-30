#ifndef RENDERER_H
#define RENDERER_H

#include <k_tools/k_image.h>
#include <k_tools/k_opencl_util.h>
#include <k_tools/k_util.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "status.h"
#include "structs.h"

extern Renderer ren;

//--------------------------------------------------------------------------------------------------------------------//
// management                                                                                                         //
//--------------------------------------------------------------------------------------------------------------------//

Status create_renderer();
Status destroy_renderer();
Status begin_rendering();
Status end_rendering();
k_Image *get_image();

//--------------------------------------------------------------------------------------------------------------------//
// scene                                                                                                              //
//--------------------------------------------------------------------------------------------------------------------//

Status set_output_properties(int width, int height);
Status set_background_properties(float red, float green, float blue, float brightness);
Status add_voxel(int x, int y, int z, VoxMaterial material);
Status remove_voxel(int x, int y, int z);

//--------------------------------------------------------------------------------------------------------------------//
// camera                                                                                                             //
//--------------------------------------------------------------------------------------------------------------------//

Status set_camera_properties(float sensorWidth, float focalLength, float aperture, float exposure);
Status set_camera_pos(float x, float y, float z, float rx, float ry);
Status set_mouse_pos(int x, int y);
VoxMaterial *get_material_at_mouse();
Status add_voxel_at_mouse(VoxMaterial material);
Status remove_voxel_at_mouse();

//--------------------------------------------------------------------------------------------------------------------//
// materials                                                                                                          //
//--------------------------------------------------------------------------------------------------------------------//

VoxMaterial create_light_source_material(float r, float g, float b, float brightness);
VoxMaterial create_lambertian_material(float r, float g, float b);
VoxMaterial create_metal_material(float r, float g, float b, float tint, float fuzz);
VoxMaterial create_dielectric_material(float r, float g, float b, float tint, float fuzz, float refIdx);

#endif
