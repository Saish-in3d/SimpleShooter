// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include"Components/PrimitiveComponent.h"
#include "SupportPack.h"
#include "ShooterPlayerController.h"
#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimeSaveGame.h"
#include "CurveWall.h"
#include "CharSelectWidget.h"
#include "DataPlayer.h"
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

float AShooterCharacter::SetTime()
{
	float TimeSinceSpawn = GetWorld()->GetTimeSeconds();
	return TimeSinceSpawn;
}

void AShooterCharacter::SetAIShallShoot(bool value)
{
	AIShallShoot = value;
}

bool AShooterCharacter::GetAIShallShoot()
{
	return AIShallShoot;
}

FDataPlayer AShooterCharacter::GetDataPlayer(FDataPlayer DP)
{

	return DP;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
	

	Health = MaxHealth;

	GunAmmo = MaxGunAmmo;

	AShooterAIController* AIShooterController = Cast<AShooterAIController>(GetController());
	if (AIShooterController)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		if(Gun)
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));
			Gun->SetOwner(this);
		}
	}

	if (TimeSaveGameObject == nullptr)
	{
		TimeSaveGameObject = Cast<UTimeSaveGame>(UGameplayStatics::CreateSaveGameObject(WowGameClass));
		//UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
		UGameplayStatics::SaveGameToSlot(TimeSaveGameObject, TEXT("PlayerName"), 0);
		
	}

	/*for (FDataPlayer SinglePlayerData : MyShooterGameInstance->PlayerDataSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("test"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SinglePlayerData.DataPlayeName.ToString());

	}*/

	Test();
	//PlayerName = GetName();
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooterCharacter::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetWidgetToFocus(nullptr);
		PlayerController->SetInputMode(InputMode);
		ShooterPlayerController = Cast<AShooterPlayerController>(PlayerController);
		if (ShooterPlayerController)
		{
			PauseWidget = ShooterPlayerController->SetPauseWidget();
		}
	}
	
}

void AShooterCharacter::SetCurveAmount()
{
	if (CurveAmount == -90.f)
	{
		CurveAmount = 90.f;
		return;
	}
	CurveAmount -= 90.f;
}

void AShooterCharacter::Test()
{
	bool DoesSlotExists = UGameplayStatics::DoesSaveGameExist(FString("NameTimeSlot"), 0);
	if(DoesSlotExists && TimeSaveGameObject)
	{
		TimeSaveGameObject->Timegg = SetTime();

		PlayerName = TimeSaveGameObject->PlayerName;

		

		UGameplayStatics::SaveGameToSlot(TimeSaveGameObject, TEXT("TimeSaveSlot"), 0);
		UE_LOG(LogTemp, Warning, TEXT("Testing Test"));
	}
}

float AShooterCharacter::GetCurveAmount()
{
	
	return CurveAmount;
}

void AShooterCharacter::Shoot()
{
	if(OverlappingGun)
	{
		OverlappingGun->PullTrigger();
	}
}

void AShooterCharacter::AIShoot()
{
	if (Gun)
	{
		Gun->PullTrigger();
	}
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::ProjectileCurveAbility()
{
	FVector ProjectileSpawnPointLocation = BallProjectileSpawnPoint->GetComponentLocation();

	FVector Location = BallProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = BallProjectileSpawnPoint->GetComponentRotation();

	if(IsStunned == false && IsCurveBallReleased == false)
	{
		
		auto Projectile = GetWorld()->SpawnActor<ACurveWall>(BallClass, Location, Rotation);
		if (Projectile)
		{
			if (ActorHasTag(FName("StunChar")))
			{
				IsCurveBallReleased = true;
			}
			Projectile->SetOwner(this);
		}
	}
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
	
	if (GunAmmo == 0.f&& IsBodyAmmoPresent && !IsReloading && OverlappingGun)
	{
		IsReloading = true;
		OverlappingGun->PlayReloadSound();
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

FText AShooterCharacter::GetDirection()
{
	if(CurveAmount == 90.f)
	{
		return FText::FromString(TEXT("Right"));
	}
	else if (CurveAmount == 0.f)
	{
		return FText::FromString(TEXT("Front"));
	}
	else if (CurveAmount == -90.f)
	{
		return FText::FromString(TEXT("Left"));
	}
	return FText::FromString(TEXT("Null"));
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

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckAndReloadGunAmmo();
	CheckBodyAmmoLevel();
	CheckGunAmmoLevel();
	SetTime();
	//UE_LOG(LogTemp, Warning, TEXT("Hello, World!"));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), &PlayerName);
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
	PlayerInputComponent->BindAction(TEXT("Ability"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ProjectileCurveAbility);
	PlayerInputComponent->BindAction(TEXT("PickGun"), EInputEvent::IE_Pressed, this, &AShooterCharacter::EquipGun);
	PlayerInputComponent->BindAction(TEXT("Pause"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PauseGame);
	PlayerInputComponent->BindAction(TEXT("CurveChange"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SetCurveAmount);
}

bool AShooterCharacter::IsDead() const
{
	if (Health <= 5.f)
	{
		return true;
	}
	else return false;
}