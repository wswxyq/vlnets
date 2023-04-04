#include "EventMCVarExtractor.h"

#include "nusimdata/SimulationBase/MCTruth.h"

namespace VLN
{

    static const std::vector<std::string> SCALAR_VARS({"isCC", "pdg", "mode", "lepPdg", "nuE", "lepE", "hadE"});

    static const std::vector<std::string> VECTOR_VARS({"fpdgCode", "trackID", "start.x", "start.y", "start.z", "PX", "PY", "PZ"});

    EventMCVarExtractor::EventMCVarExtractor(
        const std::string &prefix, const std::string &labelGenerator)
        : VarExtractorBase(prefix, SCALAR_VARS, VECTOR_VARS),
          labelGenerator(labelGenerator)
    {
    }

    void EventMCVarExtractor::extractVars(const art::Event &evt, VarDict &vars)
    {
        std::vector<art::Ptr<simb::MCTruth>> mcTruth;

        auto mcTruth_h = evt.getHandle<std::vector<simb::MCTruth>>(labelGenerator);
        if (!mcTruth_h)
        {
            return;
        }

        art::fill_ptr_vector(mcTruth, mcTruth_h);
        if (mcTruth.empty())
        {
            return;
        }

        const auto &nuInt = mcTruth[0]->GetNeutrino();

        setScalarVar(vars, "isCC", (nuInt.CCNC() == 0));
        setScalarVar(vars, "pdg", nuInt.Nu().PdgCode());
        setScalarVar(vars, "mode", nuInt.Mode());
        setScalarVar(vars, "lepPdg", nuInt.Lepton().PdgCode());

        const double nuE = nuInt.Nu().E();
        const double lepE = nuInt.Lepton().Momentum().T();

        setScalarVar(vars, "nuE", nuE);
        setScalarVar(vars, "lepE", lepE);
        setScalarVar(vars, "hadE", nuE - lepE);

        // Shaowei added MCParticle information
        // Add fpdgCode
        // Add nucleon momentum cut
        if (mcTruth[0]->NParticles() > 0)
        {
            for (int i = 0; i < mcTruth[0]->NParticles(); i++)
            {
                const auto &particle = mcTruth[0]->GetParticle(i);
                if (particle.StatusCode() == 1)
                {
                    // this will select final state particles
                    if (( particle.PdgCode() == 2212 ) && ((particle.E(0) - particle.Mass()) >= 0.02) ) || 
                        (particle.PdgCode() != 2212 && particle.PdgCode() != 2112)
                    {
                        appendToVectorVar(vars, "fpdgCode", (double)particle.PdgCode());
                        appendToVectorVar(vars, "trackID", (double)particle.TrackId());
                        appendToVectorVar(vars, "start.x", particle.Vx());
                        appendToVectorVar(vars, "start.y", particle.Vy());
                        appendToVectorVar(vars, "start.z", particle.Vz());
                        appendToVectorVar(vars, "PX", particle.Px());
                        appendToVectorVar(vars, "PY", particle.Py());
                        appendToVectorVar(vars, "PZ", particle.Pz());
                    }
                }
            }
        }
    }
}
