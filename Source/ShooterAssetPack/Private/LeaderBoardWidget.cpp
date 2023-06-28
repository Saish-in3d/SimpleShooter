// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DataPlayer.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "LeaderBoardWidget.h"



	bool ULeaderBoardWidget::Initialize()
	{
		Super::Initialize();
		return true;
	}

	void ULeaderBoardWidget::NativeConstruct()
	{
		Super::NativeConstruct();

		//UTimeSaveGame* TimeSaveGameInstance = Cast<UTimeSaveGame>(UGameplayStatics::CreateSaveGameObject(UTimeSaveGame::StaticClass()));
		UTimeSaveGame* TimeSaveGameInstance = Cast<UTimeSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("FinalSaveSlot"), 0));
		if (TimeSaveGameInstance)
		{
			//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard loop Name is %s"), *TimeSaveGameInstance->SavedPlayerDataArray[0]);
			for (int32 i = 0; i < TimeSaveGameInstance->SavedPlayerDataArray.Num(); i++)
			{
				if ( i % 2 == 0)
				{
					PlayerNameArray.Add(TimeSaveGameInstance->SavedPlayerDataArray[i]);
				}
				else
				{
					float FloatValue = FCString::Atof(*TimeSaveGameInstance->SavedPlayerDataArray[i]);
					PlayerScoreArray.Add(FloatValue);
				}

			}

			for (const FString String : PlayerNameArray)
			{
				//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard test"));
				UE_LOG(LogTemp, Warning, TEXT("LeaderBoard final loop Name is %s"), *String);
			}
			for (const float String : PlayerScoreArray)
			{
				//UE_LOG(LogTemp, Warning, TEXT("LeaderBoard test"));
				UE_LOG(LogTemp, Warning, TEXT("LeaderBoard final loop time is %f"), String);
			}
		}
	}

	UDataObject* ULeaderBoardWidget::DeserializeUObject(const TArray<uint8>& SerializedData)
	{
		UE_LOG(LogTemp, Warning, TEXT("DS test"));
		UDataObject* Object = nullptr;
		FMemoryReader MemoryReader(SerializedData);

		FObjectAndNameAsStringProxyArchive Ar(MemoryReader, true);
		Ar << Object;
		//FObjectReader ObjectReader(Object,SerializedData);
		
		//if(Object)

		return Object;
	}


