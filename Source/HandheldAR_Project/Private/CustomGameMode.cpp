// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"

ACustomGameMode::ACustomGameMode()
{
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();
	
	// Activates the tick function
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomGameMode::StartPlay()
{
	// This is called before any BeginPlay
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Score: %d"), GetScore()));
	
	// This function will transcend to call BeginPlay on all the actors
	Super::StartPlay();
}

int32 ACustomGameMode::GetScore()
{
	return GetGameState<ACustomGameState>()->Score;
	//return int32();
}

void ACustomGameMode::SetScore(int32 NewScore)
{
	GetGameState<ACustomGameState>()->Score += NewScore;
}
