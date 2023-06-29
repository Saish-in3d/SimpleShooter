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

private:

	class UDataObject* ConstructDataObject();

	UPROPERTY()
	class UScoreEntryWidget* ScoreEntryWidget;


	
};
