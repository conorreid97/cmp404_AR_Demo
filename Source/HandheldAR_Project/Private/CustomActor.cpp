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

	// Find the Cube Asset and assign it using C++ (Right click on object in the Content Drawer to get Reference string)
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMeshComponent->SetStaticMesh(MeshAsset.Object);

	// Find the material that i want on the cube
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/StarterContent/Materials/M_Concrete_Poured.M_Concrete_Poured'"));

	if (Material.Succeeded()) {
		//ActorMaterialInstance = UMaterialInstanceDynamic::Create(Material)
		ActorMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, StaticMeshComponent);
	}

	StaticMeshComponent->SetMaterial(0, ActorMaterialInstance);
	//StaticMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
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
	FVector relativeLoc;

	// making the actor move in the path of infinity symbol
	float t = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	/*float scale*/relativeLoc.Z = 20 / (3 - cos(2 * t));
	relativeLoc.X = /*scale*/relativeLoc.Z * cos(t);
	/*float y*/relativeLoc.Y = /*scale*/relativeLoc.Z * sin(2 * t) / 2;

	v = FVector(relativeLoc.X, relativeLoc.Y, /*scale*/relativeLoc.Z);
	//SetActorLocation(v);

	//UE_LOG(LogTemp, Warning, TEXT("My Actor's Location is %s"), *actorLocation.ToString());

	//UKismetSystemLibrary::PrintString(this, FString(TEXT("Hello world")),
	//	true, true, FLinearColor::Red, 5);

	//SetActorLocation(FVector v);

	// Making a 4x4 Matrix
	FMatrix mat_init;
	FVector initLocation;
	

	mat_init = FMatrix::Identity;
	mat_init.M[3][0] = initLocation.X;
	mat_init.M[3][1] = initLocation.Y;
	mat_init.M[3][2] = initLocation.Z;

	// Move using the matrix
	FMatrix mat_moving = FMatrix::Identity;
	mat_moving.M[3][0] = relativeLoc.X;		// this is the calculated X from the previous lab
	mat_moving.M[3][1] = relativeLoc.Y;
	mat_moving.M[3][2] = relativeLoc.Z;

	FMatrix mat_final = mat_moving * mat_init;

	SetActorTransform(FTransform(mat_final));

	//GetWorldTimerManager().SetTimer(Ticker, this, &ACustomGameMode::SpawnCube, 4.0f, true, 0.0f);

}

void ACustomActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FVector ActorLoc = GetActorLocation();


}

