// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterInterface.h"
#include "DataPlayer.h"
#include "ShooterCharacter.generated.h"



UCLASS()
class SHOOTERASSETPACK_API AShooterCharacter : public ACharacter, public IShooterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//persistent check for character health
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	//Pulls trigger of the gun object
	void Shoot();

	//Pulls trigger of AI possessed gun
	void AIShoot();

	//Persistent health check for widget
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	//Spawns Projectile
	virtual void ProjectileCurveAbility();

	//Reduces single bullet after confirmed trigger action
	void ReduceGunAmmo();

	//persistent check for reload
	bool IsReloading = false;

	//adds random health to character in multiples of 10 when triggered
	void AddHealth();

	//adds random ammo to character in multiples of 30 when triggered
	void AddAmmo();

	//persistent check for body ammo 
	bool IsBodyAmmoPresent = true;

	//persistent check for gun ammo to enable auto relaod
	bool IsGunAmmoPresent = true;

	//Attaches gun to char skeletal mesh and sets owner
	void PickUp(class AGun* OverlappingGun);

	//Used when character overlaps with pickup item for getting overlapped object refrence in character class 
	void SetOverlappingActor(AActor* OverlappingActorTemp);

	//perdidtent check for time since spawn
	UFUNCTION(BlueprintPure)
	float SetTime();

	//Test Function to check high score
	void Test();

	//persistent check to get curve amount for widgets and curve calculations
	float GetCurveAmount();

	// bool indicates the stun status of AI controlled characters for AI Blackboard
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStunned = false;

	// bool indicates the stun status of AI controlled characters for AI Blackboard
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsCurveBallReleased = false;

	//
	void SetAIShallShoot(bool value);

	// Returns bool value which is used to set the shoot tick function in btt shoot
	bool GetAIShallShoot();


	//persistent returning of ammo values in blueprints for HUD
	UFUNCTION(BlueprintPure)
		float GetBodyAmmo();

	//persistent returning of ammo values in blueprints for HUD
	UFUNCTION(BlueprintPure)
		float GetGunAmmo();

	//persistent returning of curve direction in blueprints for HUD
	UFUNCTION(BlueprintPure)
		FText GetDirection();


	struct FDataPlayer GetDataPlayer(struct FDataPlayer DP);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
	USceneComponent* BallProjectileSpawnPoint;

private:	
	//character movement forward
	void MoveForward(float Value);
	
	//character movement left right
	void MoveRight(float Value);

	//
	class AGun* Gun;

	//Used For spawning object of AGun BP class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	//Used For spawning object of Ammo and health pickup BP class
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf< class ASupportPack> SupportPackClass;

	// Max Health at gamestart
	UPROPERTY(EditAnywhere)
	float MaxHealth = 50;

	//realtime health
	float Health;

	//Default actor function to handle damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	UPROPERTY(EditAnywhere)
	float MaxGunAmmo = 30.f;

	float GunAmmo;

	UPROPERTY(EditAnywhere)
	float BodyAmmo = 60.f;

	//Persistent checking of gun & body ammo level and run reload ammo function after some delay.
	void CheckAndReloadGunAmmo();

	//Function triggered after delay to add ammo to the gun and subtract from the body
	UFUNCTION()
	void AddMaxAmmo();

	FTimerHandle ReloadDelay;

	//Persistent checking of ammo level to regulate reload function
	void CheckBodyAmmoLevel();

	//Persistent checking of ammo level to regulate reload function
	void CheckGunAmmoLevel();

	//Spawns support pack when enemy death is triggered
	void Die();
	
	UPROPERTY(VisibleAnywhere)
	class AGun* OverlappingGun;

	void EquipGun();

	AActor* OverlappingActor;

	void PauseGame();

	class AShooterPlayerController* ShooterPlayerController;

	UUserWidget* PauseWidget;


	// High Score recording Start
	UPROPERTY(EditAnywhere)
	FString PlayerName;

	UPROPERTY(EditAnywhere)
	float TimeRecord;

	class UTimeSaveGame* TimeSaveGameObject;

	FString SaveSlotName;

	TSubclassOf<UTimeSaveGame> WowGameClass;
	// High Score recording Start

	// BP Class for curve projectile
	UPROPERTY(EditAnywhere)
	class UClass* BallClass;

	float CurveAmount = 90.f; 

	void SetCurveAmount();

	bool AIShallShoot = true;

	class UDataSaveGame* DataSaveGameObject;

	
};
