#include <Arduino.h>
#include <SdFat.h>
#include <pins.h>
#include <unity.h>

SdFat sd;

void test_sd_init(){
    // Start SD card
    if (!sd.begin(SD_CS_PIN, SPI_FULL_SPEED)) {
        TEST_FAIL_MESSAGE("SD card not initialized");
    }
}

void test_sd_read_write(){
    const char file_name[] = "test_sdfat.txt";
    const char test_data[] = "This data should be written to the text file.\n"
                             "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    File file;

    // Delete file if it exists
    if(sd.exists(file_name)){
        TEST_ASSERT_TRUE_MESSAGE(sd.remove(file_name), "Failed to delete file");
    }

    // Create file and open in read/write mode
    oflag_t oflags = (O_CREAT | O_RDWR);
    if(!file.open(file_name, oflags)){
        TEST_FAIL_MESSAGE("Failed to open file");
    }

    // Write some data
    size_t bytes_written = file.write(test_data);
    Serial.print("Wrote ");
    Serial.print(bytes_written);
    Serial.println(" bytes to the file");
    TEST_ASSERT_EQUAL_MESSAGE(sizeof(test_data)-1, bytes_written, "Failed to write all bytes");

    // Close and reopen file
    TEST_ASSERT_TRUE_MESSAGE(file.close(), "Failed to close file");
    TEST_ASSERT_TRUE_MESSAGE(file.open(file_name, oflags), "Failed to re-open file");

    // Read some of the data back, an null terminate it to make it a valid str
    char read_data[65];
    size_t bytes_read = file.read(read_data, 64);
    read_data[bytes_read] = '\0';

    Serial.print("Read ");
    Serial.print(bytes_read);
    Serial.print(" bytes, which are as follows: \n\n");
    Serial.println(read_data);
    TEST_ASSERT_EQUAL_MESSAGE(64, bytes_read, "Failed to read 64 bytes");

    // Delete file
    TEST_ASSERT_TRUE_MESSAGE(sd.remove(file_name), "Failed to delete file");
}

void setup(){
    delay(2000);
    UNITY_BEGIN();

    RUN_TEST(test_sd_init);
    RUN_TEST(test_sd_read_write);

    UNITY_END();
}


void setUp(void){}
void tearDown(void){}
void loop(){}