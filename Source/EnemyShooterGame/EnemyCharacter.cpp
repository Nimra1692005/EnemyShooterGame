#include "EnemyCharacter.h"
#include "EnemyProjectile.h"
#include "EnemyShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    ShootInterval = 2.f;
    MuzzleOffset  = FVector(80.f, 0.f, 40.f);
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    FindPlayer();

    // Start shooting timer
    GetWorldTimerManager().SetTimer(ShootTimerHandle, this,
        &AEnemyCharacter::ShootAtPlayer, ShootInterval, true, ShootInterval);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FacePlayer(DeltaTime);
}

void AEnemyCharacter::FindPlayer()
{
    PlayerTarget = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyCharacter::FacePlayer(float DeltaTime)
{
    if (!PlayerTarget) return;

    // Build a rotation that looks from enemy toward player (yaw only)
    FVector Direction = PlayerTarget->GetActorLocation() - GetActorLocation();
    Direction.Z = 0.f; // keep upright — only rotate on yaw

    if (!Direction.IsNearlyZero())
    {
        FRotator TargetRotation = Direction.Rotation();
        FRotator CurrentRotation = GetActorRotation();

        // Smooth interpolation so it doesn't snap
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.f);
        SetActorRotation(NewRotation);
    }
}

void AEnemyCharacter::ShootAtPlayer()
{
    if (!PlayerTarget || !ProjectileClass) return;

    // Check player is still alive
    AEnemyShooterCharacter* Player = Cast<AEnemyShooterCharacter>(PlayerTarget);
    if (Player && Player->IsDead()) return;

    UWorld* World = GetWorld();
    if (!World) return;

    // Spawn location: in front of the enemy
    FVector  SpawnLocation = GetActorLocation() + GetActorForwardVector() * MuzzleOffset.X
                           + FVector(0.f, 0.f, MuzzleOffset.Z);
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner     = this;
    SpawnParams.Instigator = GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AEnemyProjectile* Projectile = World->SpawnActor<AEnemyProjectile>(
        ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

    if (Projectile)
    {
        // Aim directly at the player's center mass
        FVector AimDirection = (PlayerTarget->GetActorLocation() - SpawnLocation).GetSafeNormal();
        Projectile->FireInDirection(AimDirection);
    }
}
