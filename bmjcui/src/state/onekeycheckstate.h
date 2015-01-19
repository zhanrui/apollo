#ifndef ONEKEYCHECKSTATE_H
#define ONEKEYCHECKSTATE_H

#include <QObject>

class OneKeyCheckState : public QObject {
    Q_OBJECT

public:
    explicit OneKeyCheckState(QObject* parent = 0);
    ~OneKeyCheckState();

signals:

public slots:
    void actionSlot(const QString& qs);
    //void cancelCheck();

private:
    bool m_isSelected;
    QString m_normalIcon;
};

#endif // ONEKEYCHECKSTATE_H
