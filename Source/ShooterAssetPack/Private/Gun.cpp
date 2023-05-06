// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		AController* OwnerController =  OwnerPawn->GetController();
		if (OwnerController)
		{
			FVector Location;
			FRotator Rotation;
			OwnerController->GetPlayerViewPoint(Location, Rotation);
		
			//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
			FVector End = Location + Rotation.Vector() * MaxRange;
			FHitResult Hit;
			bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
			if (bSuccess && BulletImpact)
			{
				//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
				FVector ShotDirection = -Rotation.Vector();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),BulletImpact, Hit.Location, Rotation); //ShotDirection.Rotation()

				AActor* HitActor = Hit.GetActor();
				if (HitActor )
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
					HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
				}

			}

		}
	}
}

