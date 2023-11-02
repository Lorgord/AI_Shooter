// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIS_BTTask_MoveToRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class AI_SHOOTER_API UAIS_BTTask_MoveToRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

	UAIS_BTTask_MoveToRandomLocation();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float InRadius = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector MoveUntilKeyIsTrue;

private:

	UPROPERTY()
	UBehaviorTreeComponent* BTComponent = nullptr;
	
	UPROPERTY()
	UBlackboardComponent* Blackboard = nullptr;

	UPROPERTY()
	FAIRequestID MoveRequestID;
};
