# SourceMod Config Loader
Simple SourceMod config loading system.


## Example

    char file[PLATFORM_MAX_PATH];
    char buffer[128];
    
    BuildPath(Path_SM, file, sizeof(file), "configs/mysettings.cfg");
    Config_Setup("Server-Settings", file);
    bool mybool = Config_LoadBool("mybool", true, "Default bool description");
    Config_LoadString("mystring", "default string description", "Default string description", buffer, sizeof(buffer));