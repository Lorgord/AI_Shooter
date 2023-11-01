// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_Attack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"



EBTNodeResult::Type UAIS_BTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();


	if (!IsValid(AICharacter) || !IsValid(Blackboard)) return EBTNodeResult::Failed;

	AActor* CurrentTarget = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!IsValid(CurrentTarget))
	{
		AICharacter->StopShooting();
		return EBTNodeResult::Failed;
	}

	const float Distance = FVector::Dist(CurrentTarget->GetActorLocation(), AICharacter->GetActorLocation());

	if (Distance > MaxFireDistance)
	{
		AICharacter->StopShooting();
		return EBTNodeResult::Failed;
	}

	AICharacter->StartShooting();
	
	return EBTNodeResult::Succeeded;
}
