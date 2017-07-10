Strict

Import brl.filestream
Import mojo.data

#If TARGET="android"

Import "native/android/modfile.android.java"

#ElseIf TARGET="ios"

Import "native/ios/modfile.ios.cpp"

#End

Class ModFile Extends NativeModFile
    
    Method New(path:String, preload:Bool = True)
        Self.path = path
        If preload
            Load()
        EndIf
    End
    
    Method GetPath:String() Property
        Return path
    End
    
    Method Load:Bool()
        Local buffer:DataBuffer = DataBuffer.Load(FixDataPath(GetPath()))
        If buffer <> Null
            LoadMODData(buffer)
            loaded = True
            Return True
        EndIf
        Return False
    End
    
    Method IsLoaded:Bool() Property
        Return loaded
    End
    
    Private
    Field path:String
    Field loaded:Bool = False

End

Private

#If TARGET<>"android" And TARGET<>"ios"

Class NativeModFile
    Method LoadMODData:Void(data:DataBuffer)
        Print("Load mod file")
    End
End

#Else

Extern

Class NativeModFile
    Method LoadMODData:Void(data:DataBuffer)
End

#End