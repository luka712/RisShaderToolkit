using AutoMapper;
using Microsoft.Extensions.Logging.Abstractions;
using Ris.ShaderToolkit.Dto;
using Ris.ShaderToolkit.Json;
using System.Text.Json;

namespace Ris.ShaderToolkit
{
    internal class JsonReader
    {
        private readonly IMapper _mapper;

        internal JsonReader()
        {
            MapperConfiguration config = new (cfg =>
            {
                cfg.AddProfile<AutoMapperProfile>();
            }, new NullLoggerFactory());

            _mapper = config.CreateMapper();
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

            List<ShaderCompileTaskDto> results = new ();

            foreach (ShaderJson shader in compileJson.Shaders)
            {
                // Create a task for each shader
                string inputFilePath = Path.IsPathRooted(shader.Name)
                    ? shader.Name
                    : Path.Combine(directory, shader.Name);

                ShaderCompileTaskDto compileTask = _mapper.Map<ShaderCompileTaskDto>(shader);
                compileTask.InputFilePath = inputFilePath;
                results.Add(compileTask);
            }

            return results;
        }
    }
}
