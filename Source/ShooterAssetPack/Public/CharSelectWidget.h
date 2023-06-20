// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UCharSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
		class UButton* FlashCharButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* WallCharButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* StartGameButton;

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

	//TSubclassOf<ACharacter*> CharacterDisplayClass;

	//TArray<ACharacter*> CharacterDisplayClass;

	TArray<AActor*> FoundActors;

	class ACharacterDisplayPawn* CharDisplayPawn;
};