#ifndef DIALOGLIEN_H
#define DIALOGLIEN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace WA_UI {
class DialogLien;
}

class DialogLien : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLien(QString *url, QString  *text, bool *annuler, QWidget *parent = 0);
    ~DialogLien();

public slots:
    void valider();

protected:
    QString* parentUrl;
    QString* parentText;
    bool* parentAnnuler;
    QLineEdit* urlEdit;
    QLineEdit* textEdit;
    QPushButton* ok;
    QPushButton* cancel;

};

#endif // DIALOGLIEN_H
