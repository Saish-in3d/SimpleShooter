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

	virtual void ClearHUD_Implementation();

	UFUNCTION()
	void OpenMainMenu();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PauseWidgetClass;

	UUserWidget* PauseWidget;


};
