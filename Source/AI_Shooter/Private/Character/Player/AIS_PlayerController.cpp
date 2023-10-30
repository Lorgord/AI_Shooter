// Copyright by Egor "Lorgord" Voronov


#include "AI_Shooter/Public/Character/Player/AIS_PlayerController.h"

#include "AI_Shooter/Public/Character/Player/AIS_PlayerCharacter.h"

AAIS_PlayerController::AAIS_PlayerController()
{
}

void AAIS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MyCharacter = Cast<AAIS_PlayerCharacter>(InPawn);
}

void AAIS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}
