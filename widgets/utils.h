// 工具类，提供一些简便的接口

#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>
#include <QObject>
#include <QVariant>

class Utils: public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);
    ~Utils();

    // 获取当前的时间戳
    Q_INVOKABLE uint currentTimeStamp();

    // 时间转换为日期格式
    Q_INVOKABLE QString dateTimeFormat(const QDateTime &dt, QString format = "yyyy-MM-dd hh:mm:ss");

    // 时间戳转换为日期格式
    Q_INVOKABLE QString timeStampFormat(qint64 time);

    // 获取一年中的第一天
    Q_INVOKABLE QDateTime firstDayOfYear();

    // 获取一年中的最后一天
    Q_INVOKABLE QDateTime lastDayOfYear();

    // 生成隐藏的字符串
    Q_INVOKABLE QString generateXXX(const QString &text, QChar ch = '*', int number = 8);

    // 生成随机口令
    Q_INVOKABLE QString generatePasscode();

    // 校验IP
    Q_INVOKABLE bool isIpVaild(const QString &ip);

    // 检查密码
    Q_INVOKABLE QVariant checkPassword(const QVariant &list) const;
};

#endif // UTILS_H
