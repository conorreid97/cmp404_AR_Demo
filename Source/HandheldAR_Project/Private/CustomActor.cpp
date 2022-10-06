// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACustomActor::ACustomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ACustomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector v;
	FVector actorLocation;

	actorLocation = GetActorLocation();
	
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, actorLocation.ToString());

	

	// making the actor move in the path of infinity symbol
	float t = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	float scale = 2 / (3 - cos(2 * t));
	float x = scale * cos(t);
	float y = scale * sin(2 * t) / 2;		

	v = FVector(x, y, scale);
	SetActorLocation(v);

	//UE_LOG(LogTemp, Warning, TEXT("My Actor's Location is %s"), *actorLocation.ToString());

	//UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")),
	//	true, true, FLinearColor::Red, 5);

	//SetActorLocation(FVector v);

}

