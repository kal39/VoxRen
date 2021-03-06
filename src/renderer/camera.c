#include "renderer.h"

int sign(float a) {
	return a < 0 ? -1 : 1;
}

Status set_camera_properties(float sensorWidth, float focalLength, float aperture, float exposure) {
	ren.camera.sensorWidth = sensorWidth;
	ren.camera.focalLength = focalLength;
	ren.camera.aperture = aperture;
	ren.camera.exposure = exposure;

	return SUCCESS;
}

Status set_camera_pos(float x, float y, float z, float rx, float ry) {
	ren.camera.pos = (cl_float3){.x = x, .y = y, .z = z};
	ren.camera.rot = (cl_float2){.x = rx, .y = ry};

	while (1) {
		if (abs(ren.camera.rot.x) > 2 * M_PI) ren.camera.rot.x -= 2 * M_PI * sign(ren.camera.rot.x);
		else break;
	}

	while (1) {
		if (abs(ren.camera.rot.y) > 2 * M_PI) ren.camera.rot.y -= 2 * M_PI * sign(ren.camera.rot.y);
		else break;
	}

	if (ren.camera.rot.y < -M_PI / 2) ren.camera.rot.y = -M_PI / 2;
	if (ren.camera.rot.y > M_PI / 2) ren.camera.rot.y = M_PI / 2;

	if (ren.camera.rot.x < -M_PI) ren.camera.rot.x = 2 * M_PI + ren.camera.rot.x;
	if (ren.camera.rot.x > M_PI) ren.camera.rot.x = -2 * M_PI + ren.camera.rot.x;

	return SUCCESS;
}

Status set_mouse_pos(int x, int y) {
	ren.mousePos.x = x;
	ren.mousePos.y = y;

	return SUCCESS;
}

VoxMaterial *get_material_at_mouse() {
	for (int i = 0; i < ren.scene.voxelCount; i++) {
		Voxel *v = &ren.scene.voxels[i];
		if (v->pos.x == ren.lookingAtPos.x && v->pos.y == ren.lookingAtPos.y && v->pos.z == ren.lookingAtPos.z)
			return &v->material;
	}

	return NULL;
}

Status add_voxel_at_mouse(VoxMaterial material) {
	if (ren.scene.voxelCount == 0) {
		dbg("Adding voxel (0, 0, 0)");
		add_voxel(0, 0, 0, material);
		return FAILURE;
	}

	if (ren.lookingAt) {
		int x = ren.lookingAtPos.x + ren.lookingAtNormal.x;
		int y = ren.lookingAtPos.y + ren.lookingAtNormal.y;
		int z = ren.lookingAtPos.z + ren.lookingAtNormal.z;

		dbg("Adding voxel (%d, %d, %d)", x, y, z);
		add_voxel(x, y, z, material);
	}

	return SUCCESS;
}

Status remove_voxel_at_mouse(VoxMaterial material) {
	if (ren.lookingAt) {
		dbg("Removing voxel (%d, %d, %d)", ren.lookingAtPos.x, ren.lookingAtPos.y, ren.lookingAtPos.z);
		remove_voxel(ren.lookingAtPos.x, ren.lookingAtPos.y, ren.lookingAtPos.z);
	}

	return SUCCESS;
}