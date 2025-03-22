#include "main.h"
#include "MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Set up logging
    qSetMessagePattern("[%{type}] %{time yyyy-MM-dd hh:mm:ss}%{if-debug}@%{function}:%{line}%{endif}: %{message}");
    qInstallMessageHandler(logMessageHandler);
    qDebug() << "Started " + Common::PROJECT_NAME + " " + Common::VERSION;

    // I18N initialisation
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages)
    {
        const QString baseName = Common::DATA_NAME + "_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    // Main window properties
    MainWindow w;
    w.setMinimumSize(640, 480);
    w.show();

    return QApplication::exec();
}

void logMessageHandler(const QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    const QString typeStr = qFormatLogMessage(type, context, message);
    const qint64 currentTime = QDateTime::currentSecsSinceEpoch();

    QFile file("runtime_" + QString::fromStdString(std::to_string(currentTime)) + ".log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&file);
    textStream << typeStr << "\n";
}

