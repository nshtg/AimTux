#include "fovchanger.h"

bool Settings::FOVChanger::enabled = false;
bool Settings::FOVChanger::ignore_scope = true;
float Settings::FOVChanger::value = 100.f;

bool Settings::FOVChanger::viewmodel_enabled = false;
float Settings::FOVChanger::viewmodel_value = 90.f;

void FOVChanger::RenderView(CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
	if (!Settings::FOVChanger::enabled && !Settings::FOVChanger::viewmodel_enabled)
			return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (!localplayer->GetAlive())
	{
		if (*localplayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && localplayer->GetObserverTarget())
			localplayer = (C_BasePlayer*) entitylist->GetClientEntityFromHandle(localplayer->GetObserverTarget());

		if (!localplayer)
			return;
	}

	if (Settings::FOVChanger::enabled && (Settings::FOVChanger::ignore_scope ? !localplayer->IsScoped() : true))
		setup.fov = Settings::FOVChanger::value;

	if (Settings::FOVChanger::viewmodel_enabled && (Settings::FOVChanger::ignore_scope ? !localplayer->IsScoped() : true))
		setup.fovViewmodel = Settings::FOVChanger::viewmodel_value;
}