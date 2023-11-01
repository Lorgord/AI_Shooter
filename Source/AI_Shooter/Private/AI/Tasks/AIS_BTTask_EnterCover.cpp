// Copyright by Egor "Lorgord" Voronov


#include "AI/Tasks/AIS_BTTask_EnterCover.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"



EBTNodeResult::Type UAIS_BTTask_EnterCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	AAIS_AICharacter* AICharacter = AIController->GetPawn<AAIS_AICharacter>();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();


	if (!IsValid(AICharacter) || !IsValid(Blackboard))
	{
		return EBTNodeResult::Failed;
	}

	AICharacter->Crouch();
	AICharacter->StartReloading();

	return EBTNodeResult::Succeeded;
}
