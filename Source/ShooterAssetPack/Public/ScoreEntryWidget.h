// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ScoreEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UScoreEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void PrepData1(int64 Index);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:

	UPROPERTY( EditAnywhere)
	class UTextBlock* PlayerNameTB;

	UPROPERTY( EditAnywhere)
	class UTextBlock* PlayerTimeTB;

	void SetName(FString Name);
	
	void SetTime(float Time);

	UPROPERTY()
	TArray<FString> NameArray;

	UPROPERTY()
	TArray<float> TimeArray;

	FString PlayerName;

	float PlayerTime;


};
