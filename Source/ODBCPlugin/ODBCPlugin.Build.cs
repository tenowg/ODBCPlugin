// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

//namespace UnrealBuildTool.Rules
//{
	public class ODBCPlugin : ModuleRules
	{
        private string ModulePath
        {
            get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
        }

		public ODBCPlugin(TargetInfo Target)
		{
            //PublicIncludePaths.AddRange(
            //    new string[] {
            //        // ... add public include paths required here ...
            //    }
            //    );

			PrivateIncludePaths.AddRange(
				new string[] {
					"ODBCPlugin/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					
					// ... add other public dependencies that you statically link with here ...
				}
				);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Core",
					"CoreUObject",
                    "Engine"
					// ... add private dependencies that you statically link with here ...
				}
				);

            //DynamicallyLoadedModuleNames.AddRange(
            //    new string[]
            //    {
            //        // ... add any modules that your module loads dynamically here ...
            //    }
            //    );
		}
	}
//}