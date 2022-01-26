DEFINES += UCHARDET_SHARED BUILDING_UCHARDET

HEADERS += \
    $$PWD/src/uchardet.h

SOURCES += \
    $$PWD/src/uchardet.cpp \
    $$PWD/src/CharDistribution.cpp \
    $$PWD/src/JpCntx.cpp \
    $$PWD/src/LangModels/LangArabicModel.cpp \
    $$PWD/src/LangModels/LangBulgarianModel.cpp \
    $$PWD/src/LangModels/LangCroatianModel.cpp \
    $$PWD/src/LangModels/LangCzechModel.cpp \
    $$PWD/src/LangModels/LangEsperantoModel.cpp \
    $$PWD/src/LangModels/LangEstonianModel.cpp \
    $$PWD/src/LangModels/LangFinnishModel.cpp \
    $$PWD/src/LangModels/LangFrenchModel.cpp \
    $$PWD/src/LangModels/LangDanishModel.cpp \
    $$PWD/src/LangModels/LangGermanModel.cpp \
    $$PWD/src/LangModels/LangGreekModel.cpp \
    $$PWD/src/LangModels/LangHungarianModel.cpp \
    $$PWD/src/LangModels/LangHebrewModel.cpp \
    $$PWD/src/LangModels/LangIrishModel.cpp \
    $$PWD/src/LangModels/LangItalianModel.cpp \
    $$PWD/src/LangModels/LangLithuanianModel.cpp \
    $$PWD/src/LangModels/LangLatvianModel.cpp \
    $$PWD/src/LangModels/LangMalteseModel.cpp \
    $$PWD/src/LangModels/LangPolishModel.cpp \
    $$PWD/src/LangModels/LangPortugueseModel.cpp \
    $$PWD/src/LangModels/LangRomanianModel.cpp \
    $$PWD/src/LangModels/LangRussianModel.cpp \
    $$PWD/src/LangModels/LangSlovakModel.cpp \
    $$PWD/src/LangModels/LangSloveneModel.cpp \
    $$PWD/src/LangModels/LangSwedishModel.cpp \
    $$PWD/src/LangModels/LangSpanishModel.cpp \
    $$PWD/src/LangModels/LangThaiModel.cpp \
    $$PWD/src/LangModels/LangTurkishModel.cpp \
    $$PWD/src/LangModels/LangVietnameseModel.cpp \
    $$PWD/src/nsHebrewProber.cpp \
    $$PWD/src/nsCharSetProber.cpp \
    $$PWD/src/nsBig5Prober.cpp \
    $$PWD/src/nsEUCJPProber.cpp \
    $$PWD/src/nsEUCKRProber.cpp \
    $$PWD/src/nsEUCTWProber.cpp \
    $$PWD/src/nsEscCharsetProber.cpp \
    $$PWD/src/nsEscSM.cpp \
    $$PWD/src/nsGB2312Prober.cpp \
    $$PWD/src/nsMBCSGroupProber.cpp \
    $$PWD/src/nsMBCSSM.cpp \
    $$PWD/src/nsSBCSGroupProber.cpp \
    $$PWD/src/nsSBCharSetProber.cpp \
    $$PWD/src/nsSJISProber.cpp \
    $$PWD/src/nsUTF8Prober.cpp \
    $$PWD/src/nsLatin1Prober.cpp \
    $$PWD/src/nsUniversalDetector.cpp

INCLUDEPATH += \
    $$PWD/src/ \
    $$PWD/LangModels

