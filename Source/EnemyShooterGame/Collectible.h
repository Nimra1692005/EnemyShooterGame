#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UCLASS()
class ENEMYSHOOTERGAME_API ACollectible : public AActor
{
    GENERATED_BODY()

public:
    ACollectible();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* MeshComp;

    UFUNCTION()
    void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

public:
    // Points awarded when collected
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 ScoreValue;

    // Spin speed for visual feedback
    UPROPERTY(EditAnywhere, Category = "Visual")
    float SpinSpeed;
};
