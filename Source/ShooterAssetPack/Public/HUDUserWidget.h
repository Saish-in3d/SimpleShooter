// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class SHOOTERASSETPACK_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
		virtual bool Initialize() override;

		virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
		
private:

	UPROPERTY()
	class AShooterCharacter* ShooterChar;

	UPROPERTY(EditAnywhere)
	class UTextBlock* BodyAmmoTB;

	void SetBodyAmmoTB();

	UPROPERTY(EditAnywhere)
	class UTextBlock* GunAmmoTB;

	void SetGunAmmoTB();

	UPROPERTY(EditAnywhere)
	class UTextBlock* DirectionTB;

	void SetDirectionTB();

	UPROPERTY(EditAnywhere)
	class UTextBlock* TimevalueTB;

	UPROPERTY(EditAnywhere)
	class UTextBlock* NamevalueTB;
	
	void SetTimevalueTB();

	UPROPERTY(EditAnywhere)
	class UProgressBar* HealthProgressBar;

	void SetHealthProgressBar();



		 


};
