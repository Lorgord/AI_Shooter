// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIS_BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class AI_SHOOTER_API UAIS_BTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

	UAIS_BTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void OnAttackCompleted();

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxFireDistance = 800.0f;

private:

	UPROPERTY()
	UBehaviorTreeComponent* BTComponent = nullptr;

	UPROPERTY()
	class AAIS_AICharacter* AICharacter = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;
	
};
