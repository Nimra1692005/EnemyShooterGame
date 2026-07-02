#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectibleSpawner.generated.h"

UCLASS()
class ENEMYSHOOTERGAME_API ACollectibleSpawner : public AActor
{
    GENERATED_BODY()

public:
    ACollectibleSpawner();

protected:
    virtual void BeginPlay() override;

private:
    // Timer that drives spawning
    FTimerHandle SpawnTimerHandle;

    // Perform one spawn
    void SpawnCollectible();

public:
    // Class to spawn
    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    TSubclassOf<class ACollectible> CollectibleClass;

    // How often a new collectible spawns (seconds)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnInterval;

    // Half-extents of the random area around this actor (X/Y only)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnAreaHalfSize;

    // Maximum collectibles alive at once (0 = unlimited)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    int32 MaxCollectibles;

    // How high above the floor to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnHeight;
};
