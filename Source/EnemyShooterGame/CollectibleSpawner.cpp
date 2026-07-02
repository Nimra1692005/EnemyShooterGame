#include "CollectibleSpawner.h"
#include "Collectible.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"

ACollectibleSpawner::ACollectibleSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    SpawnInterval    = 3.f;
    SpawnAreaHalfSize = 1000.f;
    MaxCollectibles  = 5;
    SpawnHeight      = 50.f;
}

void ACollectibleSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (CollectibleClass)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this,
            &ACollectibleSpawner::SpawnCollectible, SpawnInterval, true, 0.5f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CollectibleSpawner: No CollectibleClass set! Please assign it in the Blueprint defaults."));
    }
}

void ACollectibleSpawner::SpawnCollectible()
{
    UWorld* World = GetWorld();
    if (!World || !CollectibleClass) return;

    // Count how many collectibles are currently alive
    if (MaxCollectibles > 0)
    {
        int32 Count = 0;
        for (TActorIterator<ACollectible> It(World); It; ++It)
        {
            ++Count;
        }
        if (Count >= MaxCollectibles) return;
    }

    // Pick a random location around this actor
    FVector Origin = GetActorLocation();
    float RandX = FMath::FRandRange(-SpawnAreaHalfSize, SpawnAreaHalfSize);
    float RandY = FMath::FRandRange(-SpawnAreaHalfSize, SpawnAreaHalfSize);
    FVector SpawnLocation(Origin.X + RandX, Origin.Y + RandY, Origin.Z + SpawnHeight);

    FRotator SpawnRotation = FRotator::ZeroRotator;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    World->SpawnActor<ACollectible>(CollectibleClass, SpawnLocation, SpawnRotation, SpawnParams);
}
