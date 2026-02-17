using AutoMapper;
using Ris.ShaderToolkit.Dto;
using Ris.ShaderToolkit.Json;
using Ris.ShaderToolkit.Rules;
using System;

namespace Ris.ShaderToolkit
{
    internal class AutoMapperProfile : Profile
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

        public AutoMapperProfile()
        {
            CreateMap<ReplaceStageInputNameRuleJson, ReplaceStageInputNameRule>();
            CreateMap<ReplaceStageOutputNameRuleJson, ReplaceStageOutputNameRule>();
            CreateMap<ShaderJson, ShaderCompileTaskDto>()
                .ForMember(dest => dest.OutputFilePath, opt => opt.MapFrom(src => src.OutputFile))
                .ForMember(dest => dest.InputNameRule, opt => opt.MapFrom(src => src.Rules != null ? src.Rules.InputNameRule : null))
                .ForMember(dest => dest.OutputNameRule, opt => opt.MapFrom(src => src.Rules != null ? src.Rules.OutputNameRule : null))
                .ForMember(dest => dest.Profile, opt => opt.MapFrom(src => ResolveProfile(src.Profile)))
                .ForMember(dest => dest.SourceProfile, opt => opt.MapFrom(src => ResolveProfile(src.SourceProfile)));



        }
    }
}
