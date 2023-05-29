// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

#include "ExpandingWall.h"

// Sets default values
AExpandingWall::AExpandingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallComponent = CreateDefaultSubobject<UStaticMeshComponent>("Wall");
	RootComponent = WallComponent;

	//ArrowComponent1 = CreateDefaultSubobject<UArrowComponent>("Up");
	//ArrowComponent1->SetWorldLocationAndRotation(GetActorLocation(), FRotator(0.f, 90.f, 0.f));
	//UArrowComponent* ArrowComponent2 = CreateDefaultSubobject<UArrowComponent>("Down");
	//UArrowComponent* ArrowComponent3 = CreateDefaultSubobject<UArrowComponent>("Left");
	//UArrowComponent* ArrowComponent4 = CreateDefaultSubobject<UArrowComponent>("Right");
}

// Called when the game starts or when spawned
void AExpandingWall::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UArrowComponent>(ArrowComponents);
	for (UArrowComponent* ArrowComponent : ArrowComponents)
	{
		FVector Start = ArrowComponent->GetComponentLocation();
		FVector End = ArrowComponent->GetForwardVector()*100000.f;
		FHitResult Output;
		FCollisionQueryParams Param;
		Param.AddIgnoredActor(this);
		Param.AddIgnoredActor(GetOwner());
		bool IsTraceSuccess = ActorLineTraceSingle(Output, Start, End, ECollisionChannel::ECC_Visibility, Param);
		if (IsTraceSuccess)
		{
			FVector Boundary = Output.Location;

		}
	}

}

// Called every frame
void AExpandingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

