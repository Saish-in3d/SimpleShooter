// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_PlayerLocation.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "UpdatePlayerLocation";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory,  DeltaSeconds);

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0.f); 
	if(PlayerPawn)
	{
		
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}


}


