#include "tools.h"

#include <QMessageBox>

Tools::Tools(TextEdit *editor)
{
    this->editor = editor;
    fontSizeSpinBox = new QSpinBox();
    initActions();
    initToolBar();
    initMenuBar();

    //TODO*** next version
    insertMovieAction->setEnabled(false);
}
Tools::~Tools()
{
    delete menuBar;
    delete toolBar;
    delete fileMenu;
    delete EditMenu;
    delete HelpMenu;
}

QMenuBar* Tools::getMenuBar(){
    return menuBar;
}

QToolBar* Tools::getToolBar(){
    return toolBar;
}

void Tools::addMenu(QMenu* menu)
{
    menuBar->insertMenu(separatorBeforInsert, menu);
}

void Tools::initActions()
{
    cutAction = new Action("couper", tr("Couper"), this);
    pasteAction = new Action("coller", tr("Coller"), this);
    copyAction = new Action("copier", tr("Copier"), this);

    boldAction = new Action("gras", tr("&Gras"));
    italicAction = new Action("italique", tr("&Italique"), this);
    underlineAction = new Action("souligner", tr("&Souligner"), this);

    alignLeftAction = new Action("alignerGauche", tr("Gauche"), this);
    alignRightAction = new Action("alignerDroite", tr("Droite"), this);
    alignCenterAction = new Action("centrer", tr("Centrer"), this);
    justifyAction = new Action("justifier", tr("Justifier"), this);

    fontColorAction = new Action("couleurText", tr("Couleur"), this);
    backgroundColorAction = new Action("couleurFond", tr("Couleur de fond"), this);
    fontSizeAction = new Action("icon", tr("Taille de police"), this);

    insertListAction = new Action("liste", tr("Liste"), this);
    insertTableAction = new Action("tableau", tr("Tableau"), this);

    insertLienAction = new Action("lien", tr("&Lien"), this);
    insertPictureAction = new Action("image", tr("&Image"), this);
    insertMovieAction = new Action("video", tr("&Video"), this);

    undoAction = new Action("retour", tr("&Annuler"), this);
    redoAction = new Action("refaire", tr("&Refaire"), this);

    switchRicheAction = new Action("page", tr("Mode riche"), this);
    switchHtmlAction = new Action("html", tr("Mode HTML"), this);

    connectAction = new Action("reseau", tr("Connexion"), this);
    refreshAction = new Action("rafraichir", tr("Rafraichir"), this);
    saveAction = new Action("sauver", tr("Sauvegarder"), this);

    helpAction = new Action("aide", tr("Aide"), this);

    closeAction = new Action("icon", tr("&Fermer"), this);

    listServerAction = new Action("listeServer", tr("Liste des serveurs"), this);
    aboutAction = new Action("", tr("A propos"), this);
    optionAction = new Action("options", tr("&Options"), this);

    fontColorAction->setCheckable(true);
    backgroundColorAction->setCheckable(true);
    boldAction->setCheckable(true);
    italicAction->setCheckable(true);
    underlineAction->setCheckable(true);

    initShortcut();
}

void Tools::initShortcut()
{
    cutAction->setShortcut(QKeySequence(QKeySequence::Cut));
    pasteAction->setShortcut(QKeySequence(QKeySequence::Paste));
    copyAction->setShortcut(QKeySequence(QKeySequence::Copy));

    connectAction->setShortcut(QKeySequence(QKeySequence::Open));
    saveAction->setShortcut(QKeySequence(QKeySequence::Save));

    boldAction->setShortcut(QKeySequence(QKeySequence::Bold));
    italicAction->setShortcut(QKeySequence(QKeySequence::Italic));
    underlineAction->setShortcut(QKeySequence(QKeySequence::Underline));

    undoAction->setShortcut(QKeySequence(QKeySequence::Undo));
    redoAction->setShortcut(QKeySequence(QKeySequence::Redo));

    optionAction->setShortcut(QKeySequence(QKeySequence::Preferences));
}

void Tools::initToolBar()
{
    toolBar = new QToolBar();

    //Fichier
    toolBar->addAction(connectAction);
    toolBar->addSeparator();
    toolBar->addAction(saveAction);
    toolBar->addSeparator();

    //Edition
    toolBar->addAction(undoAction);
    toolBar->addAction(redoAction);
    toolBar->addSeparator();
    toolBar->addAction(copyAction);
    toolBar->addAction(cutAction);
    toolBar->addAction(pasteAction);
    toolBar->addSeparator();
    toolBar->addAction(boldAction);
    toolBar->addAction(italicAction);
    toolBar->addAction(underlineAction);
    toolBar->addSeparator();
    toolBar->addAction(alignLeftAction);
    toolBar->addAction(alignRightAction);
    toolBar->addAction(alignCenterAction);
    toolBar->addAction(justifyAction);
    toolBar->addSeparator();
    toolBar->addAction(switchRicheAction);
    toolBar->addAction(switchHtmlAction);
    toolBar->addSeparator();
    toolBar->addAction(insertListAction);
    toolBar->addAction(insertTableAction);
    toolBar->addSeparator();
    toolBar->addWidget(fontSizeSpinBox);
    toolBar->addAction(fontColorAction);
    toolBar->addAction(backgroundColorAction);
    toolBar->addSeparator();
    toolBar->addAction(insertLienAction);
    toolBar->addAction(insertPictureAction);
    toolBar->addAction(insertMovieAction);
    toolBar->addSeparator();

    //Option
    toolBar->addAction(optionAction);
    toolBar->addAction(listServerAction);
}

