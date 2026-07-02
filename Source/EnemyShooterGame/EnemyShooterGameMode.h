#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyShooterGameMode.generated.h"

UCLASS()
class ENEMYSHOOTERGAME_API AEnemyShooterGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AEnemyShooterGameMode();

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Points);

    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const { return CurrentScore; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    void PlayerDied();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void CheckWinCondition();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Score")
    int32 ScoreToWin;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Score")
    int32 CurrentScore;

    bool bGameOver;

    void RestartLevel();
    void WinGame();
};
