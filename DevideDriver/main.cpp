#include "gmock/gmock.h"
#include "device_driver.h"

#include "testable_flash_memory_device.cpp"

using namespace testing;

//TEST(DeviceDriver, ReadFromHW) {
//	// TODO : replace hardware with a Test Double
//	FlashMemoryDevice* hardware = new FlashMock();
//	DeviceDriver driver{ hardware };
//	int data = driver.read(0xFF);
//	EXPECT_EQ(0, data);
//}

TEST(DeviceDriver, Read5TimesFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMock hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read).Times(5);
	int data = driver.read(0xFF);
}

TEST(DeviceDriver, ReadExceptionFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMock hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read((long)0xA))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xDD))
		.WillOnce(Return((int)0xD9));

	EXPECT_THROW(driver.read(0xA), std::exception);

}

TEST(DeviceDriver, WriteFromHW) {
	// TODO : replace hardware with a Test Double
	NiceMock<FlashMock> hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read((long)0xA)).Times(1).WillOnce(Return((long)0xFF));

	driver.write(0xA, 'a');
}

TEST(DeviceDriver, WriteExceptionFromHW) {
	// TODO : replace hardware with a Test Double
	NiceMock<FlashMock> hardware;
	DeviceDriver driver{ &hardware };
	EXPECT_CALL(hardware, read((long)0xA)).Times(1).WillOnce(Return((long)0xFD));

	EXPECT_THROW(driver.write(0xA, 'a'), std::exception);

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}