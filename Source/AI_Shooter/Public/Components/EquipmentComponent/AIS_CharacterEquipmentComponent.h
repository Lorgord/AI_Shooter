// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIS_CharacterEquipmentComponent.generated.h"


class AAIS_RangeWeapon;



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AI_SHOOTER_API UAIS_CharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	//constructor
	public:
	UAIS_CharacterEquipmentComponent();

	//c++ protected methods
	protected:
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//c++ private values
	private:

	FTimerHandle ReloadTimer;

	//Blueprint methods
	public:

	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	void StopShooting();

	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	void StartReloading();

	UFUNCTION(BlueprintCallable, Category = "Eqiopment|Action")
	bool IsDoingSomeAction() { return bIsWeaponReloading; }

	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	bool IsWeaponNeedsReload();

	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	void OnWeaponStartReload();
	
	UFUNCTION(BlueprintCallable, Category = "Equipment|Action")
	void OnWeaponEndReload();

//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment|Weapon")
	TSubclassOf<AAIS_RangeWeapon> RangeWeaponClass = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Weapon")
	AAIS_RangeWeapon* RangeWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment|Weapon")
	FName WeaponSocketName = "TestWeaponSocket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment|Ammo")
	int TotalAmmo = 600;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment|Ammo")
	bool bIsAmmoInfinity = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Equipment|Reload")
	bool bIsWeaponReloading = false;


//....................................................................................................................//
//........................................................Debug.......................................................//

	UFUNCTION(BlueprintCallable, Category = "Equipment|Debug")
	void DebugDrawValues();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment|Debug")
	FVector DebugTextLocationOffset = {0.0f, 0.0f, 8.0f};
};
