// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharacterDisplayPawn.generated.h"

UCLASS()
class SHOOTERASSETPACK_API ACharacterDisplayPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterDisplayPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void FCShow();

	UFUNCTION()
	void FCHide();

	UFUNCTION()
	void WCShow();

	UFUNCTION()
	void WCHide();

	UFUNCTION()
	void GetSC();

	UFUNCTION()
	void GetWC();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* FlashCharMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WallCharMesh;

private:	

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CharSelectWidgetClass;

	class UUserWidget* CharSelectWidget;

	class UAnimInstance* WCAnimInstance;

	class UAnimInstance* FCAnimInstance;

	TSubclassOf<class UAnimInstance>* ShooterAnimInstance;

	class UShooterCharacterAnimInstance* WCShooterCharacterAnimInstance;

	class UShooterCharacterAnimInstance* FCShooterCharacterAnimInstance;

	class USphereComponent* SphereComponent;

	TArray<AActor*> FoundActors;

	class AIronShooterCharacter* WCChar;

	class AFireCharacter* SCChar;

	class UMyShooterGameInstance* MyShooterGameInstance;

};
