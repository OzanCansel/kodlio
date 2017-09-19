function Component()
{

}

Component.prototype.createOperations = function()
{
	component.createOperations();
	
        if(systemInfo.productType === "windows"){

        component.addOperation("CreateShortcut", "@TargetDir@/Kodlio.exe", "@DesktopDir@/Kodlio.lnk");
        component.addOperation("CreateShortcut", "@TargetDir@\\Kodlio.exe", "@StartMenuDir@\\Kodlio.lnk",
        "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
        "iconId=2");
            //component.addOperation("Execute" , "@TargetDir@\\install-script-x64" , "workingdirectory=@TargetDir@", "UNDOEXECUTE" , "@TargetDir@\\uninstall-script" );
            component.addOperation("Execute" , "@TargetDir@\\install-script-x64.cmd" , "workingdirectory=@TargetDir@", "UNDOEXECUTE" , "@TargetDir@\\uninstall-script.cmd" )
        }
}
