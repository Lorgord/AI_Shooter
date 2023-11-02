// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIS_BTTask_ReloadWeapon.generated.h"

/**
 * 
 */
UCLASS()
class AI_SHOOTER_API UAIS_BTTask_ReloadWeapon : public UBTTaskNode
{
	GENERATED_BODY()

	UAIS_BTTask_ReloadWeapon();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnReloadFinished();

private:

	UPROPERTY()
	UBehaviorTreeComponent* BTComponent = nullptr;
};