// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "ShooterCharacterAnimInstance.h"

APawn* UShooterCharacterAnimInstance::GetOwnerPawn1()
{
	return TryGetPawnOwner();
}

void UShooterCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	NativeOwnerPawn = TryGetPawnOwner();

	if (NativeOwnerPawn == nullptr) { return; }
	NativeSpeed = NativeOwnerPawn->GetVelocity().Size2D();

	FVector LocalVector =   UKismetMathLibrary::InverseTransformDirection(NativeOwnerPawn->GetActorTransform(), NativeOwnerPawn->GetVelocity());
	NativeAngle =  UKismetMathLibrary::MakeRotFromX(LocalVector).Yaw;

	if (ShooterCharacter)
	{
		NativeIsDead = ShooterCharacter->IsDead();
	}

	NativePitch = UKismetMathLibrary::NormalizedDeltaRotator(NativeOwnerPawn->GetControlRotation(), NativeOwnerPawn->GetActorRotation()).Pitch;

	if (ShooterCharacter)
	{
		NativeIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();
	}

}

void UShooterCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());

}
