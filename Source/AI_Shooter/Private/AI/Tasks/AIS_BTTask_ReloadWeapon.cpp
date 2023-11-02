// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_ReloadWeapon.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"
#include "Items/Weapons/RangeWeapon/AIS_RangeWeapon.h"


UAIS_BTTask_ReloadWeapon::UAIS_BTTask_ReloadWeapon()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UAIS_BTTask_ReloadWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();

	BTComponent = &OwnerComp;
	
	if (!IsValid(AICharacter))
	{
		return EBTNodeResult::Failed;
	}

	AICharacter->Crouch();
	AICharacter->StartReloading();

	if (!IsValid(AICharacter->EquipmentComponent) || !IsValid(AICharacter->EquipmentComponent->RangeWeapon))
	{
		return EBTNodeResult::Succeeded;
	}

	AICharacter->EquipmentComponent->RangeWeapon->OnWeaponStopReload.AddDynamic(this, &UAIS_BTTask_ReloadWeapon::OnReloadFinished);

	return EBTNodeResult::InProgress;
}

void UAIS_BTTask_ReloadWeapon::OnReloadFinished()
{
	if (IsValid(BTComponent))
	{
		BTComponent->GetAIOwner()->GetPawn<AAIS_AICharacter>()->EquipmentComponent->RangeWeapon->OnWeaponStopReload.RemoveDynamic(this, &UAIS_BTTask_ReloadWeapon::OnReloadFinished);
		FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
	}
}

