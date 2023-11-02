// Copyright by Egor "Lorgord" Voronov


#include "AI/Controllers/AIS_AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/AIS_AICharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"


AAIS_AIControllerBase::AAIS_AIControllerBase()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}


void AAIS_AIControllerBase::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OwningAICharacter = Cast<AAIS_AICharacter>(InPawn);

	if (IsValid(OwningAICharacter))
	{
		RunBehaviorTree(OwningAICharacter->GetBehaviorTree());
	}
}

void AAIS_AIControllerBase::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (IsValid(OwningAICharacter))
	{
		TryFindNextTarget();
	}
}

FPathFollowingRequestResult AAIS_AIControllerBase::MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath)
{
	if (IsValid(OwningAICharacter))
	{
		OwningAICharacter->UnCrouch();
	}
	
	return Super::MoveTo(MoveRequest, OutPath);
}


AActor* AAIS_AIControllerBase::GetClosestSensedActor(TSubclassOf<UAISense> SensedClass) const
{
	if (!IsValid(GetPawn())) return nullptr;

	TArray<AActor*> SensedActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(SensedClass, SensedActors);

	if (SensedActors.IsEmpty()) return nullptr;

	AActor* ClosestActor = nullptr;

	float MinSquaredDistance = FLT_MAX;

	const FVector PawnLocation = GetPawn()->GetActorLocation();
	for (const auto SensedActor : SensedActors)
	{
		if (!SensedActor->Implements<UGenericTeamAgentInterface>()) continue;

		const IGenericTeamAgentInterface* TeamAgentInterface = Cast<IGenericTeamAgentInterface>(SensedActor);
		if (TeamAgentInterface->GetTeamAttitudeTowards(*OwningAICharacter) != ETeamAttitude::Hostile) continue;
		
		
		const float CurrentSquaredDistance = (PawnLocation - SensedActor->GetActorLocation()).SizeSquared();

		if (CurrentSquaredDistance < MinSquaredDistance)
		{
			MinSquaredDistance = CurrentSquaredDistance;
			ClosestActor = SensedActor;
		}
	}

	return ClosestActor;
}

void AAIS_AIControllerBase::TryFindNextTarget()
{
	AActor* ClosestActor = GetClosestSensedActor(UAISense_Sight::StaticClass());

	if (!IsValid(Blackboard) || !IsValid(ClosestActor)) return;
	
		
	if (const AAIS_CharacterBase* CharacterBase = Cast<AAIS_CharacterBase>(ClosestActor))
	{
		if (IsValid(CharacterBase->FocusActor))
		{
			ClosestActor = CharacterBase->FocusActor;
		}
	}
	
	Blackboard->SetValueAsObject(FName("CurrentTarget"), ClosestActor);
}
