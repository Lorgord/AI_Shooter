// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISense.h"
#include "AIS_AIControllerBase.generated.h"



UCLASS()
class AI_SHOOTER_API AAIS_AIControllerBase : public AAIController
{
	GENERATED_BODY()

public:

	AAIS_AIControllerBase();

public:

	virtual void SetPawn(APawn* InPawn) override;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath) override;


protected:

	AActor* GetClosestSensedActor(TSubclassOf<UAISense> SensedClass) const;

	void TryFindNextTarget();

private:
	
	UPROPERTY()
	class AAIS_AICharacter* OwningAICharacter = nullptr;
	
};
