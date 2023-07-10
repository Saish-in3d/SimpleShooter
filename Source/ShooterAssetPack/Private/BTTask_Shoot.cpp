// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "ShooterAIController.h"
#include "ShooterAssetPack/ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}


EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}


	ShooterCharacter =  Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (ShooterCharacter && ShooterCharacter->GetAIShallShoot() == true)
	{
		ShooterCharacter->AIShoot();
	}
	
	return EBTNodeResult::Succeeded;
}
