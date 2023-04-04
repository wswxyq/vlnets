#include "EventGVarExtractor.h"

#include "nusimdata/SimulationBase/GTruth.h"

namespace VLN {

static const std::vector<std::string> SCALAR_VARS({
    "fGscatter"
});

static const std::vector<std::string> VECTOR_VARS({});

EventGVarExtractor::EventGVarExtractor(
    const std::string &prefix, const std::string &labelGenerator
)
  : VarExtractorBase(prefix, SCALAR_VARS, VECTOR_VARS),
    labelGenerator(labelGenerator)
{ }

void EventGVarExtractor::extractVars(const art::Event &evt, VarDict &vars)
{
    std::vector<art::Ptr<simb::GTruth>> gTruth;

    auto gTruth_h = evt.getHandle<std::vector<simb::GTruth>>(labelGenerator);
    if (!gTruth_h) {
        return;
    }

    art::fill_ptr_vector(gTruth, gTruth_h);
    if (gTruth.empty()) {
        return;
    }

    setScalarVar(vars, "fGscatter",   gTruth[0]->fGscatter);

}

}

