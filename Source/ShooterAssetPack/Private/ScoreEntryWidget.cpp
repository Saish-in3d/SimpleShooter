// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreEntryWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "DataObject.h"
#include "Components/TextBlock.h"



void UScoreEntryWidget::NativeConstruct()
{
	PlayerNameTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerName")));
	PlayerTimeTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerTime")));


	//OnListItemObjectSet();

}

void UScoreEntryWidget::PrepData1(int64 Index)
{
	UClass* DataObjectClass = UDataObject::StaticClass();
	if (DataObjectClass == nullptr) { return; }
	UDataObject* DataObject = Cast<UDataObject>(StaticConstructObject_Internal(DataObjectClass));
	if (DataObject)
	{
		NameArray = DataObject->PlayerNameArray;
		TimeArray = DataObject->PlayerScoreArray;

		PlayerName = NameArray[Index];
		PlayerTime = TimeArray[Index];
	}
}

void UScoreEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UScoreEntryWidget* ScoreEntryWidget = Cast<UScoreEntryWidget>(ListItemObject);
	if (ScoreEntryWidget)
	{
		SetName(ScoreEntryWidget->PlayerName);
		SetTime(ScoreEntryWidget->PlayerTime);
	}
}

void UScoreEntryWidget::SetName(FString Name)
{
	if (PlayerNameTB)
	{
		PlayerNameTB->SetText(FText::FromString(Name));
	}

}

void UScoreEntryWidget::SetTime(float Time)
{
	if (PlayerTimeTB)
	{
		PlayerTimeTB->SetText(FText::AsNumber(Time));
	}

}
