// Copyright by Egor "Lorgord" Voronov


#include "Components/AttributesComponent/AIS_CharacterAttributesComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


UAIS_CharacterAttributesComponent::UAIS_CharacterAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIS_CharacterAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = GetOwner<ACharacter>();

	
	if (!IsValid(OwnerCharacter)) return;
	
	OwnerCharacter->OnTakeAnyDamage.AddDynamic(this, &UAIS_CharacterAttributesComponent::OnTakeAnyDamage);
}

void UAIS_CharacterAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	DebugDrawAttributes();
#endif
}

void UAIS_CharacterAttributesComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsAlive()) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	
	if (!IsAlive())
	{
		if (OnCharacterDeath.IsBound())
		{
			OnCharacterDeath.Broadcast();
		}
	}
}

void UAIS_CharacterAttributesComponent::DebugDrawAttributes()
{
	if (Health <= 0.0f)
	{
		return;
	}
	FVector TextLocation = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * FVector::UpVector;
	FVector HealthTextLocation = TextLocation + HealthTextHeight * FVector::UpVector;
	
	DrawDebugString(GetWorld(), HealthTextLocation, FString::Printf(TEXT("Health: %.2f"), Health), nullptr, FColor::Green, 0.0f, true);
}