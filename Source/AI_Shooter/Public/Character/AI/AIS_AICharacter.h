// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "Character/AIS_CharacterBase.h"
#include "AIS_AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class AI_SHOOTER_API AAIS_AICharacter : public AAIS_CharacterBase
{
	GENERATED_BODY()

public:

	AAIS_AICharacter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	virtual void OnCharacterDeath_Implementation() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AICharacter|BehaviorTree")
	UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class AAIS_AIControllerBase* AIControllerBase = nullptr;
};
