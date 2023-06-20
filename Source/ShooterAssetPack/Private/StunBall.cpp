// Fill out your copyright notice in the Description page of Project Settings.


#include "StunBall.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/PostProcessVolume.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "ShooterAIController.h"
#include "ShooterInterface.h"
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
	GetWorld()->GetTimerManager().SetTimer(StunBeginTimerHandle, this, &AStunBall::StunProcess, 0.05f, false);

}

void AStunBall::StunProcess()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	for (AActor* FoundActor : FoundActors)
	{
		PostProcessVolume = Cast<APostProcessVolume>(FoundActor);
		if (PostProcessVolume)
		{
			break;
		}
	}
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ShooterChar = Cast<AShooterCharacter>(PlayerPawn);
	if (PostProcessVolume)
	{
		OriginalSettings = PostProcessVolume->Settings;
		if (StunOn1 == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Testing Test"));

			FlashSettings.BloomIntensity = 250.f;
			PostProcessVolume->Settings = FlashSettings;
			ShooterChar->IsStunned = true;
			IShooterInterface* ShooterInterface = Cast<IShooterInterface>(ShooterChar);
			if (ShooterInterface)
			{
				ShooterInterface->Execute_StunFunction2(ShooterChar);
				GetWorld()->GetTimerManager().SetTimer(StunTimerHandle3sec, this, &AStunBall::StunTimeEnds, 3.f, false);

			}

		}
		else if (StunOn1 == false)
		{
			IShooterInterface* ShooterInterface = Cast<IShooterInterface>(ShooterChar);
			if (ShooterInterface)
			{
				ShooterInterface->Execute_StunFunction2(ShooterChar);
				GetWorld()->GetTimerManager().SetTimer(NoStunTimerHandle3sec, this, &AStunBall::NoStunTimeEnds, 3.f, false);

			}
		}

	}


}

void AStunBall::StunFunction2_Implementation()
{
	FCollisionQueryParams TraceParams(FName(TEXT("MultiSphereTrace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	// Array of objects to trace against
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	// Start and end locations of the trace
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() + FVector(1.f, 0.f, 0.f);

	// Radius of the sphere
	float SphereRadius = 50000.f;

	// Perform the multi-sphere trace
	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByObjectType(OutHits, StartLocation, EndLocation, FQuat::Identity, ObjectTypes, FCollisionShape::MakeSphere(SphereRadius), TraceParams);

	// Process the hit results
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			// Access the hit result properties
			AActor* HitActor = Hit.GetActor();
			AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(HitActor);
			if (ShooterCharacter)
			{
				AShooterAIController* ShooterAIController = Cast<AShooterAIController>(ShooterCharacter->GetController());
				if (ShooterAIController)
				{
					IShooterInterface* ShooterInterface = Cast<IShooterInterface>(HitActor);
					if (ShooterInterface)
					{
						ShooterInterface->Execute_Stun2(ShooterAIController, ShooterAIController);
					}
				}
			}

		}
	}
}

void AStunBall::StunTimeEnds()
{
	PostProcessVolume->Settings = OriginalSettings;
	ShooterChar->IsStunned = false;
	Destroy();

}

void AStunBall::NoStunTimeEnds()
{
	Destroy();
}

// Called every frame
void AStunBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StunOn1 = WasRecentlyRendered(0.1f);
}

AStunBall::~AStunBall()
{

}

