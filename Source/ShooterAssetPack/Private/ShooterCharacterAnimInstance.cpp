// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAnimInstance.h"

APawn* UShooterCharacterAnimInstance::GetOwnerPawn1()
{
	return TryGetPawnOwner();
}
