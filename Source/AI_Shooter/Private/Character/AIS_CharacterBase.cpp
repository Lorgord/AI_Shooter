// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Shooter/Public/Character/AIS_CharacterBase.h"

#include "Components/AttributesComponent/AIS_CharacterAttributesComponent.h"

AAIS_CharacterBase::AAIS_CharacterBase()
{
	AttributesComponent = CreateDefaultSubobject<UAIS_CharacterAttributesComponent>(TEXT("AttributesComponent"));
}

void AAIS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AttributesComponent))
	{
		AttributesComponent->OnCharacterDeath.AddDynamic(this, &AAIS_CharacterBase::OnCharacterDeath);
	}
}

void AAIS_CharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAIS_CharacterBase::OnCharacterDeath()
{
}