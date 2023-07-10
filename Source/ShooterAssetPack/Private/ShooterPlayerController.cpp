// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "MyShooterGameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "TimeSaveGame.h"
#include "DataObject.h"
#include "KillEmAllGameModeBase.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (ShooterChar)
	{
		//UE_LOG(LogTemp, Warning, TEXT("if(ShooterChar)"));
		TimeScore = ShooterChar->SetTime();
	}
	
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
			
			if(ShooterChar)
			{
				//ShooterChar->Test();
			}
		}
		
		bool DoesSlotExists = UGameplayStatics::DoesSaveGameExist(FString("FinalSaveSlot"), 0);
		
		if(DoesSlotExists == false)
		{
			if(TimeSaveGameObject == nullptr)
			{
				TimeSaveGameObject = Cast<UTimeSaveGame>(UGameplayStatics::CreateSaveGameObject(UTimeSaveGame::StaticClass()));
			}
			UMyShooterGameInstance* MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
			if (MyShooterGameInstance && TimeSaveGameObject)
			{
				TimeSaveGameObject->SavedPlayerDataArray.Add(MyShooterGameInstance->PlayerNameValue);
				TimeSaveGameObject->SavedPlayerDataArray.Add(FString::SanitizeFloat(TimeScore));

				if (UGameplayStatics::SaveGameToSlot(TimeSaveGameObject, TEXT("FinalSaveSlot"), 0))
				{
					// Save successful
					UE_LOG(LogTemp, Warning, TEXT(" false Save successful"));
				}
				else
				{
					// Save failed
					UE_LOG(LogTemp, Warning, TEXT("false Save failed"));
				}
			}
		}
		if (DoesSlotExists == true)
		{
			if(TimeSaveGameInstance == nullptr)
			{
				TimeSaveGameInstance = Cast<UTimeSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("FinalSaveSlot"), 0));
			}
			UMyShooterGameInstance* MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
			if (MyShooterGameInstance && TimeSaveGameInstance)
			{
				for (FString g : TimeSaveGameInstance->SavedPlayerDataArray)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Before Save game loop %s"), *g);
				}
				TimeSaveGameInstance->SavedPlayerDataArray.Add(MyShooterGameInstance->PlayerNameValue);
				TimeSaveGameInstance->SavedPlayerDataArray.Add(FString::SanitizeFloat(TimeScore));
				

				if (UGameplayStatics::SaveGameToSlot(TimeSaveGameInstance, TEXT("FinalSaveSlot"), 0))
				{
					// Save successful
					UE_LOG(LogTemp, Warning, TEXT(" true Save successful"));
				}
				else
				{
					// Save failed
					UE_LOG(LogTemp, Warning, TEXT(" true Save failed"));
				}
			}

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

	SetInputMode(FInputModeGameOnly());

	if(HUDWidgetClass)
	{
		HUDWidget = CreateWidget(this, HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
	ShooterChar = Cast<AShooterCharacter>(GetPawn());
	
}

void AShooterPlayerController::ClearHUD_Implementation()
{
	HUDWidget->RemoveFromViewport();
}

void AShooterPlayerController::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}



