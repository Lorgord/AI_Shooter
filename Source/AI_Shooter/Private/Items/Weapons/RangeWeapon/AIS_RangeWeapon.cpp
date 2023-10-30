// Copyright by Egor "Lorgord" Voronov


#include "Items/Weapons/RangeWeapon/AIS_RangeWeapon.h"

#include "Engine/DamageEvents.h"


AAIS_RangeWeapon::AAIS_RangeWeapon()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void AAIS_RangeWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwningPawn = GetOwner<APawn>();
}

void AAIS_RangeWeapon::StartShooting()
{
	if (!CanShoot()) return;
	
	MakeShot();

	if (FireMode == EFireMode::FullAuto)
	{
		StopShooting();
		GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &AAIS_RangeWeapon::MakeShot, GetShotTimerInterval(), true);
	}
}

void AAIS_RangeWeapon::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void AAIS_RangeWeapon::StartReloading()
{
	if (CurrentAmmo == MaxAmmo) return;

	if (OnWeaponReload.IsBound())
	{
		OnWeaponReload.Broadcast();
		bIsReloading = true;
	}
}

void AAIS_RangeWeapon::StopReloading()
{
	bIsReloading = false;
}

void AAIS_RangeWeapon::MakeShot()
{
	if (!CanShoot() || !IsValid(OwningPawn))
	{
		StopShooting();
		return;
	}

	--CurrentAmmo;

	FVector ShotLocation;
	FRotator ShotRotation;

	if (OwningPawn->IsPlayerControlled())
	{
		const APlayerController* PlayerController = OwningPawn->GetController<APlayerController>();
		PlayerController->GetPlayerViewPoint(ShotLocation, ShotRotation);
	}
	else
	{
		ShotRotation = OwningPawn->GetBaseAimRotation();
	}
	
	ShotLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);

	const float RandSpreadAngle = FMath::RandRange(0.0f, FMath::DegreesToRadians(SpreadAngle));
	
	FVector ShotDirection = ShotRotation.Vector() + GetSpreadOffset(RandSpreadAngle, ShotRotation);

	FVector ShotEnd = ShotLocation + FiringRange * ShotDirection;

	FHitResult ShotTraceResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningPawn);

	if (GetWorld()->LineTraceSingleByChannel(ShotTraceResult, ShotLocation, ShotEnd, ECC_GameTraceChannel11, QueryParams)) //ECC_GameTraceChannel11 = ECC_Bullet
	{
		ShotDirection = ShotEnd - ShotLocation;
		ShotEnd = ShotTraceResult.ImpactPoint;
		
		FPointDamageEvent DamageEvent;
		DamageEvent.HitInfo = ShotTraceResult;
		
		ShotTraceResult.GetActor()->TakeDamage(Damage, DamageEvent, OwningPawn->GetController(), OwningPawn);
	}
	
	//..........Debug..........//
	
	DrawDebugLine(GetWorld(), ShotLocation, ShotEnd, FColor::Red, false, 0.5f);
	DrawDebugPoint(GetWorld(), ShotEnd, 5.0f, FColor::Green, false, 0.5f);
	
	//.........................//
}

FVector AAIS_RangeWeapon::GetSpreadOffset(float Angle, FRotator ShotRotation)
{
	const float SpreadSize = FMath::Tan(Angle);
	const float RotationAngle = FMath::RandRange(0.0f, 2 * PI);

	const float SpreadY = FMath::Cos(RotationAngle);
	const float SpreadZ = FMath::Sin(RotationAngle);

	const FVector Result = (ShotRotation.RotateVector(FVector::UpVector) * SpreadZ +
							ShotRotation.RotateVector(FVector::RightVector) * SpreadY) * SpreadSize;

	return Result;
}