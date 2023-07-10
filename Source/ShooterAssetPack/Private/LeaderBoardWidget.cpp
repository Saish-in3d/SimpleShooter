// Fill out your copyright notice in the Description page of Project Settings.

#include "LeaderBoardWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "DataObject.h"
#include "ScoreEntryWidget.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "MainMenuWidget.h"





	void ULeaderBoardWidget::NativeConstruct()
	{
		Super::NativeConstruct();

		BackButton->OnClicked.AddDynamic(this, &ULeaderBoardWidget::OnClickBackButton);

		LeaderboardListView1 = Cast<UListView>(GetWidgetFromName(TEXT("LeaderBoardListView")));
		if (LeaderboardListView1 == nullptr) { return; }

		/*UDataObject* DataObject = ConstructDataObject();
		if (DataObject == nullptr) { return; }
		for (int i = 0; i <= DataObject->PlayerNameArray.Num() - 1; i++)
		{
			ScoreEntryWidget = Cast<UScoreEntryWidget>(StaticConstructObject_Internal(UScoreEntryWidget::StaticClass()));
			if (ScoreEntryWidget == nullptr) { return; }
			ScoreEntryWidget->PrepData1(i);
			LeaderboardListView1->AddItem(ScoreEntryWidget);
			
			
		}*/

		SetupLeaderBoardEntry();
	}

	UDataObject* ULeaderBoardWidget::ConstructDataObject()
	{
		UClass* DataObjectClass = UDataObject::StaticClass();
		if (DataObjectClass == nullptr) { return nullptr; }
		//UDataObject* DataObject = Cast<UDataObject>(StaticConstructObject_Internal(DataObjectClass));
		UDataObject* DataObject = NewObject<UDataObject>(GetTransientPackage(), DataObjectClass);

		return DataObject;
	}

	void ULeaderBoardWidget::OnClickBackButton()
	{
		if (MainMenuWidgetClass)
		{
			UUserWidget* MainMenuWidget= CreateWidget(this, MainMenuWidgetClass );
			if (MainMenuWidget)
			{
				MainMenuWidget->AddToViewport();
			}
		}
	}

	void ULeaderBoardWidget::SetupLeaderBoardEntry()
	{
		UDataObject* DataObject = ConstructDataObject();
		if (DataObject == nullptr) { return; }
		DataObject->PlayerScoreArray;
		for (float Score : DataObject->PlayerScoreArray)
		{
			TimeValueArray.Add(Score);
		}
		TimeValueArray.Sort([](const float& a, const float& b) { return a < b; });
		for (float Score : TimeValueArray)
		{
			IndexArray.Add(FindIndex(DataObject->PlayerScoreArray, Score));
		}
		for (int64 i : IndexArray)
		{
			//ScoreEntryWidget = Cast<UScoreEntryWidget>(StaticConstructObject_Internal(UScoreEntryWidget::StaticClass()));
			ScoreEntryWidget = NewObject<UScoreEntryWidget>(GetTransientPackage(), UScoreEntryWidget::StaticClass());

			if (ScoreEntryWidget == nullptr) { return; }
			ScoreEntryWidget->PrepData1(i);
			LeaderboardListView1->AddItem(ScoreEntryWidget);


		}

	}

	int64 ULeaderBoardWidget::FindIndex(const TArray<float>& Array, float Value)
	{
		int32 Index;
		if (Array.Find(Value, Index))
		{
			return Index;
		}
		return -1; // Value not found in the array
	}

	
	

