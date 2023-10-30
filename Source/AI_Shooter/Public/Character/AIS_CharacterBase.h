// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIS_CharacterBase.generated.h"

UCLASS()
class AI_SHOOTER_API AAIS_CharacterBase : public ACharacter
{
	GENERATED_BODY()
	
//constructor
public:

	AAIS_CharacterBase();

//c++ protected methods
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Character|Death")
	void OnCharacterDeath();
	

//Blueprint values
public:

//.....................................................Components.....................................................//

	UPROPERTY(BlueprintReadOnly, Category = "Character|Components")
	class UAIS_CharacterAttributesComponent* AttributesComponent = nullptr;

//....................................................................................................................//
};
