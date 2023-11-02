// Copyright by Egor "Lorgord" Voronov


#include "AI/Decorators/AIS_BTDec_IsReloadNeeded.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"

bool UAIS_BTDec_IsReloadNeeded::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	
	if (!IsValid(AICharacter) || !IsValid(AICharacter->EquipmentComponent))
	{
		return false;
	}

	return AICharacter->EquipmentComponent->IsWeaponNeedsReload() && !AICharacter->EquipmentComponent->IsDoingSomeAction();
}
