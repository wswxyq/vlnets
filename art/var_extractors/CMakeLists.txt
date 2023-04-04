art_make_library(
    LIBRARY_NAME VLNVarExtractors
    SOURCE
        DefaultInputVarExtractor.cxx
        EventAddrVarExtractor.cxx
        EventMCVarExtractor.cxx
        EventGVarExtractor.cxx
        EventRecoEVarExtractor.cxx
        EventRecoVarExtractor.cxx
        FiducialCutVarExtractor.cxx
        PFParticleVarExtractor.cxx
        VLNEnergyVarExtractor.cxx
        VarExtractorBase.cxx
        utils.cxx
    LIBRARIES
        dunereco_AnaUtils
        larreco_Calorimetry
        larsim_Utils
        larsim_MCCheater_ParticleInventoryService_service
)

install_headers()
install_source()
install_fhicl()

