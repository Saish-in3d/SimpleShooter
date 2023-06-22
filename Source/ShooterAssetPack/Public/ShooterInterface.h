// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShooterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UShooterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTERASSETPACK_API IShooterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
		virtual void StunFunction2() {};

	UFUNCTION(BlueprintNativeEvent)
	void Stun2(class AShooterAIController* SAIC);
};
