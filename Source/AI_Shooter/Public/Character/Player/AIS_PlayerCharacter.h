// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "AI_Shooter/Public/Character/AIS_CharacterBase.h"
#include "AIS_PlayerCharacter.generated.h"



class UInputAction;



UCLASS()
class AI_SHOOTER_API AAIS_PlayerCharacter : public AAIS_CharacterBase
{
	GENERATED_BODY()

//constructor
public:

	AAIS_PlayerCharacter();


//c++ protected methods
protected:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

//.........................................Methods to bind with Input Actions.........................................//

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

//....................................................................................................................//

//Blueprint methods
public:

	virtual void OnCharacterDeath_Implementation() override;
	

//Blueprint values
public:

//................................................Input Actions values................................................//
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Input")
	UInputAction* ReloadAction;
//....................................................................................................................//

//...................................................Camera values....................................................//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Camera")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacter|Camera")
	class UCameraComponent* FollowCamera;

//....................................................................................................................//

	UPROPERTY(BlueprintReadOnly, Category = "PlayerCharacter")
	class AAIS_PlayerController* PlayerController = nullptr;

};

