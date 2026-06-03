#pragma once
#include <cstdint>

#include "../../../dumper/offsets.hpp"
#include "../../../dumper/client_dll.hpp"

namespace Offsets
{
    /*
     *  Update dumper/ with new offsets from git:a2x/cs2-dumper/output/
    */

    // -> offsets.h on a2x dumper
    constexpr uintptr_t dwEntityList = cs2_dumper::offsets::client_dll::dwEntityList;
    constexpr uintptr_t dwLocalPlayerPawn = cs2_dumper::offsets::client_dll::dwLocalPlayerPawn;
    constexpr uintptr_t dwViewMatrix = cs2_dumper::offsets::client_dll::dwViewMatrix;
    constexpr uintptr_t dwViewAngles = cs2_dumper::offsets::client_dll::dwViewAngles;

    
	// -> client.dll.hpp on a2x dumper -> C_BaseEntity 
    constexpr uintptr_t m_iHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth;
    constexpr uintptr_t m_iTeamNum = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum;
    constexpr uintptr_t m_vOldOrigin = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin;
    constexpr uintptr_t m_pGameSceneNode = cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode;

	// -> CbaseModelEntity
    constexpr uintptr_t m_vecViewOffset = cs2_dumper::schemas::client_dll::C_BaseModelEntity::m_vecViewOffset;

    // -> CGameSceneNode
    constexpr uintptr_t m_vecOrigin = cs2_dumper::schemas::client_dll::CGameSceneNode::m_vecOrigin;

    // -> C_BasePlayerPawn
    constexpr uintptr_t m_pCameraServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices;
    constexpr uintptr_t v_angle = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::v_angle;

    // -> CCSPlayerBase_CameraServices
    constexpr uintptr_t m_iFOV = cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOV;

	// -> C_CSPlayerPawn
    constexpr uintptr_t m_iShotsFired = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired;
    constexpr uintptr_t m_aimPunchAngle = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchAngle;
    constexpr uintptr_t m_aimPunchCache = 0x16F0;
    constexpr uintptr_t m_flViewmodelFOV = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_flViewmodelFOV;

	// -> C_CSPlayerController
    constexpr uintptr_t m_iszPlayerName = cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName;
    constexpr uintptr_t m_hPlayerPawn = cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn;
    constexpr uintptr_t m_bPawnIsAlive = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive;

	// -> CBodyComponentSkeletonInstance
    constexpr uintptr_t m_modelState = cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState;

	// -> CObserverServices
    constexpr ptrdiff_t m_pObserverServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pObserverServices;
    constexpr ptrdiff_t m_hObserverTarget = cs2_dumper::schemas::client_dll::CPlayer_ObserverServices::m_hObserverTarget;
	constexpr ptrdiff_t m_iObserverMode = cs2_dumper::schemas::client_dll::CPlayer_ObserverServices::m_iObserverMode;

}
