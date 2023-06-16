// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
public:

	//Whenever a pawn dies in the game this function stores and works on the pawn object
	virtual void PawnKilled(APawn* PawnKilled) override;

protected:
	//gets all controllers in the world and checks for AI controllers and decides game winner
	void EndGame(bool bIsPlayerWinner);


};
