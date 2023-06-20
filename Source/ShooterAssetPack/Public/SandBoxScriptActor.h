// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SandBoxScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API ASandBoxScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	class AShooterPlayerController* ShooterPlayerController;

	TArray<AActor*>FoundActors;

	class APlayerStart* PlayerStart;

	class AShooterCharacter* SpawnedCharacter;
};
