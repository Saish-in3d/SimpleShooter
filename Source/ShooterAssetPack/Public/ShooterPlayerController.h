// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 *  
 */
UCLASS()
class SHOOTERASSETPACK_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// can be used to focus at actor of intrest and runs logic for winner widget.
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UFUNCTION(BlueprintNativeEvent)
		void ClearHUD(); 

	UFUNCTION()
	UUserWidget* SetPauseWidget();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FTimerHandle RestartTimer;

	float RestartDelay = 5.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinWidgetClass;

	class UUserWidget* CrosshairWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrosshairWidgetClass;

	//clears HUD after game ends.
	virtual void ClearHUD_Implementation();

	//Returns to main menu level and supporting widgets 
	UFUNCTION()
	void OpenMainMenu();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PauseWidgetClass;

	UUserWidget* PauseWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UUserWidget* HUDWidget;

	class UTimeSaveGame* TimeSaveGameObject;

	TArray<uint8> ConvertStructArrayToByteArray(const TArray< struct FDataPlayer>& StructArray);

	TArray<uint8> SerializeUObject(class UDataObject* Object);

	class AShooterCharacter* ShooterChar;

	float TimeScore;

	UTimeSaveGame* TimeSaveGameInstance;
};
