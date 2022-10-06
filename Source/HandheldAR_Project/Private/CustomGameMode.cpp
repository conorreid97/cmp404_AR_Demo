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

	SpawnCube();
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

void ACustomGameMode::SpawnCube()
{
	FActorSpawnParameters SpawnInfo;
	FRotator myRot(0, 0, 0);
	FVector myLoc(300, 0, 0);
	ACustomActor* customActor = GetWorld()->SpawnActor<ACustomActor>(myLoc, myRot, SpawnInfo);
}

