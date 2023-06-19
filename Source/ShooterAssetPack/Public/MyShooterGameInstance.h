// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "MyShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UMyShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	 AShooterCharacter* Character1 ;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	//AShooterCharacter& Character1Ref = Character1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	TSubclassOf<ACharacter> CharacterClass;

};
