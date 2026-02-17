using System.Reflection;
using System.Runtime.InteropServices;


namespace Ris.ShaderToolkit
{
    public static class NativeResolver
    {
        private const string BaseName = "shader_toolkit_c";
        private static bool _isResolved;

        // Call this once at startup before any native calls
        public static void Setup()
        {
            if (_isResolved)
            {
                return;
            }
            
            NativeLibrary.SetDllImportResolver(typeof(NativeResolver).Assembly, Resolve);
            _isResolved = true;
        }

        private static IntPtr Resolve(string libraryName, Assembly assembly, DllImportSearchPath? searchPath)
        {
            if (libraryName != BaseName)
                return IntPtr.Zero; // only handle our library
            
            string prefix = OperatingSystem.IsWindows() ? "" : "lib";

            string rid = GetRuntimeIdentifier();
            string ext = OperatingSystem.IsWindows() ? ".dll" :
                         OperatingSystem.IsMacOS() ? ".dylib" : ".so";

            string path = Path.Combine(AppContext.BaseDirectory, "runtimes", rid, "native", prefix + BaseName + ext);

            if (!File.Exists(path))
                throw new DllNotFoundException($"Native library not found: {path}");

            return NativeLibrary.Load(path);
        }

        private static string GetRuntimeIdentifier()
        {
            string os = OperatingSystem.IsWindows() ? "win" :
                        OperatingSystem.IsLinux() ? "linux" :
                        OperatingSystem.IsMacOS() ? "osx" : throw new PlatformNotSupportedException();

            string arch = RuntimeInformation.ProcessArchitecture switch
            {
                Architecture.X64 => "x64",
                Architecture.X86 => "x86",
                Architecture.Arm64 => "arm64",
                Architecture.Arm => "arm",
                _ => "unknown"
            };

            return $"{os}-{arch}";
        }
    }
}
