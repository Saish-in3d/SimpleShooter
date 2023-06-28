// Fill out your copyright notice in the Description page of Project Settings.


#pragma once


#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterAssetPack/ShooterCharacter.h"
#include "Templates/SharedPointer.h"
#include "DataPlayer.h"
#include "Containers/Array.h"
#include "MyShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UMyShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMyShooterGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	 AShooterCharacter* Character1 ;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	//AShooterCharacter& Character1Ref = Character1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	TSubclassOf<ACharacter> CharacterClass;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyGameInstance")
	FDataPlayer* DataGetter = new FDataPlayer();*/

	UPROPERTY()
	FDataPlayer DataGetter ;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
		TArray< FDataPlayer> PlayerDataSet;


	UPROPERTY()
	class UDataObject* PlayerDataObject;

	UPROPERTY(Blueprintreadwrite, EditAnywhere)
		TArray< UDataObject*> PlayerDataObjects;

	//DataGetter* DataGetterPTR = new FDataPlayer();

	/*UPROPERTY()
	TSharedPtr< struct FDataPlayer> DataGetter;*/

	TArray<FString> PlayerDataArray;
	
	FString Player1;

};
