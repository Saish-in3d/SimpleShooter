// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataPlayer.h"
#include "CharSelectWidget.generated.h"

/** 
 * 
 */

UENUM()
enum class ECharSelectStatus : uint8
{
	CSS_None UMETA(DisplayName = "None"),
	CSS_CharSelected UMETA(DisplayName = "CharSelected"),
	CSS_NameEntered UMETA(DisplayName = "NameEntered"),
};



UCLASS()
class SHOOTERASSETPACK_API UCharSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UButton* FlashCharButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* WallCharButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* NameBox;


	const FText ReturnedText;

	//FDataPlayer GG;

	UPROPERTY(EditAnywhere)
		class UTextBlock* PromptTB;

	class AShooterCharacter* ShooterChar;

	bool NameEntered = false;

	bool CharSelected = false;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

	


	



private:

	UFUNCTION()
		void OnClickFlashCharButton();

	UFUNCTION()
		void OnHoverFlashCharButton();

	UFUNCTION()
		void OnClickWallCharButton();

	UFUNCTION()
		void OnHoverWallCharButton();

	UFUNCTION()
		void OnClickStartGameButton();

	UFUNCTION()
		void OnClickBackButton();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;


	TArray<AActor*> FoundActors;

	class ACharacterDisplayPawn* CharDisplayPawn;

	UFUNCTION()
	 void HandleTextBoxCommitted(const FText& Text, ETextCommit::Type CommitType) ;
	/*const FText& Text, ETextCommit::Type CommitType*/

	class UMyShooterGameInstance* MyShooterGameInstance;

	ECharSelectStatus CharSelectStatus = ECharSelectStatus::CSS_None;
};
