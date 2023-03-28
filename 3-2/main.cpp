#include <UnitTest++/UnitTest++.h>
#include </home/student/timp_lab_1/LAB_2_TASK_2/modCipher.h>
#include <string>

string s = "Serafime";

SUITE(KeyTest) {
    TEST(ValidKey) {
        CHECK_EQUAL("aermeiSf",modCipher(4, "Serafime").encryption(s));
    }
    TEST(LongKey) {
        CHECK_THROW(modCipher cp(1, "Serafime"),cipher_error);
    }
}

struct KeyB_fixture {
    modCipher * p;
    KeyB_fixture() {
        p = new modCipher(4, "Serafime");
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("AERMEISF", p->encryption("SERAFIME"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("aermeisf", p->encryption("serafime"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("aermeiSf", p->encryption("Sera fime"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_THROW(p->encryption("Sera5ime"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encryption(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encryption("2*2=5?"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("emifareS", modCipher(8, "Serafime").encryption("Serafime"));
    }
}

SUITE(DecryptText) {
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("SERAFIME", p->transcript("AERMEISF", "SERAFIME"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("Serafime", p->transcript("aermeiSf", "Serafime"));
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->transcript("Serafime", "Sera fime"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->transcript("7erafime", "7erafime"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->transcript("Sera!fime", "Sera!fime"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->transcript("", ""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("Serafime", modCipher(20, "Serafime").transcript("emifareS", "Serafime"));
    }
}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}