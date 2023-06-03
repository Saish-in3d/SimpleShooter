// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	

	if (bIsWinner == false)
	{
		UUserWidget* LoseWidget = CreateWidget(this, LoseWidgetClass);
		if (LoseWidget )
		{
			//CrosshairWidget->RemoveFromViewport();
			ClearHUD_Implementation();
			LoseWidget->AddToViewport();
		}
	}

	else if (bIsWinner == true)
	{
		UUserWidget* WinWidget = CreateWidget(this, WinWidgetClass);
		if (WinWidget )
		{
			//CrosshairWidget->RemoveFromViewport();
			ClearHUD_Implementation();
			WinWidget->AddToViewport();
			
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::OpenMainMenu, RestartDelay);
}

UUserWidget* AShooterPlayerController::SetPauseWidget()
{
	if(PauseWidgetClass)
	{
		PauseWidget = CreateWidget(this, PauseWidgetClass);
		PauseWidget->AddToViewport();
		bShowMouseCursor = true;

		return PauseWidget;
	}
	return  nullptr;
}



void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AShooterPlayerController::ClearHUD_Implementation()
{
	
}

void AShooterPlayerController::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}








