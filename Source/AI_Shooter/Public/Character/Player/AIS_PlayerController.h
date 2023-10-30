// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AIS_PlayerController.generated.h"


class AAIS_PlayerCharacter;

UCLASS()
class AI_SHOOTER_API AAIS_PlayerController : public APlayerController
{
	GENERATED_BODY()

//constructor
public:

	AAIS_PlayerController();


//c++ protected methods
protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, Category = "PlayerController")
	AAIS_PlayerCharacter* MyCharacter = nullptr;
};
