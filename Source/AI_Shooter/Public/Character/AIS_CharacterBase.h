// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "AIS_CharacterBase.generated.h"



UENUM(BlueprintType)
enum class ETeams : uint8
{
	Player,
	Red,
	Green,
	Blue
};



UCLASS()
class AI_SHOOTER_API AAIS_CharacterBase : public ACharacter, public IGenericTeamAgentInterface
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
	
	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(static_cast<uint8>(CharacterTeam)); }

//Blueprint values
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Team")
	ETeams CharacterTeam = ETeams::Red;
	
	UPROPERTY(VisibleInstanceOnly ,BlueprintReadOnly, Category = "Character|Death")
	bool bIsCharacterDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Sockets")
	FName FocusActorSocket = "AimFocus";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Focus")
	TSubclassOf<AActor> FocusActorClass = nullptr;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character|Focus")
	AActor* FocusActor = nullptr;

//.....................................................Components.....................................................//

		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Components")
	class UAIS_CharacterAttributesComponent* AttributesComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Components")
	class UAIS_CharacterEquipmentComponent* EquipmentComponent = nullptr;

//....................................................................................................................//
};
