// Fill out your copyright notice in the Description page of Project Settings.

#include "SupportPack.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASupportPack::ASupportPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PackMwsh = CreateDefaultSubobject<UStaticMeshComponent>(FName("PackMwsh"));
	RootComponent = PackMwsh;
}

// Called when the game starts or when spawned
void ASupportPack::BeginPlay()
{
	Super::BeginPlay();
	if (PackMwsh)
	{
		PackMwsh->OnComponentHit.AddDynamic(this, &ASupportPack::OnHit);
	}
	

	
	
}

void ASupportPack::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (ShooterCharacter)
	{
		int32  Value = FMath::RandRange(1, 2);
		switch (Value)
		{
        case 1:
			ShooterCharacter->AddAmmo();
            break;

        case 2:
			ShooterCharacter->AddHealth();
            break;

        default:
			ShooterCharacter->AddAmmo();
            break;
		}
	}
	Destroy();
}

// Called every frame
void ASupportPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

