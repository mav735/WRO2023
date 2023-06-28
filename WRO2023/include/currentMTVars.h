typedef struct {
    float targetV;
    float targetEnc;
} tCurrentMTVars;

tCurrentMTVars MTVarsA, MTVarsB;

void initMtVars(){
    MTVarsA.targetEnc = 0;
    MTVarsA.targetV = 0;
    MTVarsB.targetEnc = 0;
    MTVarsB.targetV = 0;
}
