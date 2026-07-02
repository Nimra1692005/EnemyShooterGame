#include "EnemyShooterGameMode.h"
#include "Kismet/GameplayStatics.h"

AEnemyShooterGameMode::AEnemyShooterGameMode()
{
    CurrentScore = 0;
    ScoreToWin   = 10;
    bGameOver    = false;
}

void AEnemyShooterGameMode::AddScore(int32 Points)
{
    if (bGameOver) return;
    CurrentScore += Points;
    UE_LOG(LogTemp, Warning, TEXT("Score: %d"), CurrentScore);
    CheckWinCondition();
}

void AEnemyShooterGameMode::CheckWinCondition()
{
    if (CurrentScore >= ScoreToWin)
    {
        WinGame();
    }
}

void AEnemyShooterGameMode::PlayerDied()
{
    if (bGameOver) return;
    bGameOver = true;
    UE_LOG(LogTemp, Warning, TEXT("Game Over! Restarting..."));

    FTimerHandle RestartTimer;
    GetWorldTimerManager().SetTimer(RestartTimer, this,
        &AEnemyShooterGameMode::RestartLevel, 3.f, false);
}

void AEnemyShooterGameMode::RestartLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), true);
}

void AEnemyShooterGameMode::WinGame()
{
    bGameOver = true;
    UE_LOG(LogTemp, Warning, TEXT("YOU WIN! Score: %d"), CurrentScore);
}
