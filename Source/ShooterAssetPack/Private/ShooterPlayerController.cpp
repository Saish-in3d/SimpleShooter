// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	UUserWidget* LoseWidget = CreateWidget(this, LoseWidgetClass);
	if(LoseWidget)
	{
		LoseWidget->AddToViewport();
	}
}


