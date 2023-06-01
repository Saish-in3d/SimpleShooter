// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include"Components/PrimitiveComponent.h"
#include "SupportPack.h"
#include "KillEmAllGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn");
	BallProjectileSpawnPoint->SetupAttachment(RootComponent);


}

void AShooterCharacter::PickUp(AGun* OverlappingGuntemp)
{
	if(OverlappingGuntemp)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		OverlappingGuntemp->AttachToComponent(GetMesh(), TransformRules, FName("WeaponSocket"));
		OverlappingGuntemp->SetOwner(this);
		OverlappingGuntemp->SetSphereCollision(false);
	}
}

void AShooterCharacter::SetOverlappingActor(AActor* OverlappingActorTemp)
{
	OverlappingActor = OverlappingActorTemp;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
	//Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	//Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));
	//Gun->SetOwner(this);

	

	Health = MaxHealth;

	GunAmmo = MaxGunAmmo;
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooterCharacter::Shoot()
{
	if(Gun)
	{
		Gun->PullTrigger();
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	
	return Health / MaxHealth;
}

void AShooterCharacter::Ability()
{

}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage( DamageAmount,   DamageEvent,  EventInstigator, DamageCauser);

	if(Health>= 0.f+ DamageApplied )
	{
		Health = Health - DamageApplied;
		//UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);
		
		if (IsDead())
		{
			
			ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
			if (GameMode)
			{
				GameMode->PawnKilled(this);
			}
			Die(); //Spawn SupportPack
			DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return DamageApplied;
}

void AShooterCharacter::ReduceGunAmmo()
{
	if(GunAmmo == 0.f)
	{
		return;
	}
	else
	{
		GunAmmo -= 1.f;
	}
}

void AShooterCharacter::AddHealth()
{
	if (Health <= 170.f)
	{
		float AddingHealth = 10.F * FMath::RandRange(1, 3);
		Health += AddingHealth;
		//add text to show health added
	}
}

void AShooterCharacter::AddAmmo()
{
	float AddingAmmo = 30.F * FMath::RandRange(1, 5);
	BodyAmmo += AddingAmmo;
	//ADD WIDGET TEXT
}

void AShooterCharacter::CheckAndReloadGunAmmo()
{
	
	if (GunAmmo == 0.f&& IsBodyAmmoPresent && !IsReloading && Gun) 
	{
		IsReloading = true;
		Gun->PlayReloadSound();
		// DELAY + FULL AMMO CALLBACK FUNCTION
		FTimerDelegate ReloadDelegate;
		ReloadDelegate.BindUFunction(this, FName("AddMaxAmmo"));
		GetWorld()->GetTimerManager().SetTimer(ReloadDelay, ReloadDelegate, 2.f, false);
	}
}

void AShooterCharacter::AddMaxAmmo()
{
	if(BodyAmmo >= 30)
	{
		GunAmmo = MaxGunAmmo;
		BodyAmmo -= MaxGunAmmo;
		IsReloading = false;
	}
}

float AShooterCharacter::GetBodyAmmo()
{
	return BodyAmmo;
}

float AShooterCharacter::GetGunAmmo()
{
	return GunAmmo;
}

void AShooterCharacter::CheckBodyAmmoLevel()
{
	if (BodyAmmo <= 0.f)
	{
		IsBodyAmmoPresent = false;
	}
	else
	{
		IsBodyAmmoPresent = true;
	}
}

void AShooterCharacter::CheckGunAmmoLevel()
{
	if (GunAmmo <= 0.f)
	{
		IsGunAmmoPresent = false;
	}
	else
	{
		IsGunAmmoPresent = true;
	}
	
}

void AShooterCharacter::Die()
{
	if(SupportPackClass)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActor = GetWorld()->SpawnActor<ASupportPack>(SupportPackClass, SpawnLocation, SpawnRotation);
	}
}



void AShooterCharacter::EquipGun()
{
	OverlappingGun = Cast<AGun>(OverlappingActor);
	if(OverlappingGun)
	{
		

		PickUp(OverlappingGun);
	}
}


	
	
	//UE_LOG(LogTemp, Warning, TEXT("Hello, World!"));




// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckAndReloadGunAmmo();
	CheckBodyAmmoLevel();
	CheckGunAmmoLevel();
	

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot); 
	PlayerInputComponent->BindAction(TEXT("Ability"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Ability);
	PlayerInputComponent->BindAction(TEXT("PickGun"), EInputEvent::IE_Pressed, this, &AShooterCharacter::EquipGun);
}

bool AShooterCharacter::IsDead() const
{
	if (Health <= 5.f)
	{
		
		return true;
	}
	else return false;
}

