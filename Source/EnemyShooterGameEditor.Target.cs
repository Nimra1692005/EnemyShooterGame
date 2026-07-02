using UnrealBuildTool;
using System.Collections.Generic;

public class EnemyShooterGameEditorTarget : TargetRules
{
	public EnemyShooterGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("EnemyShooterGame");
	}
}
