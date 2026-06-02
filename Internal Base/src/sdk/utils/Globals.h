#pragma once
#include <cstdint>
#include <Windows.h>

namespace Globals
{
    inline float ViewMatrix[16] = { 0.f };
    inline int ScreenWidth = 0;
    inline int ScreenHeight = 0;

    // ESP
    inline bool esp_enabled = true;
    inline int  esp_bind = VK_F1;

    inline bool esp_box = true;
    inline float esp_box_color[4] = { 1.f, 0.f, 0.f, 1.f };
    inline float esp_box_thickness = 1.5f;

    inline bool esp_skeleton = true;
    inline float esp_skeleton_color[4] = { 1.f, 1.f, 1.f, 0.9f };
    inline float esp_skeleton_thickness = 1.8f;

    inline bool esp_name = false;
    inline float esp_name_color[4] = { 1.f, 1.f, 1.f, 1.f };

    inline bool esp_health = true;

    // Aimbot
    inline bool aim_enabled = true;
    inline int  aim_bind = VK_F2;

    inline float aim_fov = 15.f;
    inline float aim_smooth = 25.f;

    inline bool aim_fov_visible = true;
    inline float aim_fov_color[4] = { 0.2f, 0.5f, 1.f, 0.6f };
    inline float aim_fov_thickness = 0.75f;

}
