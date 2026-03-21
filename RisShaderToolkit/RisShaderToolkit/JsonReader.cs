using RisShaderToolkit.Dto;
using RisShaderToolkit.Json;
using System.Text.Json;

namespace RisShaderToolkit
{
    /// <summary>
    /// This class is responsible for reading a JSON file that describes shader compilation tasks and 
    /// converting it into a list of `ShaderCompileTaskDto` objects that can be used by the rest of the application.
    /// </summary>
    internal class JsonReader
    {
        private static AnyProfile? ResolveProfile(string? profileStr)
        {
            if (String.IsNullOrEmpty(profileStr))
            {
                return null;
            }

            if (Enum.TryParse<AnyProfile>(profileStr, ignoreCase: true, out AnyProfile value))
            {
                return value;
            }

            throw new InvalidOperationException($"Unsupported profile type: {profileStr}.");
        }

        /// <summary>
        /// Compiles shaders based on the given JSON file.
        /// </summary>
        /// <param name="jsonFilePath">The json file path.</param>
        /// <exception cref="InvalidOperationException">
        /// In case of an error during deserialization.
        /// </exception>
        public IReadOnlyList<ShaderCompileTaskDto> LoadJson(string jsonFilePath)
        {
            string directory = Path.GetDirectoryName(jsonFilePath) ?? string.Empty;

            string json = File.ReadAllText(jsonFilePath);
            CompileJson? compileJson = JsonSerializer.Deserialize<CompileJson>(json, new JsonSerializerOptions()
            {
                PropertyNamingPolicy = JsonNamingPolicy.SnakeCaseLower
            });

            if (compileJson == null)
            {
                throw new InvalidOperationException("Failed to deserialize compile JSON.");
            }

            List<ShaderCompileTaskDto> results = new();

            foreach (ShaderJson shaderJson in compileJson.Shaders)
            {
                // Create a task for each shader
                string inputFilePath = Path.IsPathRooted(shaderJson.Name)
                    ? shaderJson.Name
                    : Path.Combine(directory, shaderJson.Name);

                ShaderCompileTaskDto compileTask = new()
                {
                    OutputFilePath = shaderJson.OutputFile,
                    EntryPoints = shaderJson.EntryPoints,
   
                };

                if(shaderJson.Stage.HasValue)
                {
                    compileTask.Stages.Add(shaderJson.Stage.Value);
                }

                if(shaderJson.Stages != null)
                {
                    compileTask.Stages.AddRange(shaderJson.Stages);
                }

                compileTask.InputFilePath = inputFilePath.Replace("\\", "/");
                compileTask.SourceProfile = ResolveProfile(shaderJson.SourceProfile);
                compileTask.Profile = ResolveProfile(shaderJson.Profile) ?? throw new InvalidOperationException("JSON entry in 'shaders' is missing 'profile' property.");
                results.Add(compileTask);
            }

            return results;
        }
    }
}
