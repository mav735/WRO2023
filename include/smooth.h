const float gBoost = 14; //18

float smooth(float v0, float targetV, float s, float a = gBoost) {
    if (fabs(v0) <= fabs(targetV)) {
        if (sgn(v0) != sgn(s)) return v0;
        if (v0 < 0) return max2(-sqrt(fabs(v0 * v0 - 2 * a * s)), targetV);
        return min2(sqrt(fabs(v0 * v0 + 2 * a * s)), targetV);
    }
    else {
        if (sgn(v0) != sgn(s)) return v0;
        if (v0 < 0)
            return min2(
                v0 + sqrt(fabs(targetV * targetV - 2 * a * s)) + targetV,
                targetV);
        return max2(v0 - sqrt(fabs(targetV * targetV + 2 * a * s)) + targetV,
                    targetV);
    }
}