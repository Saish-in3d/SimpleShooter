// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERASSETPACK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReduceHealth(float Damage);

	float GetAlpha();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere)
		float MaxHealth = 50.f;

	float Health;

	//persistent health value check to init death logic
	void CheckHealth();

	FTimerHandle WallTimer;

	//Used for walls and auto breakables where health decreases wrt time.
	void ReduceTimeHealth();
};
