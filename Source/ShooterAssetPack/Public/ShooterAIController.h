// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterInterface.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AShooterAIController : public AAIController, public IShooterInterface
{
	GENERATED_BODY() 

public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;


protected:
	virtual void BeginPlay() override;
	
private:
	class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200.f;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehaviour;

	UFUNCTION()
	virtual void Stun2_Implementation(class AShooterAIController* SAIC) override;

	FTimerHandle Stun2TimerHandle;

	void AfterDelay();

	AShooterAIController* SAICTemp;



};
