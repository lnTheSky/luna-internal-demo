#include "Aimbot.h"

#include "../../../sdk/entity/EntityManager.h"
#include "../../../sdk/utils/Utils.h"
#include "../../../../ext/imgui/imgui.h"

void Aimbot::Render() {
	if (!Globals::aim_enabled) return;

	ImDrawList* dl = ImGui::GetBackgroundDrawList();
	const float sw = ImGui::GetIO().DisplaySize.x;
	const float sh = ImGui::GetIO().DisplaySize.y;

	const auto& entities = EntityManager::Get().GetEntities();
	C_CSPlayerPawn* localPawn = EntityManager::Get().GetLocalPawn();
	Vector* viewAngles = EntityManager::Get().GetViewAngles();


	if (!localPawn)
		return;

	const ImU32 fovCol = ImGui::ColorConvertFloat4ToU32(ImVec4(
		Globals::aim_fov_color[0], Globals::aim_fov_color[1],
		Globals::aim_fov_color[2], Globals::aim_fov_color[3]
	));

	if (Globals::aim_fov_visible) {
		CCSPlayerBase_CameraServices* camServices = reinterpret_cast<CCSPlayerBase_CameraServices*>(localPawn->m_pCameraServices());
		dl->AddCircle({ sw / 2, sh / 2 }, Utils::GetFovRadius(90.f, sw, sh, Globals::aim_fov), fovCol, 0, Globals::aim_fov_thickness);
	}

	if (Globals::aim_enabled) {
		static Vector oldAimPunch{ 0.f, 0.f, 0.f };
		Vector aimPunchAngle{ 0.f, 0.f, 0.f };
		Vector macroPunch{ 0.f, 0.f, 0.f };

		CUtlVector<Vector> cache = localPawn->m_aimPunchCache();

		if (cache.count > 0)
		{
			aimPunchAngle = cache.data[cache.count - 1];
		}

		Vector vecOrigin = reinterpret_cast<CGameSceneNode*>(localPawn->m_pGameSceneNode())->m_vecOrigin();
		Vector l_eyePos = vecOrigin + localPawn->m_vecViewOffset();
		Vector l_viewAngles = localPawn->v_angle();

		Vector l_viewAngleN;
		

		// AntiRecoil
		
		Vector curAimPunch = aimPunchAngle * 2.f;
		if (localPawn->m_iShotsFired() > 0)
		{
			macroPunch = oldAimPunch - curAimPunch;
			oldAimPunch = curAimPunch;
		}
		else {
			oldAimPunch = { 0.f, 0.f, 0.f };
		}
		Utils::AngleVectors(l_viewAngles + curAimPunch, l_viewAngleN);

		C_CSPlayerPawn* enemyPawn = nullptr;
		float min_fov = 1024.f;
		for (const auto& entity : entities) {
			if (!entity.isEnemy) continue;
			Vector vecOrigin = reinterpret_cast<CGameSceneNode*>(entity.pawn->m_pGameSceneNode())->m_vecOrigin();
			Vector e_eyePos = vecOrigin + entity.pawn->m_vecViewOffset();
			Vector toTarget = e_eyePos - l_eyePos;
			Utils::NormalizeVector(toTarget);
			float angle = RAD2DEG(abs(acos(std::clamp(Utils::Dot(l_viewAngleN, toTarget), -1.f, 1.f))));;
			if (angle < min_fov) {
				min_fov = angle;
				enemyPawn = entity.pawn;
			}
		}
		if (min_fov == 1024.f || min_fov > Globals::aim_fov)
		{
			//printf("%f", fov);
			// Change to mouse_events to be read-only
			l_viewAngles = l_viewAngles + macroPunch * 2.f;
			Utils::NormalizeAngles(l_viewAngles);
			*viewAngles = l_viewAngles;
			return;
		}

		Vector targetAngles = Utils::CalcAngle(l_eyePos, reinterpret_cast<CGameSceneNode*>(enemyPawn->m_pGameSceneNode())->m_vecOrigin() + enemyPawn->m_vecViewOffset());
		Vector deltaAngles = targetAngles - l_viewAngles;
		Utils::NormalizeAngles(deltaAngles);

		l_viewAngles += (deltaAngles - curAimPunch) * (1.f / Globals::aim_smooth) * powf(1.f - min_fov / Globals::aim_fov, 3.f);

		Utils::NormalizeAngles(l_viewAngles);

		// Change to mouse_events to be read-only
		*viewAngles = l_viewAngles;
	}

}