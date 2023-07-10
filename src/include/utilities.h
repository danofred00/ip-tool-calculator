#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QSettings>
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
  explicit Utils(QSettings * settings, QObject * parent = nullptr) : QObject(parent)
  {
      m_settings = settings;
      //
  }
  
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

    inline void saveSetting(QString key, QVariant value) {
        m_settings->setValue(QAnyStringView(key), value);
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

private:
    QSettings * m_settings;
};

#endif // UTILS_H
