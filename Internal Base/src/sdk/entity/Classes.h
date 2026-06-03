#pragma once
#include <cstdint>
#include "../memory/Offsets.h"
#include "../utils/Vector.h"

#define SCHEMA(type, name, offset) \
    type name() const { \
        return *reinterpret_cast<const type*>(reinterpret_cast<uintptr_t>(this) + offset); \
    }

template<class T>
struct CUtlVector
{
    uint64_t    count;
    T*          data;
};

class CGameSceneNode
{
public:
    SCHEMA(uintptr_t, m_modelState, Offsets::m_modelState);
    SCHEMA(Vector, m_vecOrigin, Offsets::m_vecOrigin);
};

class C_Player_ObserverServices {
public:
    SCHEMA(uint32_t, m_hObserverTarget, Offsets::m_hObserverTarget);
};

class C_BaseEntity
{
public:
    SCHEMA(int, m_iHealth, Offsets::m_iHealth);
    SCHEMA(int, m_iTeamNum, Offsets::m_iTeamNum);
    SCHEMA(Vector, m_vOldOrigin, Offsets::m_vOldOrigin);
    SCHEMA(uintptr_t, m_pGameSceneNode, Offsets::m_pGameSceneNode);

    bool IsAlive() const { return m_iHealth() > 0; }
};

class CCSPlayerBase_CameraServices {
public:
    SCHEMA(uint32_t, m_iFOV, Offsets::m_iFOV);
};

class C_CSPlayerPawn : public C_BaseEntity
{
public:
    SCHEMA(Vector, m_vecViewOffset, Offsets::m_vecViewOffset);
    SCHEMA(int, m_iShotsFired, Offsets::m_iShotsFired);
    SCHEMA(Vector, m_aimPunchAngle, Offsets::m_aimPunchAngle);
    SCHEMA(float, m_flViewmodelFOV, Offsets::m_flViewmodelFOV);
    SCHEMA(uintptr_t, m_pObserverServices, Offsets::m_pObserverServices);
    SCHEMA(uintptr_t, m_pCameraServices, Offsets::m_pCameraServices);
    SCHEMA(Vector, v_angle, Offsets::v_angle);
    SCHEMA(CUtlVector<Vector>, m_aimPunchCache, Offsets::m_aimPunchCache);
};

class C_CSPlayerController : public C_BaseEntity
{
public:
    SCHEMA(uint32_t, m_hPlayerPawn, Offsets::m_hPlayerPawn);
    SCHEMA(const char*, m_iszPlayerName, Offsets::m_iszPlayerName);
    SCHEMA(bool, m_bPawnIsAlive, Offsets::m_bPawnIsAlive);
};