#-------------------------------------------------
#
# Project created by QtCreator 2013-02-09T15:58:26
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebAdministrator
TEMPLATE = app
TRANSLATIONS    = wa_en.ts \
                  wa_fr.ts
CODECFORTR      = ISO-8859-5


SOURCES += main.cpp\
        mainwindow.cpp \
    textedit.cpp \
    highlighter.cpp \
    dialoglien.cpp \
    siteview.cpp \
    block.cpp \
    page.cpp \
    sqlinterface.cpp \
    htmlbuilder.cpp \
    xmlnode.cpp \
    action.cpp \
    app.cpp \
    navigationdock.cpp \
    maincontroler.cpp \
    editwidget.cpp \
    tools.cpp \
    editblockdialog.cpp \
    settings.cpp \
    serverinfo.cpp \
    serverlistdialog.cpp

HEADERS  += mainwindow.h \
    textedit.h \
    highlighter.h \
    dialoglien.h \
    dialogtable.h \
    siteview.h \
    block.h \
    page.h \
    htmlbuilder.h \
    xmlnode.h \
    action.h \
    app.h \
    navigationdock.h \
    maincontroler.h \
    editwidget.h \
    tools.h \
    editblockdialog.h \
    settings.h \
    serverinfo.h \
    serverlistdialog.h

FORMS    +=

OTHER_FILES += \
    ressources/images/aide.png \
    ressources/images/video.png \
    ressources/images/valider.png \
    ressources/images/tableau.png \
    ressources/images/souligner.png \
    ressources/images/sauver.png \
    ressources/images/retour.png \
    ressources/images/reseau.png \
    ressources/images/refaire.png \
    ressources/images/pageWeb.png \
    ressources/images/page.png \
    ressources/images/nouveau.png \
    ressources/images/liste.png \
    ressources/images/lien.png \
    ressources/images/justifier.png \
    ressources/images/italique.png \
    ressources/images/image.png \
    ressources/images/html.png \
    ressources/images/gras.png \
    ressources/images/envoyer.png \
    ressources/images/editer.png \
    ressources/images/css.png \
    ressources/images/couper.png \
    ressources/images/couleurText.png \
    ressources/images/couleurFond.png \
    ressources/images/copier.png \
    ressources/images/coller.png \
    ressources/images/centrer.png \
    ressources/images/balise.png \
    ressources/images/annuler.png \
    ressources/images/alignerGauche.png \
    ressources/images/alignerDroite.png \
    ressources/images/icone128.png \
    ressources/images/icone48.png \
    ressources/images/options.png \
    ressources/images/listeServer.png \
    ressources/images/flash-video.png

RESOURCES += \
    sourceFile.qrc
