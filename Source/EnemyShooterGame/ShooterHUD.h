#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUD.generated.h"

/**
 * Simple HUD that draws score and health directly on screen.
 * You can replace this with a UMG Widget Blueprint if preferred.
 */
UCLASS()
class ENEMYSHOOTERGAME_API AShooterHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    UFont* HUDFont;
};
