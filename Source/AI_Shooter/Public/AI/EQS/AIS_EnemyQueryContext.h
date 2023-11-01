// Copyright by Egor "Lorgord" Voronov

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "AIS_EnemyQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class AI_SHOOTER_API UAIS_EnemyQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:

	UAIS_EnemyQueryContext();

public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
		FName CurrentTarget = "CurrentTarget";
};
