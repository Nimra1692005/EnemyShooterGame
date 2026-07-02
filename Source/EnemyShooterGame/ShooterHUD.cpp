#include "ShooterHUD.h"
#include "EnemyShooterCharacter.h"
#include "EnemyShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"

void AShooterHUD::DrawHUD()
{
    Super::DrawHUD();

    UWorld* World = GetWorld();
    if (!World) return;

    // ---- Score ----
    AEnemyShooterGameMode* GM = Cast<AEnemyShooterGameMode>(
        UGameplayStatics::GetGameMode(World));

    if (GM)
    {
        FString ScoreText = FString::Printf(TEXT("Score: %d / %d"),
            GM->GetScore(), GM->ScoreToWin);

        DrawText(ScoreText, FLinearColor::White, 30.f, 30.f, HUDFont, 1.5f);
    }

    // ---- Health ----
    AEnemyShooterCharacter* Player = Cast<AEnemyShooterCharacter>(
        UGameplayStatics::GetPlayerCharacter(World, 0));

    if (Player)
    {
        float HealthPct = Player->GetHealthPercent();
        FString HealthText = FString::Printf(TEXT("Health: %.0f%%"), HealthPct * 100.f);

        FLinearColor HealthColor = FLinearColor::LerpUsingHSV(
            FLinearColor::Red, FLinearColor::Green, HealthPct);

        DrawText(HealthText, HealthColor, 30.f, 60.f, HUDFont, 1.5f);

        // Simple health bar background (grey)
        DrawRect(FLinearColor(0.2f, 0.2f, 0.2f, 0.8f), 30.f, 85.f, 200.f, 18.f);
        // Health bar fill
        DrawRect(HealthColor, 30.f, 85.f, 200.f * HealthPct, 18.f);
    }
}
