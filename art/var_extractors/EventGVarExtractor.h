#pragma once

#include "nusimdata/SimulationBase/GTruth.h"
#include "VarExtractorBase.h"

namespace VLN {

class EventGVarExtractor : public VarExtractorBase
{
public:
    explicit EventGVarExtractor(
        const std::string &prefix,
        const std::string &labelGenerator = "generator"
    );
    ~EventGVarExtractor() = default;

protected:
    void extractVars(const art::Event &evt, VarDict &vars) override;

private:
    std::string labelGenerator;
};

}

