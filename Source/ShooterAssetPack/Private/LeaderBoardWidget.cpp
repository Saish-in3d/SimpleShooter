// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "DataObject.h"
#include "ScoreEntryWidget.h"
#include "Components/ListView.h"
#include "LeaderBoardWidget.h"




	void ULeaderBoardWidget::NativeConstruct()
	{
		Super::NativeConstruct();

		LeaderboardListView1 = Cast<UListView>(GetWidgetFromName(TEXT("LeaderBoardListView")));
		if (LeaderboardListView1 == nullptr) { return; }
		UDataObject* DataObject = ConstructDataObject();
		if (DataObject == nullptr) { return; }
		for (int i = 0; i <= DataObject->PlayerNameArray.Num() - 1; i++)
		{
			ScoreEntryWidget = Cast<UScoreEntryWidget>(StaticConstructObject_Internal(UScoreEntryWidget::StaticClass()));
			if (ScoreEntryWidget == nullptr) { return; }
			ScoreEntryWidget->PrepData1(i);
			LeaderboardListView1->AddItem(ScoreEntryWidget);
			
			
		}
	}

	UDataObject* ULeaderBoardWidget::ConstructDataObject()
	{
		UClass* DataObjectClass = UDataObject::StaticClass();
		if (DataObjectClass == nullptr) { return nullptr; }
		UDataObject* DataObject = Cast<UDataObject>(StaticConstructObject_Internal(DataObjectClass));
		return DataObject;
	}

	


