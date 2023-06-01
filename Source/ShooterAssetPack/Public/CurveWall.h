// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveWall.generated.h"

UCLASS()
class SHOOTERASSETPACK_API ACurveWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACurveWall();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;




private:	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	float CurveAmount = -90.0f; // Amount of curve applied to the right

	void InitCB();

	FQuat StartRotation;

	FQuat EndRotation;
	
	float Alpha = 0.f;

	FVector NewTargetLocation = GetActorLocation() ;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	class UClass* ExpWallClass;
};