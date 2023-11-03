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
	StopShooting();

	if (FireMode == EFireMode::FullAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &AAIS_RangeWeapon::MakeShot, GetShotTimerInterval(), true);
	}
}

void AAIS_RangeWeapon::StopShooting()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShotTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
		
		if (OnStoppedShooting.IsBound())
		{
			OnStoppedShooting.Broadcast();
		}
	}
}

void AAIS_RangeWeapon::StartReloading()
{
	if (CurrentAmmo == MaxAmmo) return;

	bIsReloading = true;
	if (OnWeaponStartReload.IsBound())
	{
		OnWeaponStartReload.Broadcast();
	}
}

void AAIS_RangeWeapon::StopReloading()
{
	bIsReloading = false;

	if (OnWeaponStopReload.IsBound())
	{
		OnWeaponStopReload.Broadcast();
	}
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
	OwningPawn->GetController()->GetPlayerViewPoint(ShotLocation, ShotRotation);

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
	
	DrawDebugLine(GetWorld(), WeaponMesh->GetSocketLocation(MuzzleSocketName), ShotEnd, FColor::Red, false, 0.5f);
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

bool AAIS_RangeWeapon::IsShooting()
{
	return GetWorld()->GetTimerManager().IsTimerActive(ShotTimer);
}
