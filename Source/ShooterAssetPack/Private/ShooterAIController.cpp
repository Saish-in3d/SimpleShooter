// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIController.h"
#include "ShooterAssetPack/ShooterCharacter.h"

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn && LineOfSightTo(PlayerPawn))
	{
		//GetBlackboardComponent()->SetValueAsVector(FName("PlayerLocation"), PlayerPawn->GetActorLocation());
		//GetBlackboardComponent()->SetValueAsVector(FName("PlayerLastLocation"), PlayerPawn->GetActorLocation());
	}
	if (PlayerPawn && !LineOfSightTo(PlayerPawn))
	{
		//GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ShooterChatacter = Cast<AShooterCharacter>(GetPawn());
	if (ShooterChatacter)
	{
		return ShooterChatacter->IsDead();
	}
	
	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	//PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0.f);

	if (AIBehaviour)
	{
		RunBehaviorTree(AIBehaviour);
	}

	
     GetBlackboardComponent()->SetValueAsVector(FName("StartLocation"), GetPawn()->GetActorLocation());
	
}
