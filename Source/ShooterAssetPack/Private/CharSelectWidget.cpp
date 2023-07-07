// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "CharDisplayActor.h"
#include "CharSelectWidget.h"
#include "CharacterDisplayPawn.h"
#include "Components/Button.h"
#include "SlateCore/Public/Input/Events.h"
#include "MyShooterGameInstance.h"
#include "MainMenuWidget.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"


bool UCharSelectWidget::Initialize()
{
	Super::Initialize();

	NameEntered = false;
	CharSelected = false;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	PromptTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Prompt")));

	for (AActor* FoundActor : FoundActors)
	{
		CharDisplayPawn = Cast<ACharacterDisplayPawn>(FoundActor);
		if (CharDisplayPawn)
		{
			CharDisplayPawn->WCHide();
			CharDisplayPawn->FCHide();
			break;
		}
	}
	FlashCharButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickFlashCharButton);
	FlashCharButton->OnHovered.AddDynamic(this, &UCharSelectWidget::OnHoverFlashCharButton);
	WallCharButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickWallCharButton);
	WallCharButton->OnHovered.AddDynamic(this, &UCharSelectWidget::OnHoverWallCharButton);
	StartGameButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickStartGameButton);
	
	if (PromptTB)
	{
		PromptTB->SetText(FText::FromString("Select Character"));
	}

	return true;

}

void UCharSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//NameBox->FOnEditableTextBoxCommittedEvent_DelegateWrapper.AddDynamic(ReturnedText, ETextCommit::OnEnter);
	NameBox->OnTextCommitted.AddDynamic(this, &UCharSelectWidget::HandleTextBoxCommitted);
	BackButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickBackButton);

}

void UCharSelectWidget::OnClickFlashCharButton()
{
	if (CharDisplayPawn == nullptr) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
	CharDisplayPawn->GetSC();
	CharSelectStatus = ECharSelectStatus::CSS_CharSelected;
	if (PromptTB)
	{
		PromptTB->SetText(FText::FromString("Flash Character Chosen"));
	}
	
}

void UCharSelectWidget::OnHoverFlashCharButton()
{
	if (CharDisplayPawn == nullptr) { return; }
	CharDisplayPawn->FCShow();
	//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
	CharDisplayPawn->WCHide();
		
}

void UCharSelectWidget::OnClickWallCharButton()
{
	if (CharDisplayPawn == nullptr) { return; }
	CharDisplayPawn->GetWC();
	CharSelectStatus = ECharSelectStatus::CSS_CharSelected;
	if (PromptTB)
	{
		PromptTB->SetText(FText::FromString("Wall Character Chosen"));
	}
}

void UCharSelectWidget::OnHoverWallCharButton()
{
	if (CharDisplayPawn == nullptr) { return; }
	CharDisplayPawn->WCShow();
	//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
	CharDisplayPawn->FCHide();
}

void UCharSelectWidget::OnClickStartGameButton()
{
	if(CharSelectStatus >= ECharSelectStatus::CSS_NameEntered)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName("SandBox"));
	}
	if (CharSelectStatus >= ECharSelectStatus::CSS_CharSelected)
	{
		if (PromptTB)
		{
			PromptTB->SetText(FText::FromString("Enter Your Name"));
		}
	}
	else 
	{
		if (PromptTB)
		{
			PromptTB->SetText(FText::FromString("Enter all details"));
		}
	}
}

void UCharSelectWidget::OnClickBackButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");

}

void UCharSelectWidget::HandleTextBoxCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	
	
	if (CharSelectStatus >= ECharSelectStatus::CSS_CharSelected)
	{
		
		switch (CommitType)
		{
		case ETextCommit::Default:
			
		 //Handle Default commit type

			break;

		case ETextCommit::OnEnter:
			//UE_LOG(LogTemp, Warning, TEXT("TEST"));
			if (CharSelectStatus == ECharSelectStatus::CSS_NameEntered)
			{
				
				if (PromptTB)
				{
					PromptTB->SetText(FText::FromString("Name already entered, reselect character type to rename"));
				}
			}
			MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
			if (MyShooterGameInstance && CharSelectStatus < ECharSelectStatus::CSS_NameEntered)
			{
				CharSelectStatus = ECharSelectStatus::CSS_NameEntered;

				MyShooterGameInstance->PlayerNameValue = Text.ToString();
				UE_LOG(LogTemp, Warning, TEXT("At text Entered %s"), *MyShooterGameInstance->PlayerNameValue);
				if (PromptTB)
				{
					PromptTB->SetText(FText::FromString("Name Entered"));
				}
			}
			break;

		case ETextCommit::OnCleared:
		//Handle Default commit type
			
		break;

		case ETextCommit::OnUserMovedFocus:
			//Handle Default commit type
			
		break;
		}
	}
	
}