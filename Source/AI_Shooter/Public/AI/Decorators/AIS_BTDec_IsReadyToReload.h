// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AIS_BTDec_IsReadyToReload.generated.h"

/**
 * 
 */
UCLASS()
class AI_SHOOTER_API UAIS_BTDec_IsReadyToReload : public UBTDecorator
{
	GENERATED_BODY()


	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
