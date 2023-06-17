// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UMyShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	ACharacter* Character1;
};
