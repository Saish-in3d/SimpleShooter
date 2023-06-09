// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "MyShooterGameInstance.h"


bool UHUDUserWidget::Initialize()
{
	Super::Initialize();

	ShooterChar = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0.f));

	BodyAmmoTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("BodyAmmo")));
	GunAmmoTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("GunAmmo")));
	DirectionTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Direction")));
	TimevalueTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Timevalue")));
	NamevalueTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameValue")));
	HealthProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthProgressBar1")));
	UMyShooterGameInstance * MyShooterGameInstance = Cast<UMyShooterGameInstance>(GetGameInstance());
	if (NamevalueTB && MyShooterGameInstance)
	{
		NamevalueTB->SetText(FText::FromString(MyShooterGameInstance->PlayerNameValue));
	}

	return true;
}

void UHUDUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ShooterChar == nullptr)
	{
		ShooterChar = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0.f));
	}
	if (ShooterChar == nullptr) { return; }

	SetBodyAmmoTB();
	SetGunAmmoTB();
	SetDirectionTB();
	SetTimevalueTB();
	SetHealthProgressBar();


}

void UHUDUserWidget::SetBodyAmmoTB()
{
	if (BodyAmmoTB)
	{
		BodyAmmoTB->SetText(FText::FromString(FString::SanitizeFloat(ShooterChar->GetBodyAmmo())));
	}
}

void UHUDUserWidget::SetGunAmmoTB()
{
	if (GunAmmoTB)
	{
		GunAmmoTB->SetText(FText::FromString(FString::SanitizeFloat(ShooterChar->GetGunAmmo())));
	}
}

void UHUDUserWidget::SetDirectionTB()
{
	if (DirectionTB)
	{
		DirectionTB->SetText(ShooterChar->GetDirection());
	}
}

void UHUDUserWidget::SetTimevalueTB()
{
	if (TimevalueTB)
	{
		TimevalueTB->SetText(FText::FromString(FString::SanitizeFloat(ShooterChar->SetTime())));
	}
}

void UHUDUserWidget::SetHealthProgressBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(ShooterChar->GetHealthPercent());
	}
}
