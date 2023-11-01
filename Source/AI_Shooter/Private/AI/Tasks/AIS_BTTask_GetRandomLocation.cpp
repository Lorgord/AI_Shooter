// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_GetRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"

EBTNodeResult::Type UAIS_BTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!IsValid(AICharacter) || !IsValid(Blackboard))
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!IsValid(NavSystem))
	{
		return EBTNodeResult::Failed;
	}
	
	FNavLocation RandomLocation;
	NavSystem->GetRandomReachablePointInRadius(AICharacter->GetActorLocation(), InRadius, RandomLocation);

	if (RandomLocation.Location == FVector::ZeroVector)
	{
		return EBTNodeResult::Failed;
	}
	
	Blackboard->SetValueAsVector(ResultKey.SelectedKeyName, RandomLocation.Location);

	return EBTNodeResult::Succeeded;
}
