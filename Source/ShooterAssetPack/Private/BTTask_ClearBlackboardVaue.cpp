// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_ClearBlackboardVaue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardVaue::UBTTask_ClearBlackboardVaue()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UBTTask_ClearBlackboardVaue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(FName("PlayerLastLocation"));

	return EBTNodeResult::Succeeded;
}
