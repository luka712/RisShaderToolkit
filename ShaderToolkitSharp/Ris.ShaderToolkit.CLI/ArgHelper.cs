namespace Ris.ShaderToolkit;

/// <summary>
/// Tool helper for command line argument parsing.
/// </summary>
internal class ArgHelper
{
    /// <summary>
    /// Get the value of a specific argument from the command line arguments.
    /// </summary>
    /// <param name="allArguments">The arguments.</param>
    /// <param name="arg">The name of argument.</param>
    /// <returns>
    /// A string representing the value of the argument, or <c>null</c> if not found.
    /// </returns>
    internal static string? GetArgumentValue(string[] allArguments, string arg)
    {
        for (int i = 0; i < allArguments.Length; i++)
        {
            // If the argument matches and there is a next argument, return it
            if (allArguments[i] == arg && i + 1 < allArguments.Length)
            {
                return allArguments[i + 1];
            }
        }

        return null;
    }

    /// <summary>
    /// Get the value of a specific argument from the command line arguments, cast to type T.
    /// </summary>
    /// <typeparam name="T">The T type.</typeparam>
    /// <param name="allArguments">The arguments.</param>
    /// <param name="arg">The name of argument.</param>
    /// <returns>
    /// A value as type T representing the value of the argument, or <c>null</c> if not found.
    /// </returns>
    internal static T? GetArgumentValue<T>(string[] allArguments, string arg)
    {
        for (int i = 0; i < allArguments.Length; i++)
        {
            // If the argument matches and there is a next argument, return it
            if (allArguments[i] == arg && i + 1 < allArguments.Length)
            {
                if (typeof(T) == typeof(string))
                {
                    return (T)(object)allArguments[i + 1];
                }
                else if (typeof(T) == typeof(int))
                {
                    return Int32.Parse(allArguments[i + 1]) is T value ? value : default;
                }
                else if (typeof(T) == typeof(bool))
                {
                    return (allArguments[i + 1].ToLower()) switch
                    {
                        "y" or "yes" or "true" => (T)(object)true,
                        "n" or "no" or "false" => (T)(object)false,
                        _ => default,
                    };
                }
                else
                {
                    throw new NotSupportedException($"Type '{typeof(T)}' is not supported in ArgHelper.GetArgumentValue<T>.");
                }

            }
        }

        return default;
    }

    /// <summary>
    /// Checks if the argument has any of the specified values.
    /// </summary>
    /// <param name="allArguments">The arguments.</param>
    /// <param name="arg">The name of argument.</param>
    /// <param name="values">The allowed values.</param>
    /// <returns>
    /// <c>true</c> if the argument has any of the specified values; otherwise, <c>false</c>.
    /// </returns>
    internal static bool ArgumentHasAnyValue(string[] allArguments, string arg, params string[] values)
    {
        for (int i = 0; i < allArguments.Length; i++)
        {
            // If the argument matches and there is a next argument, return it
            // If the argument matches and there is a next argument, return it
            if (allArguments[i] == arg && i + 1 < allArguments.Length)
            {
                return values.Contains(allArguments[i + 1]);
            }
        }
        return false;
    }
}