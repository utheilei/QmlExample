#include "utils.h"

#include <QRegExpValidator>
#include <QDebug>

#define MIN_LENGTH 6
#define MAX_LENGTH 20
#define SPECIAL_CHARACTER "~!@#$%^&*()\\[\\]\\{\\}\\\\|/?,.<>"
#define SPECIAL_DISPLAY "~!@#$%^&*()[]{}\\|/?,.<>"

const QString pattern = "^(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])(\\.(\\d|[1-9]\\d|1\\d{2}|2[0-4]\\d|25[0-5])){3}$";
const QString passwordComplexity = QString("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])[0-9A-Za-z=](.{1,})$");

Utils::Utils(QObject *parent) : QObject(parent)
{
}

Utils::~Utils()
{
}

uint Utils::currentTimeStamp()
{
    QDateTime dt = QDateTime::currentDateTime();
    return dt.toTime_t();
}

QString Utils::dateTimeFormat(const QDateTime &dt, QString format)
{
    return dt.toString(format);
}

QString Utils::timeStampFormat(qint64 time)
{
    if (time <= 0)
        return QString();

    QDateTime dt = QDateTime::fromTime_t(uint(time));
    return dateTimeFormat(dt);
}

QDateTime Utils::firstDayOfYear()
{
    QDateTime dt = QDateTime::currentDateTime();
    QDate date = dt.date();

    int y = date.year();
    date.setDate(y, 1, 1);

    return QDateTime(date, QTime(0, 0, 0));
}

QDateTime Utils::lastDayOfYear()
{
    QDateTime dt = firstDayOfYear();

    QDate date = dt.date();
    QDate lastDay = date.addYears(1);
    lastDay = lastDay.addDays(-1);

    return QDateTime(lastDay, QTime(23, 59, 59));
}

QString Utils::generateXXX(const QString &text, QChar ch, int number)
{
    if (text.isEmpty())
        return "";

    if (text.length() >= 25)
        number = 15;

    QString newText = text;
    int length = text.length();

    if (number > length)
        return text;

    int left = (length - number) / 2;
    QString holder = QString(ch).repeated(number);
    newText.replace(left, number, holder);

    return newText;
}

// 算法随机生成12个包含英文字母和数字的组合
QString Utils::generatePasscode()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec() + time.second() * 1000));

    QString charItems = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789=";
    int len = charItems.length();

    QString result;
    for (int i = 0; i < 12; i++)
        result.append(charItems.at(qrand() % (len - 1)));

    QRegExp regExp(passwordComplexity);
    QRegExpValidator regExpValidator(regExp);
    int pos = 0;
    if (regExpValidator.validate(result, pos)  !=  QValidator::State::Acceptable)
        return generatePasscode();

    return result;
}

bool Utils::isIpVaild(const QString &ip)
{
    if (!ip.contains(":"))
        return false;

    QStringList address = ip.split(":");
    if (address.size() < 2)
        return false;

    QIntValidator intValidator(1024, 65535);
    QString port = address.at(1);
    int pos = 0;
    if (port.isEmpty() || (intValidator.validate(port, pos) != QValidator::State::Acceptable))
        return false;

    QRegExp regExp(pattern);
    return regExp.exactMatch(address.at(0));
}

QVariant Utils::checkPassword(const QVariant &list) const
{
    QStringList textList = list.toStringList();
    if (textList.size() < 4)
        return QVariantList() << false << 0 << "";

    for (int i=0; i<textList.size(); i++) {
        if (textList[i].trimmed().isEmpty())
            return QVariantList() << false << i << Utils::tr("Content cannot be empty");
    }

    // 新密码不少于6位，不大于20位
    if (textList[2].length() < MIN_LENGTH || textList[2].length() > MAX_LENGTH) {
        QString message = Utils::tr("Password must be between %1 and %2 characters").arg(MIN_LENGTH).arg(MAX_LENGTH);
        return QVariantList() << false << 2 << message;
    }

    QString reg = QString("^[A-Za-z0-9%1]{%2,%3}$").arg(SPECIAL_CHARACTER).arg(MIN_LENGTH).arg(MAX_LENGTH);
    QRegExp regExpr(reg);
    // 密码只能由字母（区分大小写）、数字或特殊符号组成
    if (!regExpr.exactMatch(textList[2])) {
        QString message = Utils::tr("Password can only contain English letters (case-sensitive), numbers or special symbols (%1)").arg(SPECIAL_DISPLAY);
        return QVariantList() << false << 2 << message;
    }

    // 判断新密码和确认密码输入不一致
    if (QString::compare(textList[2], textList[3]) != 0) {
        QString message = Utils::tr("Passwords do not match");
        return QVariantList() << false << 3 << message;
    }

    return QVariantList() << true << 0 << "";
}

