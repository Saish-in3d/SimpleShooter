// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
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

	if (WallComponent)
	{
		
		
		WallMaterial = WallComponent->GetMaterial(0);
		if (WallMaterial == nullptr) { return; }
		DynamicWallMaterial = UMaterialInstanceDynamic::Create(WallMaterial, NULL);
		if (DynamicWallMaterial)
		{
			WallComponent->SetMaterial(0, DynamicWallMaterial);
		}
	}

}

float AExpandingWall::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (HealthComponent == nullptr) { return 0.0f; }
	HealthComponent->ReduceHealth(DamageAmount);
	
	return 0.0f;
}

// Called every frame
void AExpandingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthComponent == nullptr) { return ; }
	
	ChangeColor(HealthComponent->GetAlpha());
	//ChangeColor(0.5f);
}

void AExpandingWall::ChangeColor(float Alpha)
{
	if (DynamicWallMaterial)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
		DynamicWallMaterial->SetScalarParameterValue(TEXT("Blend"), Alpha);
	}
}

