// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacterAnimInstance.h"
#include "CharacterDisplayPawn.h"
#include "CharDisplayActor.h"

// Sets default values
ACharDisplayActor::ACharDisplayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlashCharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FlashCharMesh"));
	WallCharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WallCharMesh"));
	if(FlashCharMesh && WallCharMesh)
	{
		RootComponent = FlashCharMesh;
		WallCharMesh->SetupAttachment(GetRootComponent());

		WCAnimInstance = WallCharMesh->GetAnimInstance();
		FCAnimInstance = FlashCharMesh->GetAnimInstance();

		WCShooterCharacterAnimInstance = Cast<UShooterCharacterAnimInstance>(WCAnimInstance);
		FCShooterCharacterAnimInstance = Cast<UShooterCharacterAnimInstance>(FCAnimInstance);
		//FCAnimInstance
	}


}

// Called when the game starts or when spawned
void ACharDisplayActor::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController)
	{
		CharSelectWidget = CreateWidget(PlayerController, CharSelectWidgetClass);
		if (CharSelectWidget)
		{
			CharSelectWidget->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void ACharDisplayActor::FCShow()
{
	FlashCharMesh->SetHiddenInGame(false);
	if (WCShooterCharacterAnimInstance)
	{
		WCShooterCharacterAnimInstance->IsInAir1 = true;
	}
}

void ACharDisplayActor::FCHide()
{
	FlashCharMesh->SetHiddenInGame(true);
	
}

void ACharDisplayActor::WCShow()
{
	WallCharMesh->SetHiddenInGame(false);
	if (FCShooterCharacterAnimInstance)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
		FCShooterCharacterAnimInstance->IsInAir1 = true;
	}
}

void ACharDisplayActor::WCHide()
{
	WallCharMesh->SetHiddenInGame(true);
	
}

// Called every frame
void ACharDisplayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

