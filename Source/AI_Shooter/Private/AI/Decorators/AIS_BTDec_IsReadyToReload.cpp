// Copyright by Egor "Lorgord" Voronov


#include "AI/Decorators/AIS_BTDec_IsReadyToReload.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"



bool UAIS_BTDec_IsReadyToReload::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!IsValid(AICharacter) || !IsValid(Blackboard) || !IsValid(AICharacter->EquipmentComponent))
	{
		return false;
	}

	return AICharacter->EquipmentComponent->IsWeaponNeedsReload() && !AICharacter->EquipmentComponent->IsDoingSomeAction();
}
