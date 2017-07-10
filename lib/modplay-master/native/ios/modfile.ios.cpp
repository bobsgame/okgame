#include "modplug.h"

class NativeModFile : public Object {

    ModPlugFile *file;
    
public:
    void LoadMODData(BBDataBuffer* data) { file = ModPlug_Load(data->ReadPointer(),data->Length()); }
    ModPlugFile* GetData() { return file; }
};
