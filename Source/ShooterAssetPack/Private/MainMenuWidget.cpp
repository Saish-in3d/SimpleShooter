// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"
#include "Components/Button.h"




bool UMainMenuWidget::Initialize()
{
	Super::Initialize();
	//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
	StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickStartGameButton);
	LeaderBoardButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickLeaderBoardButton);
	ExitGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnClickExitGameButton);
	return true;
}



void UMainMenuWidget::OnClickStartGameButton()
{
	

	UGameplayStatics::OpenLevel(GetWorld(), FName("CharSelectLevel"));
	/*APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		if (CharSelectWidgetClass)
		{
			
			PlayerController->bShowMouseCursor = true;
		}
	}*/
	


	
}

void UMainMenuWidget::OnClickLeaderBoardButton()
{
	//UE_LOG(LogTemp, Warning, TEXT("Your message here1112"));

	if (LeaderBoardWidgetClass ) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
		auto LeaderBoardWidget = CreateWidget(this, LeaderBoardWidgetClass);
		LeaderBoardWidget->AddToViewport();
	}
}

void UMainMenuWidget::OnClickExitGameButton()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}

}


