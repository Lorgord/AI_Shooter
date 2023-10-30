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

//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Character|Battle")
	void StartShooting();
	
	UFUNCTION(BlueprintCallable, Category = "Character|Battle")
	void StopShooting();
	
	UFUNCTION(BlueprintCallable, Category = "Character|Battle")
	void StartReloading();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character|Death")
	void OnCharacterDeath();

	UFUNCTION(BlueprintCallable, Category = "Character|Death")
	FORCEINLINE bool CanUseEquipment() const { return !bIsCharacterDead; }
	

//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, Category = "Character|Death")
	bool bIsCharacterDead = false;
	

//.....................................................Components.....................................................//

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Components")
	class UAIS_CharacterAttributesComponent* AttributesComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Components")
	class UAIS_CharacterEquipmentComponent* EquipmentComponent = nullptr;

//....................................................................................................................//
};
