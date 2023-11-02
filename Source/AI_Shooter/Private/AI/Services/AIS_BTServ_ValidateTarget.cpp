// Copyright by Egor "Lorgord" Voronov


#include "AI/Services/AIS_BTServ_ValidateTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAIS_BTServ_ValidateTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn<APawn>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!IsValid(AIPawn) || !IsValid(Blackboard))
	{
		return;
	}

	const AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!IsValid(TargetActor))
	{
		Blackboard->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
		return;
	}

	const float Distance = FVector::Dist(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());

	if (Distance > MaxDistance)
	{
		Blackboard->SetValueAsObject(TargetKey.SelectedKeyName, nullptr);
		return;
	}
}
