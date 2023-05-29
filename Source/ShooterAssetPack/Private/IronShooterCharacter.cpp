// Fill out your copyright notice in the Description page of Project Settings.

#include "CurveWall.h"
#include "IronShooterCharacter.h"

AIronShooterCharacter::AIronShooterCharacter()
{

}

void AIronShooterCharacter::Ability()
{
	Super::Ability();
	FVector ProjectileSpawnPointLocation = BallProjectileSpawnPoint->GetComponentLocation();

	FVector Location = BallProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = BallProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<ACurveWall>(BallClass, Location, Rotation);
	Projectile->SetOwner(this);
}

void AIronShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
