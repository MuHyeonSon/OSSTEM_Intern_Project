QT       += core gui sql  # sql library 추가 이것들과 관련된 dll이 따라옴

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # qt 4번째보다 크면 += 뒤에 있는 것 항목을 추가시켜라

CONFIG += c++17 # 현재 C++버전 어떤 것을 쓸지를 설정

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \ # source 파일
    main.cpp \
    mainwindow.cpp

HEADERS += \ # Header 파일
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin # (컴파일할 경우) 자동으로 빌드된 실행 파일을 target path로 옮겨줌
                                        # 어떤 dircectory에다가 옮길지 정해준다. (디렉토리 명 지정 가)
else: unix:!android: target.path = /opt/$${TARGET}/bin #(qnx 아닐경우) 리눅스 인데 안드로이드냐 안드로이드가 아니냐를 따질 때 할 때 이렇게 할 수 있음
                                                       #여기는 리눅스인데 안드로이드가 아닐 경우 우항에 디렉토리로 옮겨라
                                                        # target은 apllication명이 된다.
!isEmpty(target.path): INSTALLS += target        #
