#include <NavalCommand/Error/Api/ToStringView.h>
#include <gtest/gtest.h>

TEST(ToStringViewTest, DescribesNotReady)
{
	EXPECT_EQ(NavalCommand::Error::Api::ToStringView(
		NavalCommand::Error::Api::ErrorCondition::NotReady), "not ready");
}
