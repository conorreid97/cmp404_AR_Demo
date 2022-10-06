// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HANDHELDAR_PROJECT_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;
		
	virtual void StartPlay();
	
	UFUNCTION(BlueprintCallable, Category = "Score")
		int32 GetScore();
	
	UFUNCTION(BlueprintCallable, Category = "Score")
		void SetScore(int32 NewScore);
	
};
