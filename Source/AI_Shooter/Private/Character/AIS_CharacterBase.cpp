// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Shooter/Public/Character/AIS_CharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/AttributesComponent/AIS_CharacterAttributesComponent.h"
#include "Components/EquipmentComponent/AIS_CharacterEquipmentComponent.h"



AAIS_CharacterBase::AAIS_CharacterBase()
{
	AttributesComponent = CreateDefaultSubobject<UAIS_CharacterAttributesComponent>(TEXT("AttributesComponent"));
	EquipmentComponent = CreateDefaultSubobject<UAIS_CharacterEquipmentComponent>(TEXT("EquipmentComponent"));
	
}

void AAIS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AttributesComponent))
	{
		AttributesComponent->OnCharacterDeath.AddDynamic(this, &AAIS_CharacterBase::OnCharacterDeath);
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = this;
	
	FocusActor = GetWorld()->SpawnActor<APawn>(FocusActorClass, GetTransform(), SpawnParameters);
	
	if (IsValid(FocusActor))
	{
		FocusActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FocusActorSocket);
	}
}

void AAIS_CharacterBase::StartShooting()
{
	if (IsValid(EquipmentComponent) || CanUseEquipment())
	{
		EquipmentComponent->StartShooting();
	}
}

void AAIS_CharacterBase::StopShooting()
{
	if (IsValid(EquipmentComponent) || CanUseEquipment())
	{
		EquipmentComponent->StopShooting();
	}
}

void AAIS_CharacterBase::StartReloading()
{
	if (IsValid(EquipmentComponent) || CanUseEquipment())
	{
		EquipmentComponent->StartReloading();
	}
}

void AAIS_CharacterBase::StopAllActions()
{
	if (IsValid(EquipmentComponent))
	{
		EquipmentComponent->StopAllActions();
	}
}

void AAIS_CharacterBase::OnCharacterDeath_Implementation()
{
	bIsCharacterDead = true;
	FocusActor->Destroy();
	StopAllActions();
	
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetCapsuleComponent()->DestroyComponent();
	GetMesh()->SetSimulatePhysics(true);
}
