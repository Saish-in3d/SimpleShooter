// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UShooterCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsInAir1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APawn* OwnerPawn;

	UFUNCTION(BlueprintPure)
		APawn* GetOwnerPawn1();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NativeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NativeAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool NativeIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NativePitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool NativeIsInAir;

private:
	APawn* NativeOwnerPawn;

	class AShooterCharacter* ShooterCharacter;
};
