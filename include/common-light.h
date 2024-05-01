#pragma once

void RGBtoHSV(float red, float green, float blue, float *hue, float *sat,
              float *value) {
    *hue = 0;
    *sat = 0;
    *value = 0;

    float _min = min3(red, green, blue);
    float _max = max3(red, green, blue);
    if (_min == _max) {
        *hue = 0;
    } else if (_max == red && green >= blue) {
        *hue = 60 * (green - blue) / (_max - _min);
    } else if (_max == red && green < blue) {
        *hue = 60 * (green - blue) / (_max - _min) + 360;
    } else if (_max == green) {
        *hue = 60 * (blue - red) / (_max - _min) + 120;
    } else if (_max == blue) {
        *hue = 60 * (red - green) / (_max - _min) + 240;
    }
    if (_max == 0) {
        *sat = 0;
    } else {
        *sat = 1 - (_min / _max);
    }
    *value = _max;
}