// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "CharDisplayActor.h"
#include "CharSelectWidget.h"
#include "CharacterDisplayPawn.h"
#include "Components/Button.h"

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

	return true;
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
