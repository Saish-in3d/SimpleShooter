// Fill out your copyright notice in the Description page of Project Settings.


#include "StunBall.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AStunBall::AStunBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh  = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	RootComponent = BallMesh;

}

// Called when the game starts or when spawned
void AStunBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStunBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AStunBall::~AStunBall()
{

}

