// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_Attack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"
#include "Items/Weapons/RangeWeapon/AIS_RangeWeapon.h"
#include "Kismet/KismetMathLibrary.h"


UAIS_BTTask_Attack::UAIS_BTTask_Attack()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UAIS_BTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	BTComponent = &OwnerComp;

	if (!IsValid(AICharacter) || !IsValid(Blackboard))
	{
		return EBTNodeResult::Failed;
	}
		
	TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}

	const float Distance = FVector::Dist(TargetActor->GetActorLocation(), AICharacter->GetActorLocation());

	if (Distance > MaxFireDistance)
	{
		return EBTNodeResult::Failed;
	}

	if (!IsValid(AICharacter->EquipmentComponent) || !IsValid(AICharacter->EquipmentComponent->RangeWeapon))
	{
		return EBTNodeResult::Failed;
	}

	AICharacter->StartShooting();
	AICharacter->EquipmentComponent->RangeWeapon->OnStoppedShooting.AddDynamic(this, &UAIS_BTTask_Attack::OnAttackCompleted);
	
	return EBTNodeResult::InProgress;
}

void UAIS_BTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!IsValid(AICharacter) || !IsValid(TargetActor)) return;
	
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector OwnerLocation = AICharacter->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(AICharacter);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, TargetLocation, ECC_Visibility, QueryParams))
	{
		if (HitResult.GetActor() != TargetActor->GetOwner())
		{
			AICharacter->StopShooting();
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
}

void UAIS_BTTask_Attack::OnAttackCompleted()
{
	if (IsValid(BTComponent))
	{
		BTComponent->GetAIOwner()->GetPawn<AAIS_AICharacter>()->EquipmentComponent->RangeWeapon->OnStoppedShooting.RemoveDynamic(this, &UAIS_BTTask_Attack::OnAttackCompleted);
		FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
	}
}
