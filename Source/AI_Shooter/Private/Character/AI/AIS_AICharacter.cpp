// Copyright by Egor "Lorgord" Voronov


#include "Character/AI/AIS_AICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "AI/Controllers/AIS_AIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"


AAIS_AICharacter::AAIS_AICharacter()
{
}

void AAIS_AICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIS_AICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AIControllerBase = Cast<AAIS_AIControllerBase>(NewController);
}

void AAIS_AICharacter::OnCharacterDeath_Implementation()
{
	Super::OnCharacterDeath_Implementation();

	if (IsValid(AIControllerBase))
	{
		AIControllerBase->GetBrainComponent()->StopLogic("Death");
	}
}