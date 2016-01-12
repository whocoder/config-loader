# SourceMod Config Loader
Simple SourceMod config loading system.


## Example

<<<<<<< HEAD
    char file[PLATFORM_MAX_PATH];
    char buffer[128];

    BuildPath(Path_SM, file, sizeof(file), "configs/mysettings.cfg");
    Config_Setup("Server-Settings", file);
    bool mybool = Config_LoadBool("mybool", true, "Default bool description");
    Config_LoadString("mystring", "default string description", "Default string description", buffer, sizeof(buffer));


## Credits
* [Bara](https://github.com/Bara20) - Original concept and idea
* [whocodes](https://whocodes.pw/) - Improvement and ease-of-use
=======
    void OnPluginStart(){
        char file[PLATFORM_MAX_PATH];
        BuildPath(Path_SM, file, sizeof(file), "configs/mysettings.cfg");
        
        Config_Setup("Server-Settings", file);
        
        bool mybool = Config_LoadBool("mybool", true, "Default bool description");
        int myint = Config_LoadInt("myint", 0, "Default int description");
        float myfloat = Config_LoadFloat("myfloat", 0.0, "Default float description);
        
        char buffer[128];
        Config_LoadString("mystring", "default string description", "Default string description", buffer, sizeof(buffer));
    }
>>>>>>> origin/master
