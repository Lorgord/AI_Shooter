// Copyright by Egor "Lorgord" Voronov


#include "AI_Shooter/Public/GameMode/AIS_GameModeMain.h"

#include "AI_Shooter/Public/Character/Player/AIS_PlayerController.h"

AAIS_GameModeMain::AAIS_GameModeMain()
{
	PlayerControllerClass = AAIS_PlayerController::StaticClass();
}
