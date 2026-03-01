Set WshShell = CreateObject("WScript.Shell")

' MSI deferred custom action data
targetDir = Session.Property("CustomActionData")

' Remove trailing backslash if present
If Right(targetDir, 1) = "\" Then
    targetDir = Left(targetDir, Len(targetDir) - 1)
End If

' Read current system PATH
currentPath = WshShell.Environment("System")("Path")

' Add if not already there
If InStr(1, currentPath, targetDir, vbTextCompare) = 0 Then
    WshShell.Environment("System")("Path") = currentPath & ";" & targetDir
End If
