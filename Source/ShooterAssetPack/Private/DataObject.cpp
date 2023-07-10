// Fill out your copyright notice in the Description page of Project Settings.

#include "DataObject.h"
#include "TimeSaveGame.h"
#include "Kismet/GameplayStatics.h"


UDataObject::UDataObject()
{
	UTimeSaveGame* TimeSaveGameInstance = Cast<UTimeSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("FinalSaveSlot"), 0));
	if (TimeSaveGameInstance)
	{
		//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard loop Name is %s"), *TimeSaveGameInstance->SavedPlayerDataArray[0]);
		for (int32 i = 0; i < TimeSaveGameInstance->SavedPlayerDataArray.Num(); i++)
		{
			if (i % 2 == 0)
			{
				PlayerNameArray.Add(TimeSaveGameInstance->SavedPlayerDataArray[i]);
			}
			else
			{
				float FloatValue = FCString::Atof(*TimeSaveGameInstance->SavedPlayerDataArray[i]);
				PlayerScoreArray.Add(FloatValue);
			}

		}

		/*for (const FString String : PlayerNameArray)
		{
			//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard test"));
			UE_LOG(LogTemp, Warning, TEXT("DO final loop Name is %s"), *String);
		}
		for (const float String : PlayerScoreArray)
		{
			//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard test"));
			UE_LOG(LogTemp, Warning, TEXT("DO final loop time is %f"), String);
		}*/ 

	}
}

