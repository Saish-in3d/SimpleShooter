// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterInterface.h"
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

void AShooterAIController::Stun2_Implementation(AShooterAIController* SAIC)
{
	//UE_LOG(LogTemp, Warning, TEXT("Testing Test"));
	SAICTemp = SAIC;
	SAICTemp->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), true);
	GetWorld()->GetTimerManager().SetTimer(Stun2TimerHandle, this, &AShooterAIController::AfterDelay, 3.f, false);

}

void AShooterAIController::AfterDelay()
{
	SAICTemp->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), false);
}
