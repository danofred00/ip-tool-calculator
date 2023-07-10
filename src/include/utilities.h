#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QStringEncoder>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonDocument>
#include <QJsonObject>

#define REGEX_IP "^\\d{1,3}(\\.\\d{1,3}){3}/(\\d){1,2}$"

class Utils : public QObject
{
  Q_OBJECT
  
public:
  explicit Utils(QObject * parent = nullptr) : QObject(parent)
  {}
  
public slots:

    inline QString regularExpression () const {
      return REGEX_IP;
    }

    inline bool saveFileContent(const QString & fileName, const QByteArray & content)
    {
      QFile file { fileName };

      if(file.exists()) {
          if(file.open(QFile::WriteOnly)) {
              file.write(content);
              file.close();
              return true;
          }
      }

      return false;
    }

    inline bool validateIp(QString ip)
    {
      QRegularExpression re {REGEX_IP, QRegularExpression::CaseInsensitiveOption};
      QRegularExpressionValidator validator {re, nullptr};
      int pos = 0;

      if(validator.validate(ip, pos) == QRegularExpressionValidator::Acceptable)
          return true;

      return false;
    }

    inline QByteArray encode(const QString str)
    {
      auto toUtf8 = QStringEncoder(QStringEncoder::Utf8);
      return toUtf8(str);
    }

    inline QString mapToString(QVariantMap map) {
      auto doc = QJsonDocument(QJsonObject::fromVariantMap(map));
      return QString(doc.toJson());
    }

};

#endif // UTILS_H
