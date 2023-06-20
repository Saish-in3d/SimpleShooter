// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StunBall.generated.h"

UCLASS()
class SHOOTERASSETPACK_API AStunBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStunBall();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	~AStunBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BallMesh;

	FTimerHandle StunBeginTimerHandle;

	void StunProcess();

	TArray<AActor*> FoundActors;

	class APostProcessVolume* PostProcessVolume;

	class AShooterCharacter* ShooterChar;

	FPostProcessSettings OriginalSettings;

	bool StunOn1= false;

	FPostProcessSettings FlashSettings;

	virtual void StunFunction2_Implementation() ;

	FTimerHandle StunTimerHandle3sec;

	void StunTimeEnds();

	FTimerHandle NoStunTimerHandle3sec;

	void NoStunTimeEnds();

};
