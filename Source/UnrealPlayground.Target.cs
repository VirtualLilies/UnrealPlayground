// Copyright C 2018 Tomasz Figas

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealPlaygroundTarget : TargetRules
{
	public UnrealPlaygroundTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "UnrealPlayground" } );
	}
}
