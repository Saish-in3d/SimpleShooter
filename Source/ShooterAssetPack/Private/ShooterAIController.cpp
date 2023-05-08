// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIController.h"

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (PlayerPawn && LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, AcceptanceRadius);
	}
	if (PlayerPawn && !LineOfSightTo(PlayerPawn))
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();

	}*/
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0.f);

	if (AIBehaviour)
	{
		RunBehaviorTree(AIBehaviour);
	}

	GetBlackboardComponent()->SetValueAsVector(FName("PlayerLocation"), PlayerPawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(FName("StartLocation"), GetPawn()->GetActorLocation());
	
}
