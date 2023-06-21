// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "FireCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AFireCharacter : public AShooterCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
