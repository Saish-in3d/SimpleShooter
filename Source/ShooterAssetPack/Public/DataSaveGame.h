// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataPlayer.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DataSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UDataSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	class UMyShooterGameInstance* MyShooterGameInstance;



	
};
