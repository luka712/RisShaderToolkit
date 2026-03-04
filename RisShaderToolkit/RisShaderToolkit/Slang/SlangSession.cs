namespace RisShaderToolkit.Slang
{
    /// <summary>
    /// The Slang session, which is used to manage the compilation of shaders and its resources.
    /// </summary>
    public class SlangSession : IDisposable
    {
        private readonly IntPtr _session;

        /// <summary>
        /// The constructor.
        /// </summary>
        /// <param name="globalSession">The global session.</param>
        /// <param name="sessionDescription">The session description.</param>
        /// <exception cref="Exception"></exception>
        internal SlangSession(IntPtr sessionPtr)
        {
            _session = sessionPtr;
        }

        public void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
