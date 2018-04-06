// Copyright C 2018 Tomasz Figas

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealPlaygroundEditorTarget : TargetRules
{
	public UnrealPlaygroundEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "UnrealPlayground" } );
	}
}
