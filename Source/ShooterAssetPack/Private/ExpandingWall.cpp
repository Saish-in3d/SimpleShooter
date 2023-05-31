// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "ExpandingWall.h"

// Sets default values
AExpandingWall::AExpandingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wall"));
	RootComponent = WallComponent;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComp"));

}

// Called when the game starts or when spawned
void AExpandingWall::BeginPlay()
{
	Super::BeginPlay();

}

float AExpandingWall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HealthComponent->ReduceHealth(DamageAmount);
	return 0.0f;
}

// Called every frame
void AExpandingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

