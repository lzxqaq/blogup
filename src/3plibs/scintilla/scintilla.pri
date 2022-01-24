# This file is part of Notepad Next.
# Copyright 2019 Justin Dailey
#
# Notepad Next is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Notepad Next is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Notepad Next.  If not, see <https://www.gnu.org/licenses/>.

equals(QT_MAJOR_VERSION, 6): QT += core5compat

SOURCES += \
    $$PWD/qt/ScintillaEdit/ScintillaEdit.cpp \
    $$PWD/qt/ScintillaEdit/ScintillaDocument.cpp \
    $$PWD/qt/ScintillaEditBase/PlatQt.cpp \
    $$PWD/qt/ScintillaEditBase/ScintillaQt.cpp \
    $$PWD/qt/ScintillaEditBase/ScintillaEditBase.cpp \
    $$PWD/src/XPM.cxx \
    $$PWD/src/ViewStyle.cxx \
    $$PWD/src/UniqueString.cxx \
    $$PWD/src/UniConversion.cxx \
    $$PWD/src/Style.cxx \
    $$PWD/src/Selection.cxx \
    $$PWD/src/ScintillaBase.cxx \
    $$PWD/src/RunStyles.cxx \
    $$PWD/src/RESearch.cxx \
    $$PWD/src/PositionCache.cxx \
    $$PWD/src/PerLine.cxx \
    $$PWD/src/MarginView.cxx \
    $$PWD/src/LineMarker.cxx \
    $$PWD/src/KeyMap.cxx \
    $$PWD/src/Indicator.cxx \
    $$PWD/src/Geometry.cxx \
    $$PWD/src/EditView.cxx \
    $$PWD/src/Editor.cxx \
    $$PWD/src/EditModel.cxx \
    $$PWD/src/Document.cxx \
    $$PWD/src/Decoration.cxx \
    $$PWD/src/DBCS.cxx \
    $$PWD/src/ContractionState.cxx \
    $$PWD/src/CharClassify.cxx \
    $$PWD/src/CharacterType.cxx \
    $$PWD/src/CharacterCategoryMap.cxx \
    $$PWD/src/CellBuffer.cxx \
    $$PWD/src/CaseFolder.cxx \
    $$PWD/src/CaseConvert.cxx \
    $$PWD/src/CallTip.cxx \
    $$PWD/src/AutoComplete.cxx

HEADERS  += \
    $$PWD/qt/ScintillaEdit/ScintillaEdit.h \
    $$PWD/qt/ScintillaEdit/ScintillaDocument.h \
    $$PWD/qt/ScintillaEditBase/ScintillaEditBase.h \
    $$PWD/qt/ScintillaEditBase/ScintillaQt.h

INCLUDEPATH += \
    $$PWD/qt/ScintillaEditBase/ \
    $$PWD/qt/ScintillaEdit/ \
    $$PWD/include \
    $$PWD/src

DEFINES += SCINTILLA_QT=1 MAKING_LIBRARY=1 SCI_LEXER=1 _CRT_SECURE_NO_DEPRECATE=1
CONFIG(release, debug|release) {
    DEFINES += NDEBUG=1
}

macx {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
}
