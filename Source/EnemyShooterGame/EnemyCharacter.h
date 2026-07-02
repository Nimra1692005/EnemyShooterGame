#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ENEMYSHOOTERGAME_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    // The player we are targeting
    UPROPERTY()
    AActor* PlayerTarget;

    // Timer handle for shooting
    FTimerHandle ShootTimerHandle;

    // How often the enemy shoots (seconds)
    UPROPERTY(EditAnywhere, Category = "Combat")
    float ShootInterval;

    // Projectile class to spawn
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AEnemyProjectile> ProjectileClass;

    // Muzzle offset from enemy origin
    UPROPERTY(EditAnywhere, Category = "Combat")
    FVector MuzzleOffset;

    // Find and cache the player
    void FindPlayer();

    // Rotate to face the player
    void FacePlayer(float DeltaTime);

    // Fire a projectile at the player
    void ShootAtPlayer();
};
