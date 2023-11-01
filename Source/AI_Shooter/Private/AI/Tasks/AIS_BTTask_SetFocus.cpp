// Copyright by Egor "Lorgord" Voronov

#include"AI/Tasks/AIS_BTTask_SetFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"


EBTNodeResult::Type UAIS_BTTask_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!IsValid(AICharacter) || !IsValid(Blackboard))
	{
		return EBTNodeResult::Failed;
	}

	AAIS_CharacterBase* CurrentTarget = Cast<AAIS_CharacterBase>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));

	if (!IsValid(CurrentTarget))
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = IsValid(CurrentTarget->FocusActor) ? CurrentTarget->FocusActor : CurrentTarget;
	
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_Pawn);

	if (!GetWorld()->LineTraceTestByObjectType(AICharacter->GetActorLocation(), TargetActor->GetActorLocation(), ECC_Pawn))
	{
		return EBTNodeResult::Failed;
	}
	
	AIController->SetFocus(TargetActor);
	return EBTNodeResult::Succeeded;
}
