// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderBoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API ULeaderBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "UI")
		class UListView* LeaderboardListView1;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

private:

	class UDataObject* ConstructDataObject();

	UPROPERTY()
	class UScoreEntryWidget* ScoreEntryWidget;

	UFUNCTION()
		void OnClickBackButton();

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

	UFUNCTION()
		void SetupLeaderBoardEntry();

	UPROPERTY()
	TArray<float> TimeValueArray;

	UPROPERTY()
	TArray<int64> IndexArray;

	int64 FindIndex(const TArray<float>& Array, float Value);
	
};
