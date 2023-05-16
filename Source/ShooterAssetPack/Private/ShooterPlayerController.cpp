// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	

	if (bIsWinner == false)
	{
		UUserWidget* LoseWidget = CreateWidget(this, LoseWidgetClass);
		if (LoseWidget)
		{
			CrosshairWidget->RemoveFromViewport();
			LoseWidget->AddToViewport();
		}
	}

	else if (bIsWinner == true)
	{
		UUserWidget* WinWidget = CreateWidget(this, WinWidgetClass);
		if (WinWidget)
		{
			CrosshairWidget->RemoveFromViewport();
			WinWidget->AddToViewport();
			
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CrosshairWidget = CreateWidget(this, CrosshairWidgetClass);
	CrosshairWidget->AddToViewport();
}


