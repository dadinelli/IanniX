#include <QtTest/QtTest>
#include "../gui/uihelp.h"

class TestUiHelp : public QObject {
    Q_OBJECT

    UiHelp ui;
    private slots:

    void testStatusHelp() {
        ui.statusHelp("Test Status Help");
        QVERIFY(ui.isVisible());
    }
};

#include "test_uihelp.moc"