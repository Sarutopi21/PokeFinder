std::vector<GeneratorState> StaticGenerator3::findIVs(u16 iv1, u16 iv2, u16 iv3, u16 iv4, u16 iv5, u16 iv6) const
{
    std::vector<GeneratorState> matchingStates;

    const PersonalInfo *info = staticTemplate.getInfo();

    for (u32 tid = 0; tid <= 65535; tid++)
    {
        for (u32 sid = 0; sid <= 65535; sid++)
        {
            for (u32 pid = 0; pid <= 4294967295; pid++)
            {
                u32 generatedPID = pid;
                u32 generatedIV1 = generatedPID & 31;
                u32 generatedIV2 = (generatedPID >> 5) & 31;
                u32 generatedIV3 = (generatedPID >> 10) & 31;
                u32 generatedIV4 = (generatedPID >> 15) & 31;
                u32 generatedIV5 = (generatedPID >> 20) & 31;
                u32 generatedIV6 = (generatedPID >> 25) & 31;

                if (generatedIV1 == iv1 && generatedIV2 == iv2 && generatedIV3 == iv3 &&
                    generatedIV4 == iv4 && generatedIV5 == iv5 && generatedIV6 == iv6)
                {
                    GeneratorState state(0, pid, {iv1, iv2, iv3, iv4, iv5, iv6},
                                         pid & 1, Utilities::getGender(pid, info),
                                         staticTemplate.getLevel(), pid % 25,
                                         Utilities::getShiny(pid, tsv), info);

                    if (filter.compareState(static_cast<const State &>(state)))
                    {
                        matchingStates.emplace_back(state);
                    }
                }
            }
        }
    }

    return matchingStates;
}
