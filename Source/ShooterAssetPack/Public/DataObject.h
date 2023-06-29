// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataPlayer.h"
#include "DataObject.generated.h"

/**
 * 
 */ 
UCLASS(BlueprintType, Blueprintable)
class SHOOTERASSETPACK_API UDataObject : public UObject
{
	GENERATED_BODY()

public:

	UDataObject();

	FString PlayerName;

	float PlayerTime;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
	TArray< FDataPlayer> PlayerDataSet1;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
		TArray<FString> PlayerNameArray;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
		TArray<float> PlayerScoreArray;
	
};
