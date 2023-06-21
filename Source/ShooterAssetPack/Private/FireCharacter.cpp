// Fill out your copyright notice in the Description page of Project Settings.


#include "FireCharacter.h"

void AFireCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("StunChar");

}
