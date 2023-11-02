// Copyright by Egor "Lorgord" Voronov


#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"

#include "GameFramework/Character.h"
#include "Items/Weapons/RangeWeapon/AIS_RangeWeapon.h"
#include "Kismet/GameplayStatics.h"


UAIS_CharacterEquipmentComponent::UAIS_CharacterEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIS_CharacterEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	RangeWeapon = GetWorld()->SpawnActorDeferred<AAIS_RangeWeapon>(RangeWeaponClass, FTransform::Identity, GetOwner(), GetOwner<APawn>());
	UGameplayStatics::FinishSpawningActor(RangeWeapon, FTransform::Identity);

	if (IsValid(RangeWeapon))
	{
		RangeWeapon->AttachToComponent(GetOwner<ACharacter>()->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
		RangeWeapon->OnWeaponStartReload.AddDynamic(this, &UAIS_CharacterEquipmentComponent::OnWeaponStartReload);
	}
}

void UAIS_CharacterEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	DebugDrawValues();
#endif
}

void UAIS_CharacterEquipmentComponent::StartShooting()
{
	if (IsValid(RangeWeapon))
	{
		RangeWeapon->StartShooting();
	}
}

void UAIS_CharacterEquipmentComponent::StopShooting()
{
	if (IsValid(RangeWeapon))
	{
		RangeWeapon->StopShooting();
	}
}

void UAIS_CharacterEquipmentComponent::StartReloading()
{
	if (IsValid(RangeWeapon))
	{
		RangeWeapon->StartReloading();
	}
}

void UAIS_CharacterEquipmentComponent::StopAllActions()
{
	if (IsValid(RangeWeapon))
	{
		RangeWeapon->StopShooting();
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	}
}

bool UAIS_CharacterEquipmentComponent::IsDoingSomeAction()
{
	bool Result = bIsWeaponReloading;
	
	if (IsValid(RangeWeapon))
	{
		Result |= RangeWeapon->IsShooting();
	}
	
	return Result;
}

bool UAIS_CharacterEquipmentComponent::IsWeaponNeedsReload()
{
	if (IsValid(RangeWeapon))
	{
		return RangeWeapon->CurrentAmmo <= 0;
	}

	return false;
}

void UAIS_CharacterEquipmentComponent::OnWeaponStartReload()
{
	if (!IsValid(RangeWeapon) || bIsWeaponReloading) return;
	
	if (!bIsAmmoInfinity && TotalAmmo <= 0)
	{
		return;
	}

	bIsWeaponReloading = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UAIS_CharacterEquipmentComponent::OnWeaponEndReload, RangeWeapon->ReloadTime, false);
}

void UAIS_CharacterEquipmentComponent::OnWeaponEndReload()
{
	if (!IsValid(RangeWeapon)) return;
	
	if (bIsAmmoInfinity)
	{
		RangeWeapon->FillMagazine(RangeWeapon->GetMagazineFreeSpace());
	}
	else
	{
		const int AmmoToReload = FMath::Min(TotalAmmo, RangeWeapon->GetMagazineFreeSpace());
		
		RangeWeapon->FillMagazine(AmmoToReload);
		TotalAmmo -= AmmoToReload;
	}

	bIsWeaponReloading = false;
	RangeWeapon->StopReloading();
}

void UAIS_CharacterEquipmentComponent::DebugDrawValues()
{
	if (!IsValid(RangeWeapon)) return;
	
	FVector TextLocation = RangeWeapon->GetActorLocation() + DebugTextLocationOffset;
	const FColor Color = RangeWeapon->CurrentAmmo > 0 ? FColor::Yellow : FColor::Red;
	
	DrawDebugString(GetWorld(), TextLocation, FString::Printf(TEXT("Ammo: %i/%i\nTotal: %i"), RangeWeapon->CurrentAmmo, RangeWeapon->MaxAmmo, TotalAmmo), nullptr, Color, 0.0f, true);

	if (GetWorld()->GetTimerManager().IsTimerActive(ReloadTimer))
	{
		TextLocation += FVector::UpVector * 8.0f;
		DrawDebugString(GetWorld(), TextLocation, FString::Printf(TEXT("RELOADING %.2f"), GetWorld()->GetTimerManager().GetTimerRemaining(ReloadTimer)), nullptr, FColor::Red, 0.0f, true);
	}
}
