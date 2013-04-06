#ifndef EDITBLOCKDIALOG_H
#define EDITBLOCKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

class EditBlockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditBlockDialog(QWidget *parent = 0);

    void setTitre(QString const& titre);
    void setIndex(int const& index);
    void setMaxIndex(int const& max);
    void setIndexModifiable(bool const& flag);
    void setPageName(QString const name);

public slots:
    void setCreateDate(QString const date);
    void setLastModifDate(QString const& date);
    void launcheTouchModifDate();

public:
    QString getTitre();
    int getIndex();

private:
    QLineEdit* titre;
    QSpinBox* index;
    QLabel* pageName;
    QLabel* createDate;
    QLabel* lastModifDate;
    int startIndex;

signals:
    void touchModifDate(const unsigned short &index);
};

#endif // EDITBLOCKDIALOG_H
