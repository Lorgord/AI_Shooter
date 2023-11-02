// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIS_RangeWeapon.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStartReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStopReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoppedShooting);

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	Single,
	FullAuto
};

UCLASS()
class AI_SHOOTER_API AAIS_RangeWeapon : public AActor
{
	GENERATED_BODY()

//constructor
public:
	
	AAIS_RangeWeapon();
	

//c++ protected methods
protected:
	
	virtual void BeginPlay() override;

//c++ private methods
private:

	FORCEINLINE float GetShotTimerInterval() const { return 60.0f / FireRate; }
	

//c++ private values
private:

	UPROPERTY()
	APawn* OwningPawn = nullptr;

	bool bIsReloading = false;
	
	FTimerHandle ShotTimer;


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	void StopShooting();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Reloading")
	void StartReloading();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Reloading")
	void StopReloading();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Reloading")
	FORCEINLINE void FillMagazine(const int AmmoAmount) { CurrentAmmo += AmmoAmount; }
	
	UFUNCTION(BlueprintCallable, Category = "Weapom|Reloading")
	FORCEINLINE int GetMagazineFreeSpace() const { return MaxAmmo - CurrentAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	void MakeShot();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	FVector GetSpreadOffset(float Angle, FRotator ShotRotation);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	FORCEINLINE bool CanShoot() const { return CurrentAmmo > 0 && !bIsReloading; }

	UFUNCTION(BlueprintCallable, Category = "Weapon|Shooting")
	bool IsShooting();
	

//Blueprint values
public:

	UPROPERTY(BlueprintAssignable, Category = "Weapon|Events")
	FOnWeaponStartReload OnWeaponStartReload;

	UPROPERTY(BlueprintAssignable, Category = "Weapon|Events")
	FOnWeaponStartReload OnWeaponStopReload;

	UPROPERTY(BlueprintAssignable, Category = "Weapon|Events")
	FOnStoppedShooting OnStoppedShooting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Info")
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info")
	EFireMode FireMode = EFireMode::FullAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Info", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	int MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Info", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	int CurrentAmmo = MaxAmmo;
	/*
		Using reload timer instead of reload animation
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float ReloadTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info", meta = (ClampMin = 1.0f, UIMin = 1.0f))
	float FireRate = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info", meta = (ClampMin = 1.0f, UIMin = 1.0f))
	float FiringRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float SpreadAngle = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Info", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float Damage = 2.0f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Components")
	UStaticMeshComponent* WeaponMesh = nullptr;
};
