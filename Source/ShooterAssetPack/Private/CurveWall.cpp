// Fill out your copyright notice in the Description page of Project Settings.


#include "CurveWall.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "ExpandingWall.h"
#include "Kismet/GameplayStatics.h"
#include "StunBall.h"
#include "IronShooterCharacter.h"
#include "FireCharacter.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
ACurveWall::ACurveWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	RootComponent = ProjectileMesh;
	
	ShooterChar = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

// Called when the game starts or when spawned
void ACurveWall::BeginPlay()
{
	Super::BeginPlay();
	if (ShooterChar)
	{

		CurveAmount = ShooterChar->GetCurveAmount();
		//UE_LOG(LogTemp, Warning, TEXT("MyFloat: %f"), CurveAmount);
	}
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACurveWall::OnHit);

	FVector RightVector = FVector::RightVector; // Right vector for curve direction

	StartRotation = GetActorRotation().Quaternion(); // Initial rotation of the projectile

	// Calculate the target rotation with the desired curve to the right
	FRotator TargetRotation = GetActorRotation() + FRotator(0.0f, CurveAmount, 0.0f);
	 EndRotation = TargetRotation.Quaternion(); // Target rotation in quaternion form

	 
	

}


// Called every frame
void ACurveWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Alpha <= 1.f ) { InitCB(); }

}



void ACurveWall::InitCB()
{


	// Interpolate between the start and end rotations using Slerp
	Alpha += 0.022;
	FQuat InterpolatedRotation = FQuat::Slerp(StartRotation, EndRotation, Alpha); 
	SetActorRotation(InterpolatedRotation);

	// Moving actor in the direction of forward vector achieveing curved trajectory
	FVector CurrentTargetLocation = NewTargetLocation;
	AddActorWorldOffset(CurrentTargetLocation);
	NewTargetLocation =   GetActorForwardVector() * 0.5f + CurrentTargetLocation;

	if (Alpha >= 0.95f) 
	{ 
		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();
		AIronShooterCharacter* IronShooterCharacter = Cast<AIronShooterCharacter>(ShooterChar);
		AFireCharacter* FireCharacter = Cast<AFireCharacter>(ShooterChar);

		if(ExpWallClass && IronShooterCharacter)
		{
			auto ExpWall = GetWorld()->SpawnActor<AExpandingWall>(ExpWallClass, Location, Rotation);
			ExpWall->SetOwner(this);
			Destroy();
		}
		if (StunBallClass && FireCharacter)
		{
			auto StunBall = GetWorld()->SpawnActor<AStunBall>(StunBallClass, Location, Rotation);
			StunBall->SetOwner(this);
			//Stun other players
			Destroy();
		}
	}




	
}
//if ball hits wall 
void ACurveWall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("test"));
	ShooterChar->IsCurveBallReleased = false;
	Destroy();
}












































