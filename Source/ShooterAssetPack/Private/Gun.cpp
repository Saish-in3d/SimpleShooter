// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
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

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGun::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGun::OnOverlapEnd);
	
}

void AGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* OverlappedShooterChar = Cast<AShooterCharacter>(OtherActor);
	if (OverlappedShooterChar)
	{
		OverlappedShooterChar->SetOverlappingActor(this);
		
	}
}

void AGun::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AShooterCharacter* OverlappedShooterChar = Cast<AShooterCharacter>(OtherActor);
	if (OverlappedShooterChar)
	{
		OverlappedShooterChar->SetOverlappingActor(nullptr);
		
	}
}

void AGun::PullTrigger()
{
	
	if (TriggerSound)
	{
		UGameplayStatics::SpawnSoundAttached(TriggerSound, GunMesh, TEXT("MuzzleFlashSocket"));
	}
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		
		AShooterCharacter* ShooterChar = Cast<AShooterCharacter>(GetOwner());
		if(ShooterChar && !ShooterChar->IsReloading && ShooterChar->IsGunAmmoPresent) 
		{

			GunTracing(OwnerPawn);
			if (MuzzleFlash && MuzzleSound)
			{

				UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
				UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
			}
			ShooterChar->ReduceGunAmmo();
		}

	}

	
}

void AGun::GunTracing(APawn* OwnerPawn)
{
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController)
	{
		FVector Location;
		FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location, Rotation);
		FVector End = Location + Rotation.Vector() * MaxRange;
		FHitResult Hit;
		FCollisionQueryParams Param;
		Param.AddIgnoredActor(this);
		Param.AddIgnoredActor(GetOwner());
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Param);
		if (bSuccess && BulletImpact && ImpactSound)
		{
			FVector ShotDirection = -Rotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, Hit.Location, Rotation); //ShotDirection.Rotation()
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);


			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}

		}

	}
}

void AGun::PlayReloadSound()
{
	if(ReloadSound)
	{
		UGameplayStatics::SpawnSoundAttached(ReloadSound, GunMesh, TEXT("MuzzleFlashSocket"));
	}
}

void AGun::SetSphereCollision(bool value)
{
	if (value == true)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else if (value == false)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

