// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataObject.h"
#include "LeaderBoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API ULeaderBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize();

	virtual void NativeConstruct() override;

private:

	UDataObject* DeserializeUObject(const TArray<uint8>& SerializedData);

	TArray<FString> PlayerNameArray;

	TArray<float> PlayerScoreArray;

	
};
