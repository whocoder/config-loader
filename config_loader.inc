#if defined _cfloader_included
 #endinput
#endif
#define _cfloader_included

/*
 *	All credit for this handy config-loading method goes to
 *	Bara, and his efforts in the TTT project. To use, before
 * 	loading set the KeyValues branch name (for example, TTT uses "TTT")
 *	and the config file (build the path first).
 
 *	Example:
 *		BuildPath(Path_SM, myfile, sizeof(myfile), "configs/rpgsettings.cfg");
 *		Config_Setup("RPG-Settings", myfile);
 *		Config_LoadBool("my_setting", false, "Description: My example setting");
 *
 *
 *	TTT Implementation -
 *		http://git.tf/TTT/Plugin/blob/3d3bd4e549aed1109f51111318436e98c919f23c/addons/sourcemod/scripting/ttt/ttt.sp#L4324
 *		From the highlighted line below
 * 	Bara -
 *		http://git.tf/u/Bara
 *		https://github.com/Bara20
 */



char __g_sConfigFile[PLATFORM_MAX_PATH];
char __g_sConfigName[128];
KeyValues __g_kConfigKV = INVALID_HANDLE;

stock bool Config_Setup(const char[] name, const char[] file){
    if(Config_IsValid())
        Config_Reset();

	FormatEx(__g_sConfigFile, PLATFORM_MAX_PATH, "%s", file);
	FormatEx(__g_sConfigName, sizeof(__g_sConfigName), "%s", name);

    __g_kConfigKV = CreateKeyValues(__g_sConfigName);

    if(!__g_kConfigKV.ImportFromFile(__g_sConfigFile))
		LogMessage("[CONFIG LOADER] Couldn't read file %s! Will be built now!", __g_sConfigFile);

    if(!__g_kConfigKV.ExportToFile(__g_sConfigFile)){
        LogError("[CONFIG LOADER] Couldn't build configuration file %s to desired location!", __g_sConfigFile);

        Config_Reset();
        return false;
    }

    return true;
}

stock int Config_LoadInt(const char[] name, int value, const char[] description){
    if(!Config_IsValid()){
        LogError("[CONFIG LOADER] Improper config loading usage!");
        return 0;
    }

	if(__g_kConfigKV.JumpToKey(name, false))
		value = __g_kConfigKV.GetNum("value");
	else
	{
		LogMessage("[CONFIG LOADER] Can't find setting '%s' in %s! Adding default value (%d).", name, __g_sConfigFile, value);

		__g_kConfigKV.JumpToKey(name, true);
		__g_kConfigKV.SetNum("value", value);
		__g_kConfigKV.SetString("description", description);
	    __g_kConfigKV.Rewind();
		__g_kConfigKV.ExportToFile(__g_sConfigFile);
	}

	return value;
}

stock bool Config_LoadBool(const char[] name, bool value, const char[] description){
    if(!Config_IsValid()){
        LogError("[CONFIG LOADER] Improper config loading usage!");
        return false;
    }

	if(__g_kConfigKV.JumpToKey(name, false))
		value = view_as<bool>(__g_kConfigKV.GetNum("value"));
	else
	{
		LogMessage("[CONFIG LOADER] Can't find setting '%s' in %s! Adding default value (%s).", name, __g_sConfigFile, (value ? "true" : "false"));

        __g_kConfigKV.JumpToKey(name, true);
		__g_kConfigKV.SetNum("value", value);
		__g_kConfigKV.SetString("description", description);
		__g_kConfigKV.Rewind();
		__g_kConfigKV.ExportToFile(__g_sConfigFile);
	}

	return value;
}

stock float Config_LoadFloat(const char[] name, float value, const char[] description){
    if(!Config_IsValid()){
        LogError("[CONFIG LOADER] Improper config loading usage!");
        return 0.0;
    }

	if(__g_kConfigKV.JumpToKey(name, false))
		value = __g_kConfigKV.GetFloat("value");
	else
	{
		LogMessage("[CONFIG LOADER] Can't find setting '%s' in %s! Adding default value (%f).", name, __g_sConfigFile, value);

        __g_kConfigKV.JumpToKey(name, true);
		__g_kConfigKV.SetFloat("value", value);
		__g_kConfigKV.SetString("description", description);
		__g_kConfigKV.Rewind();
		__g_kConfigKV.ExportToFile(__g_sConfigFile);
	}

	return value;
}

stock void Config_LoadString(const char[] name, const char[] value, const char[] description, char[] output, int size){
    if(!Config_IsValid()){
        LogError("[CONFIG LOADER] Improper config loading usage!");
        return;
    }

	if(__g_kConfigKV.JumpToKey(name, false))
		__g_kConfigKV.GetString("value", output, size);
	else
	{
        strcopy(output, size, value);
		LogMessage("[CONFIG LOADER] Can't find setting '%s' in %s! Adding default value (%s).", name, __g_sConfigFile, value);

        __g_kConfigKV.JumpToKey(name, true);
		__g_kConfigKV.SetString("value", value);
		__g_kConfigKV.SetString("description", description);
		__g_kConfigKV.Rewind();
		__g_kConfigKV.ExportToFile(__g_sConfigFile);
	}
}


stock bool Config_IsValid(){
    return (__g_kConfigKV != INVALID_HANDLE);
}

stock void Config_Done(){
    Config_Reset();
}

stock void Config_Reset(){
    FormatEx(__g_sConfigFile, PLATFORM_MAX_PATH, "");
    FormatEx(__g_sConfigName, sizeof(__g_sConfigName), "");

    if(__g_kConfigKV != INVALID_HANDLE){
        CloseHandle(__g_kConfigKV);
        __g_kConfigKV = INVALID_HANDLE;
    }
}
