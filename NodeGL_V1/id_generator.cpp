#include "id_generator.h"

int GetNextId()
{
    return s_NextId++;
}

ed::LinkId GetNextLinkId()
{
    return ed::LinkId(GetNextId());
}

void ResetId()
{
    s_NextId = 1;
}