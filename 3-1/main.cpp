#include <UnitTest++/UnitTest++.h>
#include </home/student/timp_lab_1/LAB_2_TASK_1/modAlphaCipher.h>

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("БВББВ",modAlphaCipher("БВБ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЖЗИЙ").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВББВ",modAlphaCipher("бвб").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б,В"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("Б В Б"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ПЕЙООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ", p->encrypt("ОДИННАДЦАТЬОЧКОВГРИФИНДОРУ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ПЕЙООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ", p->encrypt("одиннадцатьочковгрифиндору"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ПЕЙООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ", p->encrypt("ОДИННАДЦАТЬ ОЧКОВ ГРИФИНДОРУ!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ПШЛПГДСЙХЙОЕПСФ", p->encrypt("11 ОЧКОВ ГРИФИНДОРУ"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("2*2=5?"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("НГЗММЯГХЯСЫНЦЙНБВПЗУЗМГНПТ", modAlphaCipher("Я").encrypt("ОДИННАДЦАТЬОЧКОВГРИФИНДОРУ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ОДИННАДЦАТЬОЧКОВГРИФИНДОРУ", p->decrypt("ПЕЙООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("пейООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ПЕЙООБЕЧБУЭ ПШЛПГ ДСЙХЙОЕПСФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("11ПШЛПГДСЙХЙОЕПСФ"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ПЕЙООБЕЧБУЭПШЛПГДСЙХЙОЕПСФ!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ОДИННАДЦАТЬОЧКОВГРИФИНДОРУ", modAlphaCipher("Я").decrypt("НГЗММЯГХЯСЫНЦЙНБВПЗУЗМГНПТ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
