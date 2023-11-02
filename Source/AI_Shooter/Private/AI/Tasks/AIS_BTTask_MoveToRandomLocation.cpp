// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_MoveToRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Navigation/PathFollowingComponent.h"

UAIS_BTTask_MoveToRandomLocation::UAIS_BTTask_MoveToRandomLocation()
{
	bCreateNodeInstance = true;
	bNotifyTick = true;
}

EBTNodeResult::Type UAIS_BTTask_MoveToRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	Blackboard = OwnerComp.GetBlackboardComponent();

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

	BTComponent = &OwnerComp;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(RandomLocation.Location);

	FPathFollowingRequestResult RequestResult = AIController->MoveTo(MoveRequest);

	MoveRequestID = RequestResult.MoveId;
	
	AIController->ReceiveMoveCompleted.AddDynamic(this, &UAIS_BTTask_MoveToRandomLocation::OnMoveCompleted);

	return EBTNodeResult::InProgress;
}


void UAIS_BTTask_MoveToRandomLocation::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (IsValid(BTComponent) && (int)MoveRequestID.GetID() == (int)RequestID.GetID())
	{
		BTComponent->GetAIOwner()->ReceiveMoveCompleted.RemoveDynamic(this, &UAIS_BTTask_MoveToRandomLocation::OnMoveCompleted);
		FinishLatentTask(*BTComponent, EBTNodeResult::Succeeded);
	}
}

void UAIS_BTTask_MoveToRandomLocation::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!IsValid(Blackboard)) return;

	UObject* Target = Blackboard->GetValueAsObject(MoveUntilKeyIsTrue.SelectedKeyName);
	if (IsValid(Target))
	{
		BTComponent->GetAIOwner()->ReceiveMoveCompleted.RemoveDynamic(this, &UAIS_BTTask_MoveToRandomLocation::OnMoveCompleted);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
