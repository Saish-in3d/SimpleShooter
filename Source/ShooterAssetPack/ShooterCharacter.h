// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTERASSETPACK_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Shoot();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	virtual void Ability();

	void ReduceGunAmmo();

	bool IsReloading = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, category = "Basic", meta = (AllowPrivateAccess = "true"))
	USceneComponent* BallProjectileSpawnPoint;

private:	
	void MoveForward(float Value);
	
	void MoveRight(float Value);





	UPROPERTY()
	class AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;



	UPROPERTY(EditAnywhere)
	float MaxHealth = 50;

	float Health;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
	float MaxGunAmmo = 30.f;

	float GunAmmo;

	UPROPERTY(EditAnywhere)
	float BodyAmmo = 60.f;

	

	void CheckAndReloadGunAmmo();

	 

	UFUNCTION()
	void AddMaxAmmo();

	FTimerHandle ReloadDelay;

	UFUNCTION(BlueprintPure)
	float GetBodyAmmo();

	UFUNCTION(BlueprintPure)
	float GetGunAmmo();

	
	
};
