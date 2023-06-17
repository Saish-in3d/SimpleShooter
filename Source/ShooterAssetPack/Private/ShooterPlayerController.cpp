// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEmAllGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "MyShooterGameInstance.generated.h"
#include "GameFramework/PlayerStart.h"
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
			AShooterCharacter* ShooterChar = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if(ShooterChar)
			{
				ShooterChar->Test();
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

	//SetInputMode(FInputModeGameOnly());

	//if(HUDWidgetClass)
	//{
	//	HUDWidget = CreateWidget(this, HUDWidgetClass);
	//	HUDWidget->AddToViewport();
	//}
	//UMyShooterGameInstance* GameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	//for (AActor* Actor : FoundActors)
	//{
	//	APlayerStart* PlayerStart = Cast<APlayerStart>(Actor);
	//	if (PlayerStart)
	//	{
	//		PlayerStart->GetActorTransform();
	//		if (GameInstance)
	//		{
	//			//GetWorld()->SpawnActor<GameInstance->Character1>(ExpWallClass, Location, Rotation); // CONTINUE HERE
	//		}

	//		// ...
	//		break; // If you only need one PlayerStart object, you can break the loop once found
	//	}

	//}
}

void AShooterPlayerController::ClearHUD_Implementation()
{
	
}

void AShooterPlayerController::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");
}








