// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameModeBase.h"
#include "GameFramework/PlayerController.h"

void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if(PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test1"));

		PlayerController->GameHasEnded(nullptr, false);
	}
}

void AKillEmAllGameModeBase::EndGame()
{

}
