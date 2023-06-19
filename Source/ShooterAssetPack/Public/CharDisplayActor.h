// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharDisplayActor.generated.h"

UCLASS()
class SHOOTERASSETPACK_API ACharDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharDisplayActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



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

	UAnimInstance* WCAnimInstance;

	UAnimInstance* FCAnimInstance;

	
	TSubclassOf<class UAnimInstance>* ShooterAnimInstance;

	class UShooterCharacterAnimInstance* WCShooterCharacterAnimInstance;

	class UShooterCharacterAnimInstance* FCShooterCharacterAnimInstance;

public:

	void FCShow();

	void FCHide();

	void WCShow();
	
	void WCHide();
};
