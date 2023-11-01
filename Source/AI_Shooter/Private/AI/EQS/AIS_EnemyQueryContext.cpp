// Copyright by Egor "Lorgord" Voronov


#include "AI/EQS/AIS_EnemyQueryContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"



UAIS_EnemyQueryContext::UAIS_EnemyQueryContext()
{
}

void UAIS_EnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if( !IsValid(Blackboard) ) return;

	UObject* EnemyActor = Blackboard->GetValueAsObject(CurrentTarget);

	if (!IsValid(EnemyActor)) return;
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(EnemyActor));
}
