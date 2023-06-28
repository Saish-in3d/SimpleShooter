// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "CharDisplayActor.h"
#include "CharSelectWidget.h"
#include "CharacterDisplayPawn.h"
#include "Components/Button.h"
#include "SlateCore/Public/Input/Events.h"
#include "MyShooterGameInstance.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Components/EditableTextBox.h"


bool UCharSelectWidget::Initialize()
{
	Super::Initialize();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		CharDisplayPawn = Cast<ACharacterDisplayPawn>(FoundActor);
		if (CharDisplayPawn)
		{
			break;
		}
	}
	FlashCharButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickFlashCharButton);
	FlashCharButton->OnHovered.AddDynamic(this, &UCharSelectWidget::OnHoverFlashCharButton);
	WallCharButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickWallCharButton);
	WallCharButton->OnHovered.AddDynamic(this, &UCharSelectWidget::OnHoverWallCharButton);
	StartGameButton->OnClicked.AddDynamic(this, &UCharSelectWidget::OnClickStartGameButton);
	
	
	//NameBox->OnEditableTextBoxCommittedEvent.AddDynamic(ReturnedText, ETextCommit::OnEnter);
	
	//NameBox->OnEditableTex


	return true;
	
	//FDataPlayer gg1;
	//gg1.DataPlayeName;
}

void UCharSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//NameBox->FOnEditableTextBoxCommittedEvent_DelegateWrapper.AddDynamic(ReturnedText, ETextCommit::OnEnter);
	NameBox->OnTextCommitted.AddDynamic(this, &UCharSelectWidget::HandleTextBoxCommitted);

}

void UCharSelectWidget::OnClickFlashCharButton()
{
	if (CharDisplayPawn == nullptr) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
	CharDisplayPawn->GetSC();
	
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
	UGameplayStatics::OpenLevel(GetWorld(), FName("SandBox"));
}

void UCharSelectWidget::HandleTextBoxCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	switch (CommitType)
	{
	case ETextCommit::Default:
		// Handle Default commit type
		break;

	case ETextCommit::OnEnter:
		UMyShooterGameInstance* MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
		if (MyShooterGameInstance)
		{
			//MyShooterGameInstance->DataGetter.DataPlayeName = Text;
			//MyShooterGameInstance->PlayerDataArray.Add(Text.ToString());
			MyShooterGameInstance->Player1 = Text.ToString();
			UE_LOG(LogTemp, Warning, TEXT("At text Entered %s"), *MyShooterGameInstance->Player1);
		}
		break;
	}
}



//void UCharSelectWidget::HandleNameTextCommitted(const FText& Text, ETextCommit::Type CommitType)
//{
//	
//
//}
