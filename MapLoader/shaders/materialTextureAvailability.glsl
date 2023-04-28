const bool CanHaveDiffuseValues[] = { true, true, true, true, true, true, true, true, true, true, true, true, false };
const bool AlwaysHasDiffuseValues[] = { false, false, false, false, false, true, true, true, true, true, true, true, false };

const bool CanHaveSpecularValues[] = { true, true, true, true, true, true, false, false, false, true, false, true, false };
const bool AlwaysHasSpecularValues[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };

const bool CanHaveNormalValues[] = { true, true, true, true, true, true, false, false, true, true, true, true, false };
const bool AlwaysHasNormalValues[] = { false, false, false, false, false, false, false, false, false, true, false, true, false };

const bool CanHaveColorOverrideValues[] = { false, false, true, true, true, false, false, false, false, false, false, false, false };
const bool AlwaysHasColorOverrideValues[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };

const bool CanHaveEmissiveValues[] = { false, false, false, false, true, false, false, false, false, false, false, false, false };
const bool AlwaysHasEmissiveValues[] = { false, false, false, false, false, false, false, false, false, false, false, true, false };

const bool CanHaveDecalValues[] = { true, true, false, true, false, false, false, true, false, false, false, false, false };
const bool AlwaysHasDecalValues[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };

const bool CanHaveAnisotropicValues[] = { false, false, false, false, true, false, false, false, false, false, false, false, false };
const bool AlwaysHasAnisotropicValues[] = { false, false, false, false, false, false, false, false, false, false, false, false, false };// look at providing guarantees for hair
