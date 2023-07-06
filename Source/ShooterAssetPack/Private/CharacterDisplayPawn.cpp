// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacterAnimInstance.h"
#include "Components/SphereComponent.h"
#include "FireCharacter.h"
#include "IronShooterCharacter.h"
#include "MyShooterGameInstance.h"
#include "CharacterDisplayPawn.h"

// Sets default values
ACharacterDisplayPawn::ACharacterDisplayPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlashCharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FlashCharMesh"));
	WallCharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WallCharMesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (SphereComponent && FlashCharMesh && WallCharMesh)
	{
		RootComponent = SphereComponent;
		WallCharMesh->SetupAttachment(SphereComponent);
		//WallCharMesh->SetHiddenInGame(true);
		FlashCharMesh->SetupAttachment(SphereComponent);
		//FlashCharMesh->SetHiddenInGame(true);
		
		//FCAnimInstance
	}




}

// Called when the game starts or when spawned
void ACharacterDisplayPawn::BeginPlay()
{
	Super::BeginPlay();
	if (FlashCharMesh && WallCharMesh)
	{
		WCAnimInstance = WallCharMesh->GetAnimInstance();
		FCAnimInstance = FlashCharMesh->GetAnimInstance();
	}
	if (WCAnimInstance && FCAnimInstance)
	{
		WCShooterCharacterAnimInstance = Cast<UShooterCharacterAnimInstance>(WCAnimInstance);
		FCShooterCharacterAnimInstance = Cast<UShooterCharacterAnimInstance>(FCAnimInstance);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		CharSelectWidget = CreateWidget(PlayerController, CharSelectWidgetClass);
		if (CharSelectWidget)
		{
			CharSelectWidget->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		WCChar = Cast<AIronShooterCharacter>(FoundActor);
		if (WCChar)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
			MyShooterGameInstance = Cast<UMyShooterGameInstance>(WCChar->GetGameInstance());
			break;
			
		}
		
	}
	for (AActor* FoundActor : FoundActors)
	{
		SCChar = Cast<AFireCharacter>(FoundActor);
		if (SCChar)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
			break;

		}

	}
	
	
}

// Called every frame
void ACharacterDisplayPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterDisplayPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterDisplayPawn::FCShow()
{
	FlashCharMesh->SetHiddenInGame(false);
	FCShooterCharacterAnimInstance->IsInAir1 = false;
	if (WCShooterCharacterAnimInstance)
	{
		WCShooterCharacterAnimInstance->IsInAir1 = true;
	}
}

void ACharacterDisplayPawn::FCHide()
{
	FlashCharMesh->SetHiddenInGame(true);
}

void ACharacterDisplayPawn::WCShow()
{
	WallCharMesh->SetHiddenInGame(false);
	WCShooterCharacterAnimInstance->IsInAir1 = false;
	if (FCShooterCharacterAnimInstance)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
		FCShooterCharacterAnimInstance->IsInAir1 = true;
	}
}

void ACharacterDisplayPawn::WCHide()
{
	WallCharMesh->SetHiddenInGame(true);
}

void ACharacterDisplayPawn::GetSC()
{
	
	if (MyShooterGameInstance && SCChar)
	{
		
		MyShooterGameInstance->CharacterClass = SCChar->GetClass();
		//FString Message1 = MyShooterGameInstance->CharacterClass->GetFName().ToString();
		//UE_LOG(LogTemp, Warning, TEXT("Your message here %s"), *Message1);
	}
}

void ACharacterDisplayPawn::GetWC()
{
	
	if (MyShooterGameInstance && WCChar)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Your message here"));
		MyShooterGameInstance->CharacterClass = WCChar->GetClass();
		
	}
}

