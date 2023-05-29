// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "IronShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AIronShooterCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	AIronShooterCharacter();

	virtual void Ability() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UClass* BallClass;

};
