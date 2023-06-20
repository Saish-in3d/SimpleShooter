// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"
#include "MyShooterGameInstance.h"
#include "GameFramework/PlayerStart.h"

#include "SandBoxScriptActor.h"

void ASandBoxScriptActor::BeginPlay()
{
	
	ShooterPlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (ShooterPlayerController)
	{
		UMyShooterGameInstance* MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
		if (MyShooterGameInstance)
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
			for (AActor* FoundActor : FoundActors)
			{
				PlayerStart = Cast<APlayerStart>(FoundActor);
				if (PlayerStart)
				{
					break;
				}
			}
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			UClass* CharacterClass = MyShooterGameInstance->CharacterClass;
			if (CharacterClass)
			{
				SpawnedCharacter = GetWorld()->SpawnActor<AShooterCharacter>(CharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams);
				if (SpawnedCharacter)
				{
					ShooterPlayerController->Possess(SpawnedCharacter);
				}
			}
		}
	}
}

void ASandBoxScriptActor::Tick(float DeltaTime)
{
	if (ShooterPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("controller null"));
	}
	if (SpawnedCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawned actor null"));
	}
}
