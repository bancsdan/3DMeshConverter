#include "gtest/gtest.h"
#include "geometry/vector3d.hpp"
#include "geometry/triangle.hpp"

TEST(TriangleTests, TestGetArea)
{
    Triangle t1(Vector3d{0.0, 0.0, 0.0}, Vector3d{1.0, 0.0, 0.0}, Vector3d{0.0, 1.0, 0.0});
    EXPECT_DOUBLE_EQ(0.5, t1.GetArea());

    Triangle t2(Vector3d{0.0, 0.0, 0.0}, Vector3d{0.0, 0.0, 0.0}, Vector3d{0.0, 0.0, 0.0});
    EXPECT_DOUBLE_EQ(0.0, t2.GetArea());
}

/*TEST(UtilityTests, TestGetLength) {
    Triangle t1{{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
    EXPECT_DOUBLE_EQ(1.0,       Utility::GetLineSegmentLength(t1.GetC(), t1.GetA()));
    EXPECT_DOUBLE_EQ(sqrt(2.0), Utility::GetLineSegmentLength(t1.GetB(), t1.GetC()));

    Triangle t2{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 2.0, 0.0}};
    EXPECT_DOUBLE_EQ(2.0,       Utility::GetLineSegmentLength(t2.GetC(), t2.GetA()));
    EXPECT_DOUBLE_EQ(sqrt(3.0), Utility::GetLineSegmentLength(t2.GetB(), t2.GetC()));

    Triangle t3{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    EXPECT_DOUBLE_EQ(0.0,       Utility::GetLineSegmentLength(t3.GetC(), t3.GetA()));
}*/