void Tools::initMenuBar()
{
    menuBar = new QMenuBar();
    fileMenu = new QMenu(tr("Fichier"));
    EditMenu = new QMenu(tr("Edition"));
    HelpMenu = new QMenu(tr("Aide"));

    //Fichier
    fileMenu->addAction(connectAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    menuBar->addMenu(fileMenu);

    //Edition
    EditMenu->addAction(undoAction);
    EditMenu->addAction(redoAction);
    EditMenu->addSeparator();
    EditMenu->addAction(copyAction);
    EditMenu->addAction(cutAction);
    EditMenu->addAction(pasteAction);
    EditMenu->addSeparator();
    EditMenu->addAction(boldAction);
    EditMenu->addAction(italicAction);
    EditMenu->addAction(underlineAction);
    EditMenu->addSeparator();
    EditMenu->addAction(alignLeftAction);
    EditMenu->addAction(alignRightAction);
    EditMenu->addAction(alignCenterAction);
    EditMenu->addAction(justifyAction);
    EditMenu->addSeparator();
    EditMenu->addAction(switchRicheAction);
    EditMenu->addAction(switchHtmlAction);
    EditMenu->addSeparator();
    EditMenu->addAction(insertListAction);
    EditMenu->addAction(insertTableAction);
    EditMenu->addSeparator();
    EditMenu->addAction(fontColorAction);
    EditMenu->addAction(backgroundColorAction);
    EditMenu->addSeparator();
    EditMenu->addAction(insertLienAction);
    EditMenu->addAction(insertPictureAction);
    EditMenu->addAction(insertMovieAction);
    menuBar->addMenu(EditMenu);

    //Tree edition
    menuBar->addSeparator();
    separatorBeforInsert = menuBar->addSeparator();

    //Aide
    HelpMenu->addAction(optionAction);
    HelpMenu->addAction(listServerAction);
    HelpMenu->addSeparator();
    HelpMenu->addAction(aboutAction);
    HelpMenu->addAction(helpAction);
    menuBar->addMenu(HelpMenu);
}

void Tools::switchTools(bool richeMode)
{
    boldAction->setEnabled(richeMode);
    italicAction->setEnabled(richeMode);
    underlineAction->setEnabled(richeMode);
    alignLeftAction->setEnabled(richeMode);
    alignRightAction->setEnabled(richeMode);
    alignCenterAction->setEnabled(richeMode);
    justifyAction->setEnabled(richeMode);
    switchRicheAction->setEnabled(!richeMode);
    switchHtmlAction->setEnabled(richeMode);
    insertListAction->setEnabled(richeMode);
    insertTableAction->setEnabled(richeMode);
    insertLienAction->setEnabled(richeMode);
    insertPictureAction->setEnabled(richeMode);
    insertMovieAction->setEnabled(false); //Enable at futur version
    fontSizeAction->setEnabled(richeMode);
    fontColorAction->setEnabled(richeMode);
    backgroundColorAction->setEnabled(richeMode);
}

void Tools::majToolsValue()
{
    fontSizeSpinBox->setValue(editor->textCursor().charFormat().font().pointSize());

    fontColorAction->setChecked(!editor->isTextBaseColor());
    backgroundColorAction->setChecked(!editor->isTextBaseBackgroundColor());

    if(editor->fontWeight() == QFont::Bold)
        boldAction->setChecked(true);
    else
        boldAction->setChecked(false);

    if(editor->fontItalic())
        italicAction->setChecked(true);
    else
        italicAction->setChecked(false);

    if(editor->fontUnderline())
        underlineAction->setChecked(true);
    else
        underlineAction->setChecked(false);

    alignLeftAction->setEnabled(true);
    alignRightAction->setEnabled(true);
    alignCenterAction->setEnabled(true);
    justifyAction->setEnabled(true);

    switch(editor->alignment())
    {
    case Qt::AlignLeft:
            alignLeftAction->setEnabled(false);
            break;
    case Qt::AlignRight:
            alignRightAction->setEnabled(false);
            break;
    case Qt::AlignCenter:
            alignCenterAction->setEnabled(false);
            break;
    case Qt::AlignJustify:
            justifyAction->setEnabled(false);
            break;
    default:
        break;
    }
}

void Tools::openAbout()
{
    QMessageBox message;

    message.setText(tr("<strong>A propos!</strong>"));
    message.setInformativeText(tr("Version : 1.0.1 \n Auteur : Zakynes"));
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);

    message.exec();
}

void Tools::openHelp()
{
    QMessageBox message;

    message.setText(tr("<strong>Aide</strong>"));
    message.setInformativeText(tr("Il n'y a pas de document d'aide encore disponible"));
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);

    message.exec();
}
