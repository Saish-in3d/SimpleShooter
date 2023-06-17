// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	virtual bool Initialize() ;
	

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* LeaderBoardButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGame;

private:
	UFUNCTION()
	void OnClickStartGameButton();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CharSelectWidgetClass;

	UUserWidget* CharSelectWidget;

	UFUNCTION()
	void OnClickLeaderBoardButton();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LeaderBoardWidgetClass;

	UFUNCTION()
	void OnClickExitGameButton();
};
