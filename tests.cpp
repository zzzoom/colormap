#include "colormap.h"

#include "gtest/gtest.h"

#include <cmath>

static void check_nop(int cm, float value, float minimum, float maximum) {
    float r = 2.0f, g = INFINITY, b = HUGE_VALF; // All invalid outputs
    colormap_rgbf(static_cast<colormap>(cm), value, minimum, maximum, &r, &g, &b);
    EXPECT_EQ(r, 2.0f);
    EXPECT_EQ(g, INFINITY);
    EXPECT_EQ(b, HUGE_VALF);
}

static void check_all_channels(int cm, float value, float minimum, float maximum, float ref_r, float ref_g, float ref_b) {
    float r = 0.0f, g = 0.0f, b = 0.0f;
    colormap_rgbf(static_cast<colormap>(cm), value, minimum, maximum, &r, &g, &b);
    EXPECT_TRUE(abs(ref_r - r) < 0.00001f);
    EXPECT_TRUE(abs(ref_g - g) < 0.00001f);
    EXPECT_TRUE(abs(ref_b - b) < 0.00001f);
}

TEST(Colormap, ColormapBounds) {
    check_nop(-1, 1.0f, 0.0f, 2.0f);
    check_nop(COLORMAP_COUNT, 1.0f, 0.0f, 2.0f);
}

TEST(Colormap, BadRange) {
    check_nop(0, 0.0f, 2.0f, 1.0f);
}

TEST(Colormap, MinColor) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, 3.0f, 3.0f, 7.0f,
            (*colormap__ptrs[cm])[0][0],
            (*colormap__ptrs[cm])[0][1],
            (*colormap__ptrs[cm])[0][2]
        );
    }
}

TEST(Colormap, ClampMinColor) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, -1.0f, 3.0f, 7.0f,
            (*colormap__ptrs[cm])[0][0],
            (*colormap__ptrs[cm])[0][1],
            (*colormap__ptrs[cm])[0][2]
        );
    }
}

TEST(Colormap, MaxColor) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, 7.0f, 3.0f, 7.0f,
            (*colormap__ptrs[cm])[COLORMAP__MAX][0],
            (*colormap__ptrs[cm])[COLORMAP__MAX][1],
            (*colormap__ptrs[cm])[COLORMAP__MAX][2]
        );
    }
}

TEST(Colormap, ClampMaxColor) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, 10.0f, 3.0f, 7.0f,
            (*colormap__ptrs[cm])[COLORMAP__MAX][0],
            (*colormap__ptrs[cm])[COLORMAP__MAX][1],
            (*colormap__ptrs[cm])[COLORMAP__MAX][2]
        );
    }
}

TEST(Colormap, ColorTableHit) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, 5.0f, 0.0f, (float) COLORMAP__MAX,
            (*colormap__ptrs[cm])[5][0],
            (*colormap__ptrs[cm])[5][1],
            (*colormap__ptrs[cm])[5][2]
        );
    }
}

TEST(Colormap, ColorInterpolation) {
    for (int cm = 0; cm < COLORMAP_COUNT; ++cm) {
        check_all_channels(cm, 4.5f, 0.0f, (float) COLORMAP__MAX,
            ((*colormap__ptrs[cm])[4][0] + (*colormap__ptrs[cm])[5][0]) / 2.0f,
            ((*colormap__ptrs[cm])[4][1] + (*colormap__ptrs[cm])[5][1]) / 2.0f,
            ((*colormap__ptrs[cm])[4][2] + (*colormap__ptrs[cm])[5][2]) / 2.0f
        );
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}