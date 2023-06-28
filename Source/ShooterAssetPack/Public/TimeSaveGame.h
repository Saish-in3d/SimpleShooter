// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DataPlayer.h"
#include "TimeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UTimeSaveGame : public USaveGame
{
	GENERATED_BODY()
	


public:

	TArray<float> TimeArray;

	float Timegg;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
	FString PlayerName;

	TArray<uint8> SerializedPlayerData;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
	TArray<FString> SavedPlayerDataArray;


};
