DEFINES += UCHARDET_SHARED BUILDING_UCHARDET

HEADERS += \
    $$PWD/uchardet.h

SOURCES += \
    $$PWD/uchardet.cpp \
    $$PWD/CharDistribution.cpp \
    $$PWD/JpCntx.cpp \
    $$PWD/LangModels/LangArabicModel.cpp \
    $$PWD/LangModels/LangBulgarianModel.cpp \
    $$PWD/LangModels/LangCroatianModel.cpp \
    $$PWD/LangModels/LangCzechModel.cpp \
    $$PWD/LangModels/LangEsperantoModel.cpp \
    $$PWD/LangModels/LangEstonianModel.cpp \
    $$PWD/LangModels/LangFinnishModel.cpp \
    $$PWD/LangModels/LangFrenchModel.cpp \
    $$PWD/LangModels/LangDanishModel.cpp \
    $$PWD/LangModels/LangGermanModel.cpp \
    $$PWD/LangModels/LangGreekModel.cpp \
    $$PWD/LangModels/LangHungarianModel.cpp \
    $$PWD/LangModels/LangHebrewModel.cpp \
    $$PWD/LangModels/LangIrishModel.cpp \
    $$PWD/LangModels/LangItalianModel.cpp \
    $$PWD/LangModels/LangLithuanianModel.cpp \
    $$PWD/LangModels/LangLatvianModel.cpp \
    $$PWD/LangModels/LangMalteseModel.cpp \
    $$PWD/LangModels/LangPolishModel.cpp \
    $$PWD/LangModels/LangPortugueseModel.cpp \
    $$PWD/LangModels/LangRomanianModel.cpp \
    $$PWD/LangModels/LangRussianModel.cpp \
    $$PWD/LangModels/LangSlovakModel.cpp \
    $$PWD/LangModels/LangSloveneModel.cpp \
    $$PWD/LangModels/LangSwedishModel.cpp \
    $$PWD/LangModels/LangSpanishModel.cpp \
    $$PWD/LangModels/LangThaiModel.cpp \
    $$PWD/LangModels/LangTurkishModel.cpp \
    $$PWD/LangModels/LangVietnameseModel.cpp \
    $$PWD/nsHebrewProber.cpp \
    $$PWD/nsCharSetProber.cpp \
    $$PWD/nsBig5Prober.cpp \
    $$PWD/nsEUCJPProber.cpp \
    $$PWD/nsEUCKRProber.cpp \
    $$PWD/nsEUCTWProber.cpp \
    $$PWD/nsEscCharsetProber.cpp \
    $$PWD/nsEscSM.cpp \
    $$PWD/nsGB2312Prober.cpp \
    $$PWD/nsMBCSGroupProber.cpp \
    $$PWD/nsMBCSSM.cpp \
    $$PWD/nsSBCSGroupProber.cpp \
    $$PWD/nsSBCharSetProber.cpp \
    $$PWD/nsSJISProber.cpp \
    $$PWD/nsUTF8Prober.cpp \
    $$PWD/nsLatin1Prober.cpp \
    $$PWD/nsUniversalDetector.cpp

INCLUDEPATH += \
    $$PWD/ \
    $$PWD/LangModels

