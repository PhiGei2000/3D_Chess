$resourceFiles = Get-ChildItem -Path ./Resources -Recurse -File
$resourceSourceDir = Get-Item -Path ./Resources

if(-not (Test-Path ./build/bin/Debug/Resources/)) {
    New-Item -Path ./build/bin/Debug/Resources -ItemType Directory
}

$resourceDestDir = Get-Item -Path ./build/bin/Debug/Resources

foreach ($file in $resourceFiles) {
    $destFilePath = [System.IO.Path]::Combine($resourceDestDir.FullName, $file.FullName.Replace($resourceSourceDir.FullName, $resourceDestDir.FullName))    

    if(-not (Test-Path -Path $destFilePath)) {
        $destPath = $file.DirectoryName.Replace($resourceSourceDir.FullName, $resourceDestDir.FullName)

        if(-not (Test-Path -Path $destPath)) {
            New-Item -Path $destPath -ItemType Directory
        }
        
        Copy-Item -Path $file.FullName -Destination $destPath
    }
    else {
        $destFile = Get-Item -Path $destFilePath
        if ($file.LastWriteTime -gt $destFile.LastWriteTime) {
            Copy-Item -Path $file.FullName -Destination $destFile.DirectoryName
        }
    }
}

#dlls
Copy-Item -Path C:\lib\GLEW\lib\Release\Win32\glew32.dll -Destination .\build\bin
Copy-Item -Path C:\lib\GLFW\lib\glfw3.dll -Destination .\build\bin