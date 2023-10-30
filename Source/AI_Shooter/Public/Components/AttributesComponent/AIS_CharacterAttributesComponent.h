// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIS_CharacterAttributesComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, CurrentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AI_SHOOTER_API UAIS_CharacterAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

//constructor
public:

	UAIS_CharacterAttributesComponent();

//c++ protected methods
protected:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

	
//Blueprint methods/values
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Character")
	ACharacter* OwnerCharacter = nullptr;

//....................................................Health/Death....................................................//
	
	UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
	FORCEINLINE bool IsAlive() const { return Health > 0.0f; }
	
	
	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes|Events")
	FOnCharacterDeath OnCharacterDeath;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes|Health", meta = (UIMin = 0.0f))
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes|Health")
	float Health = MaxHealth;

//....................................................................................................................//
//........................................................Debug.......................................................//

	UFUNCTION(BlueprintCallable, Category = "Attributes|Debug")
	void DebugDrawAttributes();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes|Debug")
	float HealthTextHeight = 8.0f;
};
