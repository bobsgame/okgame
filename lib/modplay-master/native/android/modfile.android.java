class NativeModFile {

    private byte[] moddata;
    private boolean loaded = false;

    public void LoadMODData(BBDataBuffer modData) {
        Log.i("ModPlay", "Loading Mod File");
        moddata = modData.GetByteBuffer().array();
        loaded = true;
    }
    
    public byte[] GetData() {
        if (!loaded) {
            return new byte[0];
        }
        return moddata;
    }


